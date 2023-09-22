
#include "includes.h"
#include "OS_CPU.h"
#include "bsp.h"

#include "config.h"

#define		KEY_OK			(1 << 4 )
#define		KEY_ESC			(1 << 5 )
#define		KEY_DEC			(1 << 11)
#define		KEY_INC			(1 << 12)
#define		LED_AUTO		(1 << 16)

#define		TASK_STK_SIZE		128

OS_STK		TaskStartStk[TASK_STK_SIZE];

void TaskStart(void *data);

/* ��������Ķ�ջ�ռ� */
OS_STK	Stack_I2C[TASK_STK_SIZE];
OS_STK	Stack_MID[TASK_STK_SIZE];
OS_STK	Stack_KEY[TASK_STK_SIZE];
OS_STK	Stack_LCD[TASK_STK_SIZE];

/* ��������֮��ͨѶ�ź� */
OS_EVENT *SEM_UPDATE;
OS_EVENT *MBOX_KEYDN;

uint8 u8CntI2C= 0, u8CntMID= 0, u8CntKEY= 0, u8CntLCD= 0;
char  strKey[8] = {0};

/* Ӳ�����Ź��������� */
void Task_I2C(void *pdata)
{
	uint8 i= 0;
	pdata= pdata;
	SEM_UPDATE= OSSemCreate(1); // �����ź���
	
	while(1)
	{
		I2C_FeedDog(); // Ӳ�����Ź�
		
		if(++i>= 10) {
			i= 0;
			u8CntI2C++;
			OSSemPost(SEM_UPDATE); // �����ź���
		}
		
		OSTimeDlyHMSM(0, 0, 0, 5); // ������ʱ�ȴ�
	}
}

/* ���̴������� */
void Task_MID(void *pdata)
{
	uint8  i= 0, err;
	uint32 *key= 0;
	pdata= pdata;
	MBOX_KEYDN= OSMboxCreate(&key);
	
	while(1)
	{
		key= OSMboxPend(MBOX_KEYDN, 0, &err); // �ȴ�������Ϣ
		switch(*key) {
			case KEY_ESC: strcpy(strKey, "ESC");	break;
			case KEY_INC: strcpy(strKey, "INC");	break;
			case KEY_DEC: strcpy(strKey, "DEC");	break;
			case KEY_OK : strcpy(strKey, "OK ");	break;
		}
		
		if(++i>= 10) {
			i= 0;
			u8CntMID++;
		}
		
		OSTimeDlyHMSM(0, 0, 0, 10);
	}
}

/* ���񰴼���Ϣ���� */
void Task_KEY(void *pdata)
{
	uint8  i= 0;
	uint32 key= 0;
	pdata= pdata;
	
	while(1)
	{
		while((key= (~IO0PIN) & (KEY_ESC | KEY_INC | KEY_DEC | KEY_OK))== 0)
			OSTimeDlyHMSM(0, 0, 0, 50);
		OSMboxPost(MBOX_KEYDN, (void *)&key); // ����������Ϣ
		
		if(++i>= 10) {
			i= 0;
			u8CntKEY++;
		}
		
		OSTimeDlyHMSM(0, 0, 0, 15);
	}
}

/* ��Ļ�������� */
void Task_LCD(void *pdata)
{
	uint8 i= 0, err;
	char str[8];
	pdata= pdata;

	LCD_SetMode(LCD_MODE_CLEAR); // ����

	LCD_SetMode(LCD_MODE_HIDE);  // ������
	LCD_DrawOut();               // ��ͼ
	LCD_SetMode(LCD_MODE_SHOW);  // ����ͼ

	LCD_SetMode(LCD_MODE_TEXT);
	LCD_TextOut(2, 0, "I2C:");
	LCD_TextOut(2, 1, "MID:");
	LCD_TextOut(2, 2, "KEY:");
	LCD_TextOut(2, 3, "LCD:");

	while(1)
	{
		OSSemPend(SEM_UPDATE, 0, &err); // �ȴ��ź���

		LCD_SetMode(LCD_MODE_TEXT);
		LCD_TextOut(0, 0, strKey);

		sprintf(str, " %-3d", u8CntI2C);
		LCD_TextOut(4, 0, str);
		sprintf(str, " %-3d", u8CntMID);
		LCD_TextOut(4, 1, str);
		sprintf(str, " %-3d", u8CntKEY);
		LCD_TextOut(4, 2, str);
		sprintf(str, " %-3d", u8CntLCD);
		LCD_TextOut(4, 3, str);

		if(++i>= 10) {
			i= 0;
			u8CntLCD++;
		}

		OSTimeDlyHMSM(0, 0, 0, 20);
	}
}

void TaskStart(void *pdata)
{
	pdata = pdata;

	BSP_init();

	LCD_Init(); // LCD��ʼ��
	I2C_Init(); // I2C��ʼ��

	PINSEL0&= ~((3 << 8) | (3 << 10) | (3 << 22) | (3 << 24));
	PINSEL1&= ~ (3 << 0);
	IO0DIR |=   LED_AUTO;
	IO0DIR &= ~(KEY_ESC | KEY_INC | KEY_DEC | KEY_OK);

	OSTaskCreate(Task_I2C, (void *)0, &Stack_I2C[TASK_STK_SIZE - 1],  5);
	OSTaskCreate(Task_MID, (void *)0, &Stack_MID[TASK_STK_SIZE - 1], 10);
	OSTaskCreate(Task_KEY, (void *)0, &Stack_KEY[TASK_STK_SIZE - 1], 15);
	OSTaskCreate(Task_LCD, (void *)0, &Stack_LCD[TASK_STK_SIZE - 1], 20);

	OSTaskDel(0);
}

int main(void)
{
	OSInit();
	OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);
	OSStart();

	return 0;
}
