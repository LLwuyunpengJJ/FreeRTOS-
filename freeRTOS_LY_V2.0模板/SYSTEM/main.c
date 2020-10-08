/* 官方库文件 */
#include "sys.h"
/* 驱动库文件 */
#include "delay.h"
#include "uart.h"
/* 系统头文件 */
#include "./start_task/start_task.h"

/********* 程序入口main *********/
int main(void)
{
	/* 驱动程序初始化 */
//	NVIC_SetVectorTable(0x08000000, 0x10000);		// 向量表偏移
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	// 中断优先级设置 
	delay_init();	    	 						// 延时函数初始化	
	UART1_init();									// 串口1初始化	
	/* 操作系统入口 */
	RTOS_START();
}

