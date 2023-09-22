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
	PINSEL1&= ~(3 << 21);
	IO0DIR |= I2C_CLK | I2C_DAT | I2C_WP;
}

/**************************************************
 * Description :          �ı�DAT���ߵķ���
 * Parameters  :         isout - 0.IN 1.OUT
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_SwiDir(uint8 isout)
{
	if(isout)
		IO0DIR|=  I2C_DAT;
	else
		IO0DIR&= ~I2C_DAT;
	
	Delay(1);
}

/**************************************************
 * Description :            ���������־
 * Parameters  :                 ��
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_StartBit(void)
{
    IO0SET= I2C_CLK;    Delay(1);
    IO0SET= I2C_DAT;    Delay(1);
    IO0CLR= I2C_DAT;    Delay(1);
    IO0CLR= I2C_CLK;    Delay(1);
}

/**************************************************
 * Description :            ֹͣ�����־
 * Parameters  :                 ��
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_StopBit(void)
{
    IO0CLR= I2C_DAT;    Delay(1);
    IO0SET= I2C_CLK;    Delay(1);
    IO0SET= I2C_DAT;    Delay(1);
}

/**************************************************
 * Description :             ��Ӧ���־
 * Parameters  :                 ��
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_MaskAck(void)
{
    IO0CLR= I2C_CLK;    Delay(1);
    IO0CLR= I2C_DAT;    Delay(2);
    IO0SET= I2C_CLK;    Delay(1);
    IO0CLR= I2C_CLK;    Delay(1);
    IO0SET= I2C_DAT;    Delay(1);
}

/**************************************************
 * Description :              Ӧ���־
 * Parameters  :                 ��
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_Ack(void)
{
    IO0CLR= I2C_CLK;    Delay(1);
    IO0SET= I2C_DAT;    Delay(2);
    IO0SET= I2C_CLK;    Delay(2);
    IO0CLR= I2C_CLK;    Delay(1);
}

/**************************************************
 * Description :             ��Ӧ���־
 * Parameters  :                 ��
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_NoAck(void)
{
    IO0SET= I2C_DAT;    Delay(1);
    IO0SET= I2C_CLK;    Delay(1);
    IO0CLR= I2C_CLK;    Delay(1);
}

/**************************************************
 * Description :          ��I2C����8bit����
 * Parameters  :            dat - ��������
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_WriteBit(uint8 dat)
{
	uint8 i= 8;
	IO0CLR= I2C_CLK;		Delay(1);
	while(i--) {
		(dat & 0x80) ? (IO0SET= I2C_DAT) : (IO0CLR= I2C_DAT);	Delay(1);
		dat= dat << 1;
		IO0SET= I2C_CLK;	Delay(1);
		IO0CLR= I2C_CLK;	Delay(1);
	}
}

/**************************************************
 * Description :         ��I2C��ȡһ��8bit������
 * Parameters  :     addr - ��ȡ���ݵĵ�ַ, 0->255
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
uint8 I2C_ReadUint8(uint16 addr)
{
	uint8 i= 8, dat= 0;
	
	I2C_StartBit();
	I2C_WriteBit(0xA0 | ((addr >> 7) & 0x0E));
	I2C_Ack();
	I2C_WriteBit(addr);
	I2C_Ack();
	
	I2C_StartBit();
	I2C_WriteBit(0xA1 | ((addr >> 7) & 0x0E));
	I2C_Ack();
	
	I2C_SwiDir(0);
	while(i--) {
		dat= dat << 1;
		IO0CLR= I2C_CLK;	Delay(1);
		IO0SET= I2C_CLK;	Delay(1);
		if(IO0PIN & I2C_DAT)
			dat|= 0x01;
	}
	I2C_SwiDir(1);
	
	I2C_NoAck();
	I2C_StopBit();
	Delay(100);
	return dat;
}

/**************************************************
 * Description :         ��I2Cд��һ��8bit������
 * Parameters  :     addr - д�����ݵĵ�ַ, 0->255
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void I2C_WriteUint8(uint16 addr, uint8 dat)
{
	IO0CLR= I2C_WP;
	I2C_StartBit();
	I2C_WriteBit(0xA0 | ((addr >> 7) & 0x0E));
	I2C_Ack();
	I2C_WriteBit(addr);
	I2C_Ack();
	I2C_WriteBit(dat);
	I2C_Ack();
	I2C_StopBit();
	
	Delay(4000);
	IO0SET= I2C_WP;
}
