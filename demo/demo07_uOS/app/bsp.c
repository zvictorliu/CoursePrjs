
#include <lpc2103.h>
#define IN_TARGET
#include "includes.h"
#include "OS_CPU.h"
void IRQCTimer0(void) {

#if OS_CRITICAL_METHOD == 3
	OS_CPU_SR  cpu_sr;
#endif


	OS_ENTER_CRITICAL();
	T0IR = 0x01;
	VICVectAddr = 0;            // 通知中断控制器中断结束
	OS_EXIT_CRITICAL();
	OSTimeTick();
}

void BSP_init(void) {
	extern void IRQASMTimer0(void);

	T0IR  = 0xFF;
	T0TC  = 0;
	T0TCR = 0x01;
	T0MCR = 0x03;
	T0MR0 = (60000000 / OS_TICKS_PER_SEC);

	VICIntEnClr =  (1 << 4);
	VICVectAddr0 = (INT32U)IRQASMTimer0;
	VICVectCntl0 = (0x20 | 0x04);
	VICIntEnable = (1 << 4);
}
