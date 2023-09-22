/************************************************************************
 *                           Copyrights (C) 2007
 *-----------------------------------------------------------------------
 * Descriptions:   ����LCD��Һ������ͬʱ��ʾSJTU��ͼ�κ��ַ�
 * Attention   :                      ��
 * Created By  :                    Kngboy
 * Created Date:                  2007-09-12
 ************************************************************************/

#include "config.h"

int main(void)
{
	unsigned char flag = 1;		// ����statement is unreachable�ľ���

	uint8  i= 0;
	uint16 j= 0;
	LCD_Init(); // LCD��ʼ��
	I2C_Init(); // I2C��ʼ��
	
	LCD_SetMode(LCD_MODE_CLEAR);// ����
	
	LCD_SetMode(LCD_MODE_HIDE); // ������
	LCD_DrawOut();              // ��ͼ
	LCD_SetMode(LCD_MODE_SHOW); // ����ͼ
	
	LCD_SetMode(LCD_MODE_TEXT); // д�ַ�
	LCD_TextOut(4, 0, "��ˮ˼Դ");
	LCD_TextOut(4, 1, " ..IE.. ");
	LCD_TextOut(4, 2, " Kngboy ");
	LCD_TextOut(4, 3, "20070912");
	
	while(flag)
	{
		if(++j>= 1000) {
			j= 0;
			i= 1- i;
		}
		
		if(i== 1)
			LCD_TextOut(5, 1, ".IE.");
		else
			LCD_TextOut(5, 1, "    ");
		
		I2C_FeedDog(); // Ӳ�����Ź�
	}
	
	return 0;
}
