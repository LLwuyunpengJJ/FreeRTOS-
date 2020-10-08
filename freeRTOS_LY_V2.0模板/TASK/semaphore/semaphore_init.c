#include "./semaphore/semaphore_init.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "semphr.h"

SemaphoreHandle_t 	Uart1Semaphore;			//互斥串口1信号量
QueueHandle_t     	Uart1_Message_Queue;	//信息队列句柄
SemaphoreHandle_t 	TestSemaphore;			//测试二值信号量
EventGroupHandle_t  Test_Group;				//测试事件标志组

SHEET 			DATA_SHEET = {0};			//数据存储表
STORE_SHEET 	DATA_STORE = {0};			//掉电数据存储表
void LY_TaskCreate_semaphore_init(void)
{
																		
	Uart1Semaphore 			= 	xSemaphoreCreateMutex();					//互斥串口1信号量
	Uart1_Message_Queue		=	xQueueCreate(2,100); 						//uart1缓冲队列
	TestSemaphore			= 	xSemaphoreCreateBinary();					//测试二值信号量		
	Test_Group 				=  	xEventGroupCreate();						//测试事件标志组	
}






