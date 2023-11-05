#include "includes.h"
#include "OS_CPU.h"
#include "bsp.h"

#include "config.h"
//#include "target.h"

/*端口定义*/
#define	    KEY_OK		    (1 << 4 ) //OK键，控制电机启止
#define	    KEY_ESC		    (1 << 5 ) //ESC键，控制电机运转方向
#define	    KEY_CENT	    (1 << 6 ) //CENT键，控制CENT灯
#define     KEY_AUTO	    (1 << 7 ) //AUTO键，电机自动纠偏
#define	    KEY_MANU	    (1 << 10) //MANU键，电机手动纠偏
#define	    KEY_DEC		    (1 << 11) //DEC键，减小电机运行速度
#define	    KEY_INC	        (1 << 12) //INC键，增大电机运行速度

#define     LED_MANU		(1 << 14) //MANU灯
#define     LED_CENT		(1 << 15) //CENT灯
#define     LED_AUTO		(1 << 16) //AUTO灯
#define     LED_ALARM   (1 << 13)//ALARM灯
#define     ADC_PULSE 		(1 << 8 ) // 电机控制的端口
#define     ADC_EN    		(1 << 17)
#define     ADC_MODE 		(1 << 18)
#define     ADC_DIR   		(1 << 19)

#define		TASK_STK_SIZE		128

OS_STK		TaskStartStk[TASK_STK_SIZE];

void TaskStart(void *data);

/*分配任务的堆栈空间*/
OS_STK	StacK_I2C[128]; //看门狗控制任务
OS_STK  StacK_CAN[128]; //CAN总线任务
OS_STK	StacK_KEY[128]; //捕获按键信息任务
OS_STK	StacK_MID[128]; //键盘处理任务
OS_STK	StacK_PWM[128]; //PID算法驱动步进电机
OS_STK	StacK_LCD[128]; //屏幕显示任务

void PWM_Out(uint16 spd, uint8 dir);

/*定义任务之间通讯信号*/
OS_EVENT *SEM_UPDATE;
OS_EVENT *MBOX_KEYDN;
OS_EVENT *SEM_CAN;
OS_EVENT *SEM_AUTO;


/*定义常数*/
//K=Kp;Kt=Kp*Ts/Ti;Kd=Kp*Td/Ts; 
#define  	K              0.45//比例放大系数,初始值0.3125
#define  	T              1.9556  //Ts/Ti
#define  	TDs            1.564   //Td/Ts
#define  	Setpoint       125 //电机中点位置

#define		EXT_01		(1 << 21)
#define		EXT_02		(1 << 20)

#define		GetRelPos(dat)	(((dat) & (1 << 12)) ? (-(((dat) >> 00) & 0xFFF)) : (((dat) >> 00) & 0xFFF))

/*定义全局变量*/
uint8 control = 1; //自动纠偏控制变量
uint8 run = 1,dir = 0; //电机运行控制变量
uint8 cent=0;
uint8 u8CntKEY = 0; //键盘信息捕获任务控制变量
uint8 u8CntI2C = 0; //看门狗任务控制变量
//uint8 canout = 0; //CAN总线数据暂存变量
int16 canout= 0;
uint16 U1=0;
int16 temspd = 0; //定义全局变量控制初始运行；

char  strtmp[8]; //用于LCD输出文字时用的字符型数组变量
char  strKey[8]; //用于储存键盘信息时用的字符型数组变量


void TargetResetInit(void)
{
#ifdef __DEBUG_RAM    
    MEMMAP = 0x2;                   //remap
#endif

#ifdef __DEBUG_FLASH    
    MEMMAP = 0x1;                   //remap
#endif

#ifdef __IN_CHIP    
    MEMMAP = 0x1;                   //remap
#endif

    /* 设置系统各部分时钟 */
    PLLCON = 1;
#if (Fpclk / (Fcclk / 4)) == 1
    VPBDIV = 0;
#endif
#if (Fpclk / (Fcclk / 4)) == 2
    VPBDIV = 2;
#endif
#if (Fpclk / (Fcclk / 4)) == 4
    VPBDIV = 1;
#endif

#if (Fcco / Fcclk) == 2
    PLLCFG = ((Fcclk / Fosc) - 1) | (0 << 5);
#endif
#if (Fcco / Fcclk) == 4
    PLLCFG = ((Fcclk / Fosc) - 1) | (1 << 5);
#endif
#if (Fcco / Fcclk) == 8
    PLLCFG = ((Fcclk / Fosc) - 1) | (2 << 5);
#endif
#if (Fcco / Fcclk) == 16
    PLLCFG = ((Fcclk / Fosc) - 1) | (3 << 5);
#endif
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
    while((PLLSTAT & (1 << 10)) == 0);
    PLLCON = 3;
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
    
    /* 设置存储器加速模块 */
    MAMCR = 0;
#if Fcclk < 20000000
    MAMTIM = 1;
#else
#if Fcclk < 40000000
    MAMTIM = 2;
#else
    MAMTIM = 3;
#endif
#endif
    MAMCR = 2;
    
    /* 初始化VIC */
    VICIntEnClr = 0xffffffff;
    VICVectAddr = 0;
    VICIntSelect = 0;

    /* 添加自己的代码 */

}



/***********************************************************
                      看门狗控制任务
                      
describe：程序运行，每隔一段时间给看门狗信号，清空它的计数器
          否则计数器溢出，会给处理器一个复位信号。
************************************************************/
void TasK_I2C(void *pdata)
{
	uint8 i= 0;
	pdata= pdata;
	
	SEM_UPDATE= OSSemCreate(1); // 创建信号量
	
	while(1)
	{
		I2C_FeedDog(); // 硬件看门狗
		if(++i>= 10) {
			i= 0;
			u8CntI2C++;
			OSSemPost(SEM_UPDATE); // 发送信号量
		}
		OSTimeDlyHMSM(0, 0, 0, 5); // 自身延时等待
	}
}



/**********************************************************
                        CAN总线任务
                        
describe：读出输出值，作为PID算法的输入，接受处理数据
***********************************************************/
void TasK_CAN(void* pdata)
{
	uint8 err= 0;
	pdata=pdata;
	err= err;
	
	SEM_CAN= OSSemCreate(1); // 创建信号量
	
   	InitCAN(CAN1);// CAN初始化
	ConfigAFReg();// 配置接收控制

	while(1)
	{
		/* 采用中断方式接收数据, 如果收到数据, 可以在此处进行检测 */
		while(!((CANRcvCyBufApp[CAN1].ReadPoint!= CANRcvCyBufApp[CAN1].WritePoint) || CANRcvCyBufApp[CAN1].FullFlag)) 
			OSTimeDlyHMSM(0, 0, 0, 5);
		canout= GetRelPos(CANRcvCyBufApp[CAN1].RcvBuf[CANRcvCyBufApp[CAN1].ReadPoint].RDA.Word);
		//can总线传来的数据是64位的，对其中低32位数据右移10位后取出最后的11位数据赋给全局变量canout
		
		OSSemPost(SEM_CAN); // 发送信号量
		//发送一个信号量。如果有任务等待，调用OS_EventTaskRdy()将任务置为就绪，调度。
		
		if(++CANRcvCyBufApp[CAN1].ReadPoint>= USE_CAN_cycRCV_BUF_SIZE)
			CANRcvCyBufApp[CAN1].ReadPoint= 0;
		CANRcvCyBufApp[CAN1].FullFlag= 0;
	}
}



/**********************************************************
                       键盘处理任务
***********************************************************/
void TasK_MID(void *pdata)
{
	uint8  err;
	bool flag = 1;
	int step = 0;
	uint32 *Key= 0;
	pdata= pdata;
	MBOX_KEYDN= OSMboxCreate(&Key);
	
	while(1)
	{
		Key= OSMboxPend(MBOX_KEYDN, 0, &err); // 等待来自Task_KEY的邮箱消息
				switch(*Key) 
		{
			case KEY_CENT:
			
			IO0CLR=LED_CENT;
	
			//对中程序

		while(flag)
   {
   while((~IO1PIN) & EXT_01)//没到最左
   {
     PWM_Out(60, 1);//移动到最左
   }
   while((~IO1PIN) & EXT_02)//没到最右
   {
     PWM_Out(60, 0);step++;//移动到最右开始计数
   }
   step = step/2;
	 step += 33000;
   while(step!=0)
   {
     PWM_Out(60, 1);//控制速度与方向
     step--; 
     flag = 0;    
   }
	 PWM_Out(0, 0);
  }
	 flag = 1;
	 IO0SET=LED_CENT;//按键控制
					break;
				
					
					
			case KEY_AUTO: 
					control=1-control;
					if(control)
					{
						IO0SET=LED_AUTO;
						strcpy(strtmp, "    ");
						
						break;
					}
					else
					{
						IO0CLR=LED_AUTO;
						strcpy(strtmp, "AUTO");
						IO0SET=LED_MANU;
						break;
					}
					
			case KEY_MANU:
			{   IO0SET=LED_AUTO;
				  control=1;
				IO0CLR=LED_MANU;
					strcpy(strtmp, "MANU");}
					OSSemPost(SEM_UPDATE);
		}	
		

    		
		OSTimeDlyHMSM(0, 0, 0, 300);
	}
}



/**********************************************************
                        按键处理任务
***********************************************************/
void TasK_KEY(void *pdata)
{
	uint8  i= 0;
	uint32 Key= 0;
	pdata= pdata;

	MBOX_KEYDN= OSMboxCreate(&Key);// 创建邮箱信息，准备送给Task_MID
	
	I2C_Init(); //I2C初始化
	
	/*按键和灯的端口定义*/	
	PINSEL0&=~((3<<12) | (3<<14) | (3<<20) | (3<<28) | ((uint32)3<<30));
	PINSEL1&=~(3<<0);
	IO0DIR |= LED_AUTO | LED_MANU | LED_CENT|LED_ALARM;//set LED AS out
	IO0DIR &= ~(KEY_AUTO | KEY_MANU | KEY_CENT);//set KEY AS in
  
	while(1)
	{
	
		while((Key= (~IO0PIN) & (KEY_AUTO | KEY_CENT | KEY_MANU))== 0)
					OSTimeDlyHMSM(0, 0, 0, 50);
					
		OSMboxPost(MBOX_KEYDN, (void *)&Key); // 发送邮箱消息给Task_MID

		if(++i>= 10)
		{
			i= 0;
			u8CntKEY++;
		}
		
		OSTimeDlyHMSM(0, 0, 0, 15);
		I2C_FeedDog();//喂狗
	}
}



/**********************************************************
                       电机驱动任务
***********************************************************/
/*电机驱动函数*/
void PWM_Out(uint16 spd, uint8 dir) 
{
	temspd=0;//设置初始速度，让电机初始状态为停；
	//检测边界情况
	if(dir== 1 && ((~IO1PIN) & EXT_01)== 0) {spd = 0;	 IO0CLR =LED_ALARM;}
  else if(dir== 0 && ((~IO1PIN) & EXT_02)== 0) {spd = 0;  IO0CLR =LED_ALARM;}
	else 
		IO0SET=LED_ALARM;

	if(spd == 0)
	{
		PWMTCR= 2;
		return;
	}
	else 
		IO0SET=LED_ALARM;
	
	if(dir)
		IO0SET= (1 << 19);
	else
		IO0CLR= (1 << 19);
	
	PWMMR0= Fpclk/ (spd*10);//设置定时器的时间,通过匹配时重新设置计数值来控制PWM周期率
	PWMMR4= PWMMR0/ 2;// 50%占空比
	PWMLER= (1 << 0) | (1 << 4);// PWM0和PWM4匹配锁存
	PWMTCR= 9;// 启动PWM输出
}


void TasK_PWM(void* pdata)
{
	//PID算法
	uint8 err = 0;
	uint8 dir=0;
	int e[3]= {0};
	int outn = 0;
	
//	FP32 q0=K*(1+T),q1=-K,U=0; //计算q0和q1，并给u0赋初值
	FP32 q0=K*(1+T+TDs);
	FP32 q1=-K*(1+2*TDs);
	FP32 q2=K*TDs;
	FP32 U=0; //计算q0和q1和q2，并给u0赋初值
	
	pdata=pdata; 
	  while(1)
	 {
		OSSemPend(SEM_CAN,0, &err);//功能：申请一个信号量。
		//任务在无法获得信号量时会调用OS_EventTaskWait()挂起，再调用OSSched()进行任务切换。
		//在超时返回时,调用OS_EventTo（）将任务置为就绪.
		
		temspd=50;
		
		/* 以下是电机控制端口和PWM端口设置 */
		PINSEL0&=~ (3 << 16); // 将PWM端口设置为普通的IO口
		PINSEL0|=  (2 << 16); // 选中PWM4
		PINSEL1&=~((3 <<  2) | (3 <<  4) | (3 <<  6));// 设置为电机控制口17，18，19
		PINSEL2 &= ~0x08;
		IO0DIR |=(ADC_EN | ADC_MODE | ADC_DIR);//输出
		IO0CLR  =  (1 << 17);//P0.17置0
		PWMMCR  = 2;//reset PWMMCR0
		PWMPCR  = 1 << 12;// enable PM4
		
		e[0]= canout;//计算K时刻的误差采样值
		
    if(e[0] > 30)dir=1;
		    else if(e[0] <- 30)dir=0;
		         else temspd=0;
		
		if(temspd==0) {
			PWM_Out(0, 0);
			continue;
		}
		  else
      {
				U=q0*e[0]+q1*e[1]+q2*e[2];
				U1=U;
				if(U>0)
				outn = 0.4*U;
				else
				outn = -0.4*U;
				
				temspd=outn;
				if(temspd > 99)
					temspd = 99;
		  }	
        e[2]=e[1];
        e[1]=e[0]; //数据传递				
		
		/*传递电机运行速度与方向给电机驱动函数*/
   if (control==0)
	{
		if(1)
			{
			if(!((dir== 1 && ((~IO1PIN) & EXT_01)== 0) || 
			     (dir== 0 && ((~IO1PIN) & EXT_02)== 0))) {
				PWM_Out(temspd, dir);
			}
			else
				PWM_Out(0, 0);
		  }
		  //else
			//PWM_Out(0, 0);
   		
    	/*PID算法计算增量*/
	   		
			
	}
	}
	
}


/**********************************************************
                      屏幕控制任务
***********************************************************/
void TasK_LCD(void *pdata)
{
	uint8 err;
	char str[8];
	uint8 spd= 50, dir= 1, run= 0;

	pdata= pdata;
	
	/* 电机控制端口和PWM端口设置 */
	PINSEL0&=~ (3 << 16);
	PINSEL0|=  (2 << 16);
	PINSEL1&=~((3 <<  2) | (3 <<  4) | (3 <<  6));
	IO0DIR |= ((1 << 17) | (1 << 18) | (1 << 19));
	IO0CLR  =  (1 << 17);
	PWMMCR  = 2;
	PWMPCR  = 1 << 12;
			
	LCD_Init(); // LCD初始化
	LCD_SetMode(LCD_MODE_CLEAR); // 清屏
	
	while(1)
	{
		OSSemPend(SEM_UPDATE, 0, &err); // 等待看门狗信号量
		//功能：申请一个信号量。
		//任务在无法获得信号量时会调用OS_EventTaskWait()挂起，再调用OSSched()进行任务切换。
		//在超时返回时,调用OS_EventTo（）将任务置为就绪.
		
		if(control == 1)	
		{
			LCD_SetMode(LCD_MODE_TEXT);  // 写字符
			LCD_TextOut(0, 0, strtmp);

			/*LCD显示字符*/
			LCD_TextOut(2, 0, "Control:");
			LCD_TextOut(0, 1, "+/- SPD:");
			LCD_TextOut(0, 2, "ESC DIR:");
			LCD_TextOut(0, 3, "OK  RUN:");

			/*实现INC、DEC、ESC、OK键的功能*/
			if((~IO0PIN) & KEY_INC)
				if(++spd> 99)
					spd= 99;
			if((~IO0PIN) & KEY_DEC)
				if(--spd< 1)
					spd= 1;
			if((~IO0PIN) & KEY_ESC)
				dir= 1- dir;
			if((~IO0PIN) & KEY_OK )
				run= 1- run;
			
			sprintf(str, " %02d", spd);
			LCD_TextOut(4, 1, str); //显示速度
			
			/*根据电机方向和运行与否全局变量在LCD屏上显示相应字符*/
			if(dir)
				LCD_TextOut(4, 2, "RIGHT");
			else
				LCD_TextOut(4, 2, "LEFT ");
			if(run)
				LCD_TextOut(4, 3, "GOING");
			else
				LCD_TextOut(4, 3, "STOP ");
			
			/*传递电机运行速度与方向给电机驱动函数*/
			if(run)
				PWM_Out(spd, dir);
			else
				PWM_Out(0, 0);
			Sleep(30);
			I2C_FeedDog(); // 硬件看门狗
		}
		
		/*???AUTO??????????AUTO??*/
		if(control == 0) 
		{
			LCD_SetMode(LCD_MODE_CLEAR);
			Delay(1000);
			LCD_SetMode(LCD_MODE_TEXT);
			LCD_TextOut(0, 0, strtmp);

			sprintf(str, "%d", temspd);
			LCD_TextOut(1, 1, "SPD:");
			LCD_TextOut(4, 1, str);
			
			LCD_TextOut(1, 2, "DIR:");
			if(dir)
				LCD_TextOut(4, 2, "RIGHT");
			else
				LCD_TextOut(4, 2, "LEFT ");
			
			LCD_TextOut(1, 3, "ERR:");
			sprintf(str, "%d", canout);
			LCD_TextOut(4, 3, str);
		}
		OSTimeDlyHMSM(0, 0, 0, 20);
	}
}


void TaskStart(void *pdata)
{
	pdata = pdata;
	TargetResetInit(); //必须在板级初始化之前
	BSP_init(); //板级支持包

	LCD_Init(); // LCD初始化
	I2C_Init(); // I2C初始化


	PINSEL0&= ~((3 << 8) | (3 << 10) | (3 << 22) | (3 << 24));
	PINSEL1&= ~ (3 << 0);
	IO0DIR |=   LED_AUTO;
	IO0DIR &= ~(KEY_ESC | KEY_INC | KEY_DEC | KEY_OK);

	OSTaskCreate(TasK_I2C, (void *)0, &StacK_I2C[TASK_STK_SIZE - 1],  5);
	OSTaskCreate(TasK_MID, (void *)0, &StacK_MID[TASK_STK_SIZE - 1], 10);
	OSTaskCreate(TasK_KEY, (void *)0, &StacK_KEY[TASK_STK_SIZE - 1], 15);
	OSTaskCreate(TasK_LCD, (void *)0, &StacK_LCD[TASK_STK_SIZE - 1], 20);
	OSTaskCreate(TasK_CAN, (void *)0, &StacK_CAN[TASK_STK_SIZE - 1], 25);
	OSTaskCreate(TasK_PWM, (void *)0, &StacK_PWM[TASK_STK_SIZE - 1], 30);

	OSTaskDel(0);
}


/*******************************************************************
                             main函数
********************************************************************/

int main(void)
{	
	OSInit(); // 操作系统初始化

	OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);
	OSStart();    // 开始系统任务调度
	
	return 0;
}
