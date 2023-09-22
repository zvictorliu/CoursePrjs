/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			target.c
** Last modified Date:	2004-09-17
** Last Version:		1.0
** Descriptions:		header file of the specific codes for LPC2100 target boards
**						Every project should include a copy of this file, user may modify it as needed
**------------------------------------------------------------------------------------------------------
** Created by:			Chenmingji
** Created date:		2004-02-02
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			Chenmingji
** Modified date:		2004-09-17
** Version:				1.01
** Descriptions:		Renewed the template, added more compiler supports 
**
**------------------------------------------------------------------------------------------------------
** Modified by: 
** Modified date:
** Version:	
** Descriptions: 
**
********************************************************************************************************/

#define IN_TARGET
#include "config.h"
#include "os_cfg.h"  
#include "OS_CPU.h"
#include "includes.h"  


OS_CPU_SR cpu_sr = 0;

/*********************************************************************************************************
** Function name:			IRQ_Exception
**
** Descriptions:			interrupt exceptional handler , change it as needed
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
        void IRQ_Exception(void)
{
    while(1);                   // change it to your code  ��һ���滻Ϊ�Լ��Ĵ���
}

/*********************************************************************************************************
** Function name:			FIQ_Exception
**
** Descriptions:			Fast interrupt exceptional handler , change it as needed
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
        void FIQ_Exception(void)
{
    while(1);                   // change it to your code  ��һ���滻Ϊ�Լ��Ĵ���
}
/*********************************************************************************************************
** Function name:			Timer0_Exception
**
** Descriptions:			Timer0 interrupt service function
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
        void Timer0_Exception(void)
{
    T0IR = 0x01;
    VICVectAddr = 0;            //interrupt close ֪ͨ�жϿ������жϽ���
    OSTimeTick();
}

/*********************************************************************************************************
** Function name:			Timer0Init
**
** Descriptions:			Initialize the Time0
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
        void Timer0Init(void)
{
    T0IR = 0xffffffff;
    T0TC = 0;
    T0TCR = 0x01;
    T0MCR = 0x03;
    T0MR0 = (Fpclk / OS_TICKS_PER_SEC);
 }
/*********************************************************************************************************
** Function name:			VICInit
**
** Descriptions:			Initialize the Interrupt Vevtor Controller
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
        void VICInit(void)
{
    extern void IRQ_Handler(void);
    extern void Timer0_Handler(void);

    VICIntEnClr   = 0xffffffff;
    VICDefVectAddr= (uint32)IRQ_Handler;
	
    VICVectAddr0  = (uint32)Timer0_Handler;
    VICVectCntl0  = (0x20 | 0x04);
    VICIntEnable  = 1 << 4;
    
 }

/*********************************************************************************************************
** Function name:			TargetInit
**
** Descriptions:			Initialize the target board; it is called in a necessary place, change it as 
**							needed
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
        void TargetInit(void)
{
    // CPU_SR_ALLOC();   // 2020 07 10 
	  OS_ENTER_CRITICAL();
    srand((uint32) TargetInit);
    VICInit();
    Timer0Init();
    OS_EXIT_CRITICAL();
}
/*********************************************************************************************************
** Function name:			InitialiseUART0
**
** Descriptions:			Initialize the Uart0
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
        void InitialiseUART0(uint32 bps)
{  	
    uint16 Fdiv;
    
    PINSEL0 = (PINSEL0 & 0xfffffff0) | 0x05;    /* Select the pins for Uart ѡ��ܽ�ΪUART0 */

    U0LCR = 0x80;                               /* Enable to access the frequenc regecter ������ʷ�Ƶ���ӼĴ��� */
    Fdiv = (Fpclk / 16) / bps;                  /* Set the baudrate���ò����� */
    U0DLM = Fdiv / 256;							
	U0DLL = Fdiv % 256;						
    U0LCR = 0x03;                               /* Disable to access the frequenc regecter ��ֹ���ʷ�Ƶ���ӼĴ��� */
                                                /* set to 8,1,n ������Ϊ8,1,n */
	U0IER = 0x00;                               /* Disable interrupt��ֹ�ж� */
    U0FCR = 0x00;                               /* initial FIFO ��ʼ��FIFO */
} 
/*********************************************************************************************************
** Function name:			TargetResetInit
**
** Descriptions:			Initialize the target 
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
//        void TargetResetInit(void)
//{
//#ifdef __DEBUG_RAM    
//    MEMMAP = 0x2;                   //remap
//#endif

//#ifdef __DEBUG_FLASH    
//    MEMMAP = 0x1;                   //remap
//#endif

//#ifdef __IN_CHIP    
//    MEMMAP = 0x1;                   //remap
//#endif

//    PINSEL0 = (PINSEL0 & 0xFFFF0000) | 0x05 | 0x50;

///* ����ϵͳ������ʱ�� */
///* Set system timers for each component */
//    PLLCON = 1;
//#if (Fpclk / (Fcclk / 4)) == 1
//    VPBDIV = 0;
//#endif
//#if (Fpclk / (Fcclk / 4)) == 2
//    VPBDIV = 2;
//#endif
//#if (Fpclk / (Fcclk / 4)) == 4
//    VPBDIV = 1;
//#endif

//#if (Fcco / Fcclk) == 2
//    PLLCFG = ((Fcclk / Fosc) - 1) | (0 << 5);
//#endif
//#if (Fcco / Fcclk) == 4
//    PLLCFG = ((Fcclk / Fosc) - 1) | (1 << 5);
//#endif
//#if (Fcco / Fcclk) == 8
//    PLLCFG = ((Fcclk / Fosc) - 1) | (2 << 5);
//#endif
//#if (Fcco / Fcclk) == 16
//    PLLCFG = ((Fcclk / Fosc) - 1) | (3 << 5);
//#endif
//    PLLFEED = 0xaa;
//    PLLFEED = 0x55;
//    while((PLLSTAT & (1 << 10)) == 0);
//    PLLCON = 3;
//    PLLFEED = 0xaa;
//    PLLFEED = 0x55;

///* ���ô洢������ģ�� */
///* Set memory accelerater module*/
//    MAMCR = 0;
//#if Fcclk < 20000000
//    MAMTIM = 1;
//#else
//#if Fcclk < 40000000
//    MAMTIM = 2;
//#else
//    MAMTIM = 3;
//#endif
//#endif
//    MAMCR = 2;

///* ���ô��п� */
///* initialize UART*/
//    InitialiseUART0(115200);

///* ����ʵʱʱ�� */
///* initialize RTC*/
//    CCR = 1;
//    PREINT = Fpclk / 32768 - 1;
//    PREFRAC = Fpclk - (Fpclk / 32768) * 32768;
//    YEAR = 2003;
//    MONTH = 6;
//    DOM = 2;
//    
///* initialize VIC*/
//    VICIntEnClr = 0xffffffff;
//    VICVectAddr = 0;
//    VICIntSelect = 0;
//    T0IR = 0xffffffff;
//    T0TCR = 0X02;
//}

/*********************************************************************************************************
**                  ����ΪһЩ��ϵͳ��صĿ⺯����ʵ��
**                  ����������ads�Ĳο���������⺯���ֲ�
**                  �û����Ը����Լ���Ҫ���޸�        
********************************************************************************************************/
/*********************************************************************************************************
**                  The implementations for some library functions
**                  For more details, please refer to the ADS compiler handbook and The library 
**					function manual
**                  User could change it as needed       
********************************************************************************************************/

#include "rt_sys.h"
#include "stdio.h"

#pragma import(__use_no_semihosting_swi)

        int __rt_div0(int a)
{
    a = a;
    return 0;
}

        int fputc(int ch,FILE *f)
{
    ch = ch;
    f = f;
    return 0;
}

    int fgetc(FILE *f)
{
    f = f;
    return 0;
}


        int _sys_close(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}

        int _sys_write(FILEHANDLE fh, const unsigned char * buf,
                      unsigned len, int mode)
{
    fh = fh;
    buf = buf;
    len =len;
    mode = mode;
    return 0;
}
        int _sys_read(FILEHANDLE fh, unsigned char * buf,
                     unsigned len, int mode)
{
    fh = fh;
    buf = buf;
    len =len;
    mode = mode;
    
    return 0;
}

       void _ttywrch(int ch)
{
    ch = ch;
}

        int _sys_istty(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}
        int _sys_seek(FILEHANDLE fh, long pos)
{
    fh = fh;
    return 0;
}
        int _sys_ensure(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}

        long _sys_flen(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}
       int _sys_tmpnam(char * name, int sig, unsigned maxlen)
{
    name = name;
    sig = sig;
    maxlen = maxlen;
    return 0;
}

        void _sys_exit(int returncode)
{
    returncode = returncode;
}

        char *_sys_command_string(char * cmd, int len)
{
    cmd = cmd;
    len = len;
    return 0;
}

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
