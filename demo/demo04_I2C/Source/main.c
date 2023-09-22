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

	uint8  i= 0;
	char str[16];
	
	LCD_Init(); // LCD��ʼ��
	I2C_Init(); // I2C��ʼ��
	
	LCD_SetMode(LCD_MODE_CLEAR); // ����
	
	LCD_SetMode(LCD_MODE_HIDE);  // ������
	LCD_DrawOut();               // ��ͼ
	LCD_SetMode(LCD_MODE_SHOW);  // ����ͼ
	
	LCD_SetMode(LCD_MODE_TEXT);  // д�ַ�
	LCD_TextOut(2, 0, "�������");
	
	i= I2C_ReadUint8(0x01);      // ��ȡ����
	sprintf(str, "NO.1:%-3d", i);
	LCD_TextOut(2, 1, str);
	
	i= I2C_ReadUint8(0x00);
	sprintf(str, "NO.2:%-3d", i);
	LCD_TextOut(2, 2, str);
	I2C_WriteUint8(0x01, i);     // д������
	
	while(flag)
	{
		sprintf(str, "NO.3:%-3d", ++i);
		LCD_TextOut(2, 3, str);
		I2C_WriteUint8(0x00, i);
		Sleep(20);
	}
	
	return 0;
}
