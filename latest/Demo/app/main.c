#include "includes.h"
#include "OS_CPU.h"
#include "bsp.h"

#include "config.h"
//#include "target.h"

/*�˿ڶ���*/
#define	    KEY_OK		    (1 << 4 ) //OK�������Ƶ����ֹ
#define	    KEY_ESC		    (1 << 5 ) //ESC�������Ƶ����ת����
#define	    KEY_CENT	    (1 << 6 ) //CENT��������CENT��
#define     KEY_AUTO	    (1 << 7 ) //AUTO��������Զ���ƫ
#define	    KEY_MANU	    (1 << 10) //MANU��������ֶ���ƫ
#define	    KEY_DEC		    (1 << 11) //DEC������С��������ٶ�
#define	    KEY_INC	        (1 << 12) //INC���������������ٶ�

#define     LED_MANU		(1 << 14) //MANU��
#define     LED_CENT		(1 << 15) //CENT��
#define     LED_AUTO		(1 << 16) //AUTO��
#define     LED_ALARM   (1 << 13)//ALARM��
#define     ADC_PULSE 		(1 << 8 ) // ������ƵĶ˿�
#define     ADC_EN    		(1 << 17)
#define     ADC_MODE 		(1 << 18)
#define     ADC_DIR   		(1 << 19)

#define		TASK_STK_SIZE		128

OS_STK		TaskStartStk[TASK_STK_SIZE];

void TaskStart(void *data);

/*��������Ķ�ջ�ռ�*/
OS_STK	StacK_I2C[128]; //���Ź���������
OS_STK  StacK_CAN[128]; //CAN��������
OS_STK	StacK_KEY[128]; //���񰴼���Ϣ����
OS_STK	StacK_MID[128]; //���̴�������
OS_STK	StacK_PWM[128]; //PID�㷨�����������
OS_STK	StacK_LCD[128]; //��Ļ��ʾ����

void PWM_Out(uint16 spd, uint8 dir);

/*��������֮��ͨѶ�ź�*/
OS_EVENT *SEM_UPDATE;
OS_EVENT *MBOX_KEYDN;
OS_EVENT *SEM_CAN;
OS_EVENT *SEM_AUTO;


/*���峣��*/
//K=Kp;Kt=Kp*Ts/Ti;Kd=Kp*Td/Ts; 
#define  	K              0.45//�����Ŵ�ϵ��,��ʼֵ0.3125
#define  	T              1.9556  //Ts/Ti
#define  	TDs            1.564   //Td/Ts
#define  	Setpoint       125 //����е�λ��

#define		EXT_01		(1 << 21)
#define		EXT_02		(1 << 20)

#define		GetRelPos(dat)	(((dat) & (1 << 12)) ? (-(((dat) >> 00) & 0xFFF)) : (((dat) >> 00) & 0xFFF))

/*����ȫ�ֱ���*/
uint8 control = 1; //�Զ���ƫ���Ʊ���
uint8 run = 1,dir = 0; //������п��Ʊ���
uint8 cent=0;
uint8 u8CntKEY = 0; //������Ϣ����������Ʊ���
uint8 u8CntI2C = 0; //���Ź�������Ʊ���
//uint8 canout = 0; //CAN���������ݴ����
int16 canout= 0;
uint16 U1=0;
int16 temspd = 0; //����ȫ�ֱ������Ƴ�ʼ���У�

char  strtmp[8]; //����LCD�������ʱ�õ��ַ����������
char  strKey[8]; //���ڴ��������Ϣʱ�õ��ַ����������


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

    /* ����ϵͳ������ʱ�� */
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
    
    /* ���ô洢������ģ�� */
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
    
    /* ��ʼ��VIC */
    VICIntEnClr = 0xffffffff;
    VICVectAddr = 0;
    VICIntSelect = 0;

    /* ����Լ��Ĵ��� */

}



/***********************************************************
                      ���Ź���������
                      
describe���������У�ÿ��һ��ʱ������Ź��źţ�������ļ�����
          �����������������������һ����λ�źš�
************************************************************/
void TasK_I2C(void *pdata)
{
	uint8 i= 0;
	pdata= pdata;
	
	SEM_UPDATE= OSSemCreate(1); // �����ź���
	
	while(1)
	{
		I2C_FeedDog(); // Ӳ�����Ź�
		if(++i>= 10) {
			i= 0;
			u8CntI2C++;
			OSSemPost(SEM_UPDATE); // �����ź���
		}
		OSTimeDlyHMSM(0, 0, 0, 5); // ������ʱ�ȴ�
	}
}



/**********************************************************
                        CAN��������
                        
describe���������ֵ����ΪPID�㷨�����룬���ܴ�������
***********************************************************/
void TasK_CAN(void* pdata)
{
	uint8 err= 0;
	pdata=pdata;
	err= err;
	
	SEM_CAN= OSSemCreate(1); // �����ź���
	
   	InitCAN(CAN1);// CAN��ʼ��
	ConfigAFReg();// ���ý��տ���

	while(1)
	{
		/* �����жϷ�ʽ��������, ����յ�����, �����ڴ˴����м�� */
		while(!((CANRcvCyBufApp[CAN1].ReadPoint!= CANRcvCyBufApp[CAN1].WritePoint) || CANRcvCyBufApp[CAN1].FullFlag)) 
			OSTimeDlyHMSM(0, 0, 0, 5);
		canout= GetRelPos(CANRcvCyBufApp[CAN1].RcvBuf[CANRcvCyBufApp[CAN1].ReadPoint].RDA.Word);
		//can���ߴ�����������64λ�ģ������е�32λ��������10λ��ȡ������11λ���ݸ���ȫ�ֱ���canout
		
		OSSemPost(SEM_CAN); // �����ź���
		//����һ���ź��������������ȴ�������OS_EventTaskRdy()��������Ϊ���������ȡ�
		
		if(++CANRcvCyBufApp[CAN1].ReadPoint>= USE_CAN_cycRCV_BUF_SIZE)
			CANRcvCyBufApp[CAN1].ReadPoint= 0;
		CANRcvCyBufApp[CAN1].FullFlag= 0;
	}
}



/**********************************************************
                       ���̴�������
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
		Key= OSMboxPend(MBOX_KEYDN, 0, &err); // �ȴ�����Task_KEY��������Ϣ
				switch(*Key) 
		{
			case KEY_CENT:
			
			IO0CLR=LED_CENT;
	
			//���г���

		while(flag)
   {
   while((~IO1PIN) & EXT_01)//û������
   {
     PWM_Out(60, 1);//�ƶ�������
   }
   while((~IO1PIN) & EXT_02)//û������
   {
     PWM_Out(60, 0);step++;//�ƶ������ҿ�ʼ����
   }
   step = step/2;
	 step += 33000;
   while(step!=0)
   {
     PWM_Out(60, 1);//�����ٶ��뷽��
     step--; 
     flag = 0;    
   }
	 PWM_Out(0, 0);
  }
	 flag = 1;
	 IO0SET=LED_CENT;//��������
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
                        ������������
***********************************************************/
void TasK_KEY(void *pdata)
{
	uint8  i= 0;
	uint32 Key= 0;
	pdata= pdata;

	MBOX_KEYDN= OSMboxCreate(&Key);// ����������Ϣ��׼���͸�Task_MID
	
	I2C_Init(); //I2C��ʼ��
	
	/*�����͵ƵĶ˿ڶ���*/	
	PINSEL0&=~((3<<12) | (3<<14) | (3<<20) | (3<<28) | ((uint32)3<<30));
	PINSEL1&=~(3<<0);
	IO0DIR |= LED_AUTO | LED_MANU | LED_CENT|LED_ALARM;//set LED AS out
	IO0DIR &= ~(KEY_AUTO | KEY_MANU | KEY_CENT);//set KEY AS in
  
	while(1)
	{
	
		while((Key= (~IO0PIN) & (KEY_AUTO | KEY_CENT | KEY_MANU))== 0)
					OSTimeDlyHMSM(0, 0, 0, 50);
					
		OSMboxPost(MBOX_KEYDN, (void *)&Key); // ����������Ϣ��Task_MID

		if(++i>= 10)
		{
			i= 0;
			u8CntKEY++;
		}
		
		OSTimeDlyHMSM(0, 0, 0, 15);
		I2C_FeedDog();//ι��
	}
}



/**********************************************************
                       �����������
***********************************************************/
/*�����������*/
void PWM_Out(uint16 spd, uint8 dir) 
{
	temspd=0;//���ó�ʼ�ٶȣ��õ����ʼ״̬Ϊͣ��
	//���߽����
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
	
	PWMMR0= Fpclk/ (spd*10);//���ö�ʱ����ʱ��,ͨ��ƥ��ʱ�������ü���ֵ������PWM������
	PWMMR4= PWMMR0/ 2;// 50%ռ�ձ�
	PWMLER= (1 << 0) | (1 << 4);// PWM0��PWM4ƥ������
	PWMTCR= 9;// ����PWM���
}


void TasK_PWM(void* pdata)
{
	//PID�㷨
	uint8 err = 0;
	uint8 dir=0;
	int e[3]= {0};
	int outn = 0;
	
//	FP32 q0=K*(1+T),q1=-K,U=0; //����q0��q1������u0����ֵ
	FP32 q0=K*(1+T+TDs);
	FP32 q1=-K*(1+2*TDs);
	FP32 q2=K*TDs;
	FP32 U=0; //����q0��q1��q2������u0����ֵ
	
	pdata=pdata; 
	  while(1)
	 {
		OSSemPend(SEM_CAN,0, &err);//���ܣ�����һ���ź�����
		//�������޷�����ź���ʱ�����OS_EventTaskWait()�����ٵ���OSSched()���������л���
		//�ڳ�ʱ����ʱ,����OS_EventTo������������Ϊ����.
		
		temspd=50;
		
		/* �����ǵ�����ƶ˿ں�PWM�˿����� */
		PINSEL0&=~ (3 << 16); // ��PWM�˿�����Ϊ��ͨ��IO��
		PINSEL0|=  (2 << 16); // ѡ��PWM4
		PINSEL1&=~((3 <<  2) | (3 <<  4) | (3 <<  6));// ����Ϊ������ƿ�17��18��19
		PINSEL2 &= ~0x08;
		IO0DIR |=(ADC_EN | ADC_MODE | ADC_DIR);//���
		IO0CLR  =  (1 << 17);//P0.17��0
		PWMMCR  = 2;//reset PWMMCR0
		PWMPCR  = 1 << 12;// enable PM4
		
		e[0]= canout;//����Kʱ�̵�������ֵ
		
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
        e[1]=e[0]; //���ݴ���				
		
		/*���ݵ�������ٶ��뷽��������������*/
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
   		
    	/*PID�㷨��������*/
	   		
			
	}
	}
	
}


/**********************************************************
                      ��Ļ��������
***********************************************************/
void TasK_LCD(void *pdata)
{
	uint8 err;
	char str[8];
	uint8 spd= 50, dir= 1, run= 0;

	pdata= pdata;
	
	/* ������ƶ˿ں�PWM�˿����� */
	PINSEL0&=~ (3 << 16);
	PINSEL0|=  (2 << 16);
	PINSEL1&=~((3 <<  2) | (3 <<  4) | (3 <<  6));
	IO0DIR |= ((1 << 17) | (1 << 18) | (1 << 19));
	IO0CLR  =  (1 << 17);
	PWMMCR  = 2;
	PWMPCR  = 1 << 12;
			
	LCD_Init(); // LCD��ʼ��
	LCD_SetMode(LCD_MODE_CLEAR); // ����
	
	while(1)
	{
		OSSemPend(SEM_UPDATE, 0, &err); // �ȴ����Ź��ź���
		//���ܣ�����һ���ź�����
		//�������޷�����ź���ʱ�����OS_EventTaskWait()�����ٵ���OSSched()���������л���
		//�ڳ�ʱ����ʱ,����OS_EventTo������������Ϊ����.
		
		if(control == 1)	
		{
			LCD_SetMode(LCD_MODE_TEXT);  // д�ַ�
			LCD_TextOut(0, 0, strtmp);

			/*LCD��ʾ�ַ�*/
			LCD_TextOut(2, 0, "Control:");
			LCD_TextOut(0, 1, "+/- SPD:");
			LCD_TextOut(0, 2, "ESC DIR:");
			LCD_TextOut(0, 3, "OK  RUN:");

			/*ʵ��INC��DEC��ESC��OK���Ĺ���*/
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
			LCD_TextOut(4, 1, str); //��ʾ�ٶ�
			
			/*���ݵ��������������ȫ�ֱ�����LCD������ʾ��Ӧ�ַ�*/
			if(dir)
				LCD_TextOut(4, 2, "RIGHT");
			else
				LCD_TextOut(4, 2, "LEFT ");
			if(run)
				LCD_TextOut(4, 3, "GOING");
			else
				LCD_TextOut(4, 3, "STOP ");
			
			/*���ݵ�������ٶ��뷽��������������*/
			if(run)
				PWM_Out(spd, dir);
			else
				PWM_Out(0, 0);
			Sleep(30);
			I2C_FeedDog(); // Ӳ�����Ź�
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
	TargetResetInit(); //�����ڰ弶��ʼ��֮ǰ
	BSP_init(); //�弶֧�ְ�

	LCD_Init(); // LCD��ʼ��
	I2C_Init(); // I2C��ʼ��


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
                             main����
********************************************************************/

int main(void)
{	
	OSInit(); // ����ϵͳ��ʼ��

	OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);
	OSStart();    // ��ʼϵͳ�������
	
	return 0;
}
