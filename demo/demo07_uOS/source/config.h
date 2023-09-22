#ifndef	CONFIG_H
#define	CONFIG_H

#include	<stdio.h>
#include	<stdlib.h>

#include	"LPC2294.h"

typedef	  signed char	int8;
typedef	  signed short	int16;
typedef	  signed long	int32;
typedef	unsigned char	uint8;
typedef	unsigned short	uint16;
typedef	unsigned long	uint32;
typedef	unsigned char	BOOL;
typedef	unsigned char	bool;

typedef	unsigned long	INT32U;

#define		TRUE		1
#define		FALSE		0

#define		true		1
#define		false		0

#define		Fosc		11059200					//Crystal frequence,10MHz~25MHz，should be the same as actual status. 
													//应当与实际一至晶振频率,10MHz~25MHz，应当与实际一至
#define		Fcclk		(Fosc * 4)					//System frequence,should be (1~32)multiples of Fosc,and should be equal or less  than 60MHz. 
													//系统频率，必须为Fosc的整数倍(1~32)，且<=60MHZ
#define		Fcco		(Fcclk * 4)					//CCO frequence,should be 2、4、8、16 multiples of Fcclk, ranged from 156MHz to 320MHz. 
													//CCO频率，必须为Fcclk的2、4、8、16倍，范围为156MHz~320MHz
#define		Fpclk		(Fcclk / 1) * 1				//VPB clock frequence , must be 1、2、4 multiples of (Fcclk / 4).
													//VPB时钟频率，只能为(Fcclk / 4)的1、2、4倍

#include	"myI2C.h"
#include	"myLCD.h"

#endif
