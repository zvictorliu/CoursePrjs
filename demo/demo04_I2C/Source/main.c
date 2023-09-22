/************************************************************************
 *                           Copyrights (C) 2007
 *-----------------------------------------------------------------------
 * Descriptions:   用在LCD的液晶屏上同时显示SJTU的图形和字符
 * Attention   :                      无
 * Created By  :                    Kngboy
 * Created Date:                  2007-09-12
 ************************************************************************/

#include "config.h"

uint8 hour= 10, minute= 10, second= 10;

/**************************************************
 * Description :          Timer0中断服务函数
 * Parameters  :                 无
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
	
	T0IR= 0x01;        // 清除中断标志
	VICVectAddr= 0x00; // 中断返回
}

int main(void)
{
	unsigned char flag = 1;		// 避免statement is unreachable的警告

	uint8  i= 0;
	char str[16];
	
	LCD_Init(); // LCD初始化
	I2C_Init(); // I2C初始化
	
	LCD_SetMode(LCD_MODE_CLEAR); // 清屏
	
	LCD_SetMode(LCD_MODE_HIDE);  // 先隐藏
	LCD_DrawOut();               // 画图
	LCD_SetMode(LCD_MODE_SHOW);  // 显现图
	
	LCD_SetMode(LCD_MODE_TEXT);  // 写字符
	LCD_TextOut(2, 0, "掉电记忆");
	
	i= I2C_ReadUint8(0x01);      // 读取数据
	sprintf(str, "NO.1:%-3d", i);
	LCD_TextOut(2, 1, str);
	
	i= I2C_ReadUint8(0x00);
	sprintf(str, "NO.2:%-3d", i);
	LCD_TextOut(2, 2, str);
	I2C_WriteUint8(0x01, i);     // 写入数据
	
	while(flag)
	{
		sprintf(str, "NO.3:%-3d", ++i);
		LCD_TextOut(2, 3, str);
		I2C_WriteUint8(0x00, i);
		Sleep(20);
	}
	
	return 0;
}
