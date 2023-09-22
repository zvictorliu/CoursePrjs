/************************************************************************
 *                           Copyrights (C) 2007
 *-----------------------------------------------------------------------
 * Descriptions:   用Auto\Center\Manual键盘控制Auto\Center\Manual灯的亮灭
 * Attention   :                      无
 * Created By  :                    Kngboy
 * Created Date:                  2007-09-12
 ************************************************************************/

/************************************************************************
 *		P0.6    -   KEY CENT
 *		P0.7    -   KEY AUTO
 *		P0.10   -   KEY MANU
 *		P0.14   -   LED MANU
 *		P0.15   -   LED CENT
 *		P0.16   -   LED AUTO
 ************************************************************************/

#include "config.h"

#define		KEY_CENT		(1 << 6 )
#define		KEY_AUTO		(1 << 7 )
#define		KEY_MANU		(1 << 10)
#define		LED_MANU		(1 << 14)
#define		LED_CENT		(1 << 15)
#define		LED_AUTO		(1 << 16)

int main(void)
{
	unsigned char flag = 1;		// 避免statement is unreachable的警告

	/* 定义Auto, Center, Manual灯和按钮的端口 */
	PINSEL0&= ~((3 << 12) | (3 << 14) | (3 << 20) | (3 << 28) | ((uint32)3 << 30));
	PINSEL1&= ~ (3 << 0);
	IO0DIR |=   LED_AUTO | LED_MANU | LED_CENT;
	IO0DIR &= ~(KEY_AUTO | KEY_MANU | KEY_CENT);
	
	I2C_Init(); // I2C初始化
	while(flag)
	{
		if(IO0PIN & KEY_AUTO)
			IO0SET= LED_AUTO;
		else
			IO0CLR= LED_AUTO;
		
		if(IO0PIN & KEY_MANU)
			IO0SET= LED_MANU;
		else
			IO0CLR= LED_MANU;
		
		if(IO0PIN & KEY_CENT)
			IO0SET= LED_CENT;
		else
			IO0CLR= LED_CENT;
		
		I2C_FeedDog(); // 喂狗操作
	}

	return 0;
}
