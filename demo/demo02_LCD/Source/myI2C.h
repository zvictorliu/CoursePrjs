#ifndef _myI2C_H__
#define _myI2C_H__

#include "config.h"

/**********************************
 *		P0.2   -   clk
 *		P0.3   -   dat
 **********************************/
#define		I2C_CLK			(1 << 2)
#define		I2C_DAT			(1 << 3)

void Delay(uint16 dly);
void Sleep(uint16 dly);
void I2C_Init(void);
void I2C_FeedDog(void);

#endif
