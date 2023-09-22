#include "config.h"

/**************************************************
 * Description :             短延时函数
 * Parameters  :            dly - 延时时间
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void Delay(uint32 dly)
{
	uint16 i;
	for(; dly> 0; dly--)
		for(i= 0; i< 10; i++);
}

/**************************************************
 * Description :             长延时函数
 * Parameters  :            dly - 延时时间
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void Sleep(uint32 dly)
{
	uint16 i;
	for(; dly> 0; dly--)
		for(i= 0; i< 40000; i++);
}

/**************************************************
 * Description :            I2C端口初始化
 * Parameters  :                 无
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_Init(void)
{
	PINSEL0&= ~((3 << 4) | (3 << 6));
	IO0DIR |= I2C_CLK | I2C_DAT;
}

/**************************************************
 * Description :          硬件看门狗喂狗函数
 * Parameters  :                 无
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_FeedDog(void)
{
	IO0SET  = I2C_DAT;
	Delay(10);
	IO0CLR  = I2C_DAT;
	Delay(10);
}
