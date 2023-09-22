/************************************************************************
 *                           Copyrights (C) 2007
 *-----------------------------------------------------------------------
 * Descriptions:   ����LCD��Һ������ͬʱ��ʾSJTU��ͼ�κ��ַ�
 * Attention   :                      ��
 * Created By  :                    Kngboy
 * Created Date:                  2007-09-12
 ************************************************************************/

#include "config.h"

#define		KEY_OK			(1 << 4 )
#define		KEY_ESC			(1 << 5 )
#define		KEY_DEC			(1 << 11)
#define		KEY_INC			(1 << 12)

/**************************************************
 * Description :            �����������
 * Parameters  :      spd - ����ٶ� dir - �������
 * Created By  :               Kngboy
 * Created Date:             2007-09-21
 **************************************************/
void PWM_Out(uint16 spd, uint8 dir)
{
	if(spd== 0) {
		PWMTCR= 2;
		return;
	}
	
	if(dir)
		IO0CLR= (1 << 19);
	else
		IO0SET= (1 << 19);
	
	PWMMR0= Fpclk/ (spd* 10);
	PWMMR4= PWMMR0/ 2;
	PWMLER= (1 << 0) | (1 << 4);
	PWMTCR= 9;
}

int main(void)
{
	unsigned char flag = 1;		// ����statement is unreachable�ľ���

	uint8 spd= 50, dir= 1, run= 1;
	char str[8];
	
	LCD_Init(); // LCD��ʼ��
	I2C_Init(); // I2C��ʼ��
	PINSEL0&= ~((3 << 8) | (3 << 10) | (3 << 22) | (3 << 24));
	IO0DIR &= ~(KEY_ESC | KEY_INC | KEY_DEC | KEY_OK);
	
	/* ������ƶ˿ں�PWM�˿����� */
	PINSEL0&=~ (3 << 16);
	PINSEL0|=  (2 << 16);
	PINSEL1&=~((3 <<  2) | (3 <<  4) | (3 <<  6));
	IO0DIR |= ((1 << 17) | (1 << 18) | (1 << 19));
	IO0CLR  =  (1 << 17);
	PWMMCR  = 2;
	PWMPCR  = 1 << 12;
	
	LCD_SetMode(LCD_MODE_CLEAR); // ����
	
	LCD_SetMode(LCD_MODE_HIDE);  // ������
	LCD_DrawOut();               // ��ͼ
	LCD_SetMode(LCD_MODE_SHOW);  // ����ͼ
	
	LCD_SetMode(LCD_MODE_TEXT);  // д�ַ�
	LCD_TextOut(2, 0, " DRIVER ");
	LCD_TextOut(0, 1, "+/- SPD:");
	LCD_TextOut(0, 2, "ESC DIR:");
	LCD_TextOut(0, 3, "OK  RUN:");
	
	while(flag)
	{
		if((~IO0PIN) & KEY_INC)
			if(++spd> 99)
				spd= 99;
		if((~IO0PIN) & KEY_DEC)
			if(--spd< 1)
				spd= 1;
		if((~IO0PIN) & KEY_ESC)
			dir= 1- dir;
		if((~IO0PIN) & KEY_OK )
			run= 1- run;
		
		sprintf(str, " %02d", spd);
		LCD_TextOut(4, 1, str);
		if(dir)
			LCD_TextOut(4, 2, " -> ");
		else
			LCD_TextOut(4, 2, " <- ");
		if(run)
			LCD_TextOut(4, 3, " >> ");
		else
			LCD_TextOut(4, 3, " == ");
		
		if(run)
			PWM_Out(spd, dir);
		else
			PWM_Out(0, 0);
		Sleep(30);
		I2C_FeedDog(); // Ӳ�����Ź�
	}
	
	return 0;
}
