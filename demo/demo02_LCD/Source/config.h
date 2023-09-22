#ifndef	CONFIG_H
#define	CONFIG_H

#include	<stdio.h>
#include	<stdlib.h>

#include	"LPC2294.h"

typedef	  signed char	int8;
typedef	  signed int	int16;
typedef	  signed long	int32;
typedef	unsigned char	uint8;
typedef	unsigned int	uint16;
typedef	unsigned long	uint32;
typedef	unsigned char	BOOL;
typedef	unsigned char	bool;

#define		TRUE		1
#define		FALSE		0

#define		true		1
#define		false		0

#include	"myI2C.h"
#include	"myLCD.h"

#endif
