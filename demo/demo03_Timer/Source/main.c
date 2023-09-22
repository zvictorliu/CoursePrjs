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

	char str[10] = {0};
	LCD_Init(); // LCD初始化
	I2C_Init(); // I2C初始化

	/* 设置Timer0的参数 */
	T0TC = 0;
	T0PR = 0;
	T0MCR= 0x03;
	T0MR0= Fpclk;
	T0TCR= 0x01;
	
	/* 设置中断向量的参数 */
	VICIntSelect= 0x00;
	VICVectCntl0= 0x20 | 0x04;
	VICVectAddr0= (uint32)IRQ_Timer0;
	VICIntEnable= 1 << 0x04;
	
	LCD_SetMode(LCD_MODE_CLEAR); // 清屏
	
	LCD_SetMode(LCD_MODE_HIDE);  // 先隐藏
	LCD_DrawOut();               // 画图
	LCD_SetMode(LCD_MODE_SHOW);  // 显现图
	
	LCD_SetMode(LCD_MODE_TEXT);  // 写字符
	LCD_TextOut(1, 0, "One World,");
	LCD_TextOut(3, 1, "One Dream.");
	LCD_TextOut(2, 2, "07/09/21");
	
	while(flag)
	{
		sprintf(str, "%02d:%02d:%02d", hour, minute, second);
		LCD_TextOut(2, 3, str);
		I2C_FeedDog(); // 硬件看门狗
	}
	
	return 0;
}
