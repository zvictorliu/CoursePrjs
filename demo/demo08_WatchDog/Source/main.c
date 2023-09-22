/************************************************************************
 *                           Copyrights (C) 2007
 *-----------------------------------------------------------------------
 * Descriptions:   ����LCD��Һ������ͬʱ��ʾSJTU��ͼ�κ��ַ�
 * Attention   :                      ��
 * Created By  :                    Kngboy
 * Created Date:                  2007-09-12
 ************************************************************************/

#include "config.h"

#define		KEY_OK			(1 << 4 )

int main(void)
{
	unsigned char flag = 1;		// ����statement is unreachable�ľ���

	uint8 i= 0, j= 0;
	char str[8];
	LCD_Init(); // LCD��ʼ��
	I2C_Init(); // I2C��ʼ��
	
	LCD_SetMode(LCD_MODE_CLEAR); // ����
	
	LCD_SetMode(LCD_MODE_HIDE);  // ������
	LCD_DrawOut();               // ��ͼ
	LCD_SetMode(LCD_MODE_SHOW);  // ����ͼ
	
	LCD_SetMode(LCD_MODE_TEXT);  // д�ַ�
	LCD_TextOut(0, 3, "PRESS OK TO KILL!");
	LCD_TextOut(6, 2, " 0");
	
	PINSEL0&= ~(3 << 8);
	IO0DIR &= ~(KEY_OK);
	/* ���ÿ��Ź��ļ�ʱ��ģʽ */
	WDTC  = 0x500000;
	WDMOD = 0x03;
	/* ��һ��ι�����Ź������� */
	WDFEED= 0xAA;
	WDFEED= 0x55;
	
	while(flag)
	{
		/* OK��û�а���, ����ι�������ֵ����Ĳ��� */
		if(((~IO0PIN) & KEY_OK)== 0) {
			if(++i>= 100) {
				i= 0;
				j++;
			}
			sprintf(str, " %-3d", j);
			LCD_TextOut(6, 2, str);
			
			WDFEED= 0xAA;
			WDFEED= 0x55;
			LCD_TextOut(6, 0, "    ");
		}
		else
			LCD_TextOut(6, 0, " OK!");
		
		Delay(100);
		I2C_FeedDog(); // Ӳ�����Ź�
	}
	
	return 0;
}
