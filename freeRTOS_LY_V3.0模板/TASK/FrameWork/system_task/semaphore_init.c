#include "./system_task/semaphore_init.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "semphr.h"

#define blen 3

SemaphoreHandle_t 	Uart1Semaphore;			//二值信号量句柄
QueueHandle_t     	Uart1_Message_Queue;	//信息队列句柄


SHEET 			DATA_SHEET = {0};			//数据存储表
STORE_SHEET 	DATA_STORE = {0};			//掉电数据存储表
void LY_TaskCreate_semaphore_init(void)
{
																		
	Uart1Semaphore 			= 	xSemaphoreCreateMutex();					//二值信号量
	Uart1_Message_Queue		=	xQueueCreate(2,100); 						//uart2缓冲队列
	
}






