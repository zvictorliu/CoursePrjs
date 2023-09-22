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

#define		Fosc		11059200					//Crystal frequence,10MHz~25MHz��should be the same as actual status. 
													//Ӧ����ʵ��һ������Ƶ��,10MHz~25MHz��Ӧ����ʵ��һ��
#define		Fcclk		(Fosc * 4)					//System frequence,should be (1~32)multiples of Fosc,and should be equal or less  than 60MHz. 
													//ϵͳƵ�ʣ�����ΪFosc��������(1~32)����<=60MHZ
#define		Fcco		(Fcclk * 4)					//CCO frequence,should be 2��4��8��16 multiples of Fcclk, ranged from 156MHz to 320MHz. 
													//CCOƵ�ʣ�����ΪFcclk��2��4��8��16������ΧΪ156MHz~320MHz
#define		Fpclk		(Fcclk / 1) * 1				//VPB clock frequence , must be 1��2��4 multiples of (Fcclk / 4).
													//VPBʱ��Ƶ�ʣ�ֻ��Ϊ(Fcclk / 4)��1��2��4��

#include	"myI2C.h"
#include	"myLCD.h"

#endif
