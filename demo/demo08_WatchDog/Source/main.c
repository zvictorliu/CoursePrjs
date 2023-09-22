/************************************************************************
 *                           Copyrights (C) 2007
 *-----------------------------------------------------------------------
 * Descriptions:   用在LCD的液晶屏上同时显示SJTU的图形和字符
 * Attention   :                      无
 * Created By  :                    Kngboy
 * Created Date:                  2007-09-12
 ************************************************************************/

#include "config.h"

#define		KEY_OK			(1 << 4 )

int main(void)
{
	unsigned char flag = 1;		// 避免statement is unreachable的警告

	uint8 i= 0, j= 0;
	char str[8];
	LCD_Init(); // LCD初始化
	I2C_Init(); // I2C初始化
	
	LCD_SetMode(LCD_MODE_CLEAR); // 清屏
	
	LCD_SetMode(LCD_MODE_HIDE);  // 先隐藏
	LCD_DrawOut();               // 画图
	LCD_SetMode(LCD_MODE_SHOW);  // 显现图
	
	LCD_SetMode(LCD_MODE_TEXT);  // 写字符
	LCD_TextOut(0, 3, "PRESS OK TO KILL!");
	LCD_TextOut(6, 2, " 0");
	
	PINSEL0&= ~(3 << 8);
	IO0DIR &= ~(KEY_OK);
	/* 设置看门狗的计时和模式 */
	WDTC  = 0x500000;
	WDMOD = 0x03;
	/* 第一次喂狗看门狗才启动 */
	WDFEED= 0xAA;
	WDFEED= 0x55;
	
	while(flag)
	{
		/* OK键没有按下, 进行喂狗和数字递增的操作 */
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
		I2C_FeedDog(); // 硬件看门狗
	}
	
	return 0;
}
