/************************************************************************
 *                           Copyrights (C) 2007
 *-----------------------------------------------------------------------
 * Descriptions:   用在LCD的液晶屏上同时显示SJTU的图形和字符
 * Attention   :                      无
 * Created By  :                    Kngboy
 * Created Date:                  2007-09-12
 ************************************************************************/

#include "config.h"

int main(void)
{
	unsigned char flag = 1;		// 避免statement is unreachable的警告

	uint8  i= 0;
	uint16 j= 0;
	LCD_Init(); // LCD初始化
	I2C_Init(); // I2C初始化
	
	LCD_SetMode(LCD_MODE_CLEAR);// 清屏
	
	LCD_SetMode(LCD_MODE_HIDE); // 先隐藏
	LCD_DrawOut();              // 画图
	LCD_SetMode(LCD_MODE_SHOW); // 显现图
	
	LCD_SetMode(LCD_MODE_TEXT); // 写字符
	LCD_TextOut(4, 0, "饮水思源");
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
		
		I2C_FeedDog(); // 硬件看门狗
	}
	
	return 0;
}
