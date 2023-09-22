/************************************************************************
 *                           Copyrights (C) 2007
 *-----------------------------------------------------------------------
 * Descriptions:   ����LCD��Һ������ͬʱ��ʾSJTU��ͼ�κ��ַ�
 * Attention   :                      ��
 * Created By  :                    Kngboy
 * Created Date:                  2007-09-12
 ************************************************************************/

#include "config.h"

uint8 hour= 10, minute= 10, second= 10;

/**************************************************
 * Description :          Timer0�жϷ�����
 * Parameters  :                 ��
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void __irq IRQ_Timer0(void)
{
	if(++second>= 60) {
		second= 0;
		if(++minute>= 60) {
			minute= 0;
			if(++hour>= 24)
				hour= 0;
		}
	}
	
	T0IR= 0x01;        // ����жϱ�־
	VICVectAddr= 0x00; // �жϷ���
}

int main(void)
{
	unsigned char flag = 1;		// ����statement is unreachable�ľ���

	char str[10] = {0};
	LCD_Init(); // LCD��ʼ��
	I2C_Init(); // I2C��ʼ��

	/* ����Timer0�Ĳ��� */
	T0TC = 0;
	T0PR = 0;
	T0MCR= 0x03;
	T0MR0= Fpclk;
	T0TCR= 0x01;
	
	/* �����ж������Ĳ��� */
	VICIntSelect= 0x00;
	VICVectCntl0= 0x20 | 0x04;
	VICVectAddr0= (uint32)IRQ_Timer0;
	VICIntEnable= 1 << 0x04;
	
	LCD_SetMode(LCD_MODE_CLEAR); // ����
	
	LCD_SetMode(LCD_MODE_HIDE);  // ������
	LCD_DrawOut();               // ��ͼ
	LCD_SetMode(LCD_MODE_SHOW);  // ����ͼ
	
	LCD_SetMode(LCD_MODE_TEXT);  // д�ַ�
	LCD_TextOut(1, 0, "One World,");
	LCD_TextOut(3, 1, "One Dream.");
	LCD_TextOut(2, 2, "07/09/21");
	
	while(flag)
	{
		sprintf(str, "%02d:%02d:%02d", hour, minute, second);
		LCD_TextOut(2, 3, str);
		I2C_FeedDog(); // Ӳ�����Ź�
	}
	
	return 0;
}
