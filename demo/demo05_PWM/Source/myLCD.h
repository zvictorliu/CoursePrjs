#ifndef _myLCD_H__
#define _myLCD_H__

/*******************************
 *		P0.27   -   sel
 *		P0.28   -   dat
 *		P0.29   -   clk
 *		P0.30   -   rst
 *******************************/
#define		LCD_CS		(1 << 27)
#define		LCD_DAT		(1 << 28)
#define		LCD_CLK		(1 << 29)
#define		LCD_RST		(1 << 30)

#define		LCD_MODE_TEXT		0
#define		LCD_MODE_CLEAR		1
#define		LCD_MODE_HIDE		2
#define		LCD_MODE_SHOW		3

void LCD_Init(void);
void LCD_SetMode(uint8 mode);
void LCD_TextOut(uint8 x, uint8 y, char *p);
void LCD_DrawOut(void);

extern uint8 const picSJTU[64][16];

#endif
