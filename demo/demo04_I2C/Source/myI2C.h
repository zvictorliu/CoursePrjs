#ifndef _myI2C_H__
#define _myI2C_H__

/**********************************
 *		P0.2   -   clk
 *		P0.3   -   dat
 *		P0.21  -   wp
 **********************************/
#define		I2C_CLK			(1 << 2)
#define		I2C_DAT			(1 << 3)
#define		I2C_WP			(1 << 21)

void  Delay(uint32 dly);
void  Sleep(uint32 dly);
void  I2C_Init(void);
uint8 I2C_ReadUint8(uint16 addr);
void  I2C_WriteUint8(uint16 addr, uint8 data);

#endif
