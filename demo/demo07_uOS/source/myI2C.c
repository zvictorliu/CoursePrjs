#include "config.h"

/**************************************************
 * Description :             ����ʱ����
 * Parameters  :            dly - ��ʱʱ��
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
 * Description :             ����ʱ����
 * Parameters  :            dly - ��ʱʱ��
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
 * Description :            I2C�˿ڳ�ʼ��
 * Parameters  :                 ��
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_Init(void)
{
	PINSEL0&= ~((3 << 4) | (3 << 6));
	IO0DIR |= I2C_CLK | I2C_DAT;
}

/**************************************************
 * Description :          Ӳ�����Ź�ι������
 * Parameters  :                 ��
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
