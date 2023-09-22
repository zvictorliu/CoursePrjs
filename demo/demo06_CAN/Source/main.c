/************************************************************************
 *                           Copyrights (C) 2007
 *-----------------------------------------------------------------------
 * Descriptions:   ����LCD��Һ������ͬʱ��ʾSJTU��ͼ�κ��ַ�
 * Attention   :                      ��
 * Created By  :                    Kngboy
 * Created Date:                  2007-09-12
 ************************************************************************/

#include "config.h"

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

int main(void)
{
	unsigned char flag = 1;		// ����statement is unreachable�ľ���

	uint16 i= 0;
	char str[8];

	TargetResetInit();

	LCD_Init();   // LCD��ʼ��
	I2C_Init();   // I2C��ʼ��
   	InitCAN(CAN1);// CAN��ʼ��
	ConfigAFReg();// ���ý��տ���
	
	LCD_SetMode(LCD_MODE_CLEAR);
	LCD_SetMode(LCD_MODE_TEXT);
	LCD_TextOut(2, 0, "Can Bus");
	LCD_TextOut(1, 1, "H:00000000");
	LCD_TextOut(1, 2, "L:00000000");
	LCD_TextOut(2, 3, "- 0000 -");
	
	while(flag)
	{
		/* �����жϷ�ʽ��������, ����յ�����, �����ڴ˴����м�� */
		if((CANRcvCyBufApp[CAN1].ReadPoint!= CANRcvCyBufApp[CAN1].WritePoint) || CANRcvCyBufApp[CAN1].FullFlag) {
			sprintf(str, "%08X", (unsigned int)(CANRcvCyBufApp[CAN1].RcvBuf[CANRcvCyBufApp[CAN1].ReadPoint].RDB.Word));
			LCD_TextOut(2, 1, str);
			sprintf(str, "%08X", (unsigned int)(CANRcvCyBufApp[CAN1].RcvBuf[CANRcvCyBufApp[CAN1].ReadPoint].RDA.Word));
			LCD_TextOut(2, 2, str);

			if(++i >= 10000)
				i = 0;
			sprintf(str, "%04d", i);
			LCD_TextOut(3, 3, str);
			
			if(++CANRcvCyBufApp[CAN1].ReadPoint>= USE_CAN_cycRCV_BUF_SIZE)
				CANRcvCyBufApp[CAN1].ReadPoint= 0;
			CANRcvCyBufApp[CAN1].FullFlag= 0;
		}
		
		I2C_FeedDog(); // Ӳ�����Ź�
	}
	
	return 0;
}
