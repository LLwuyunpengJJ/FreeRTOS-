#include "./system_task/check_task.h"
#include "FreeRTOS.h"
#include "task.h"
TaskHandle_t check_Task_Handler;//任务句柄

#define check_printf(...) 	{xSemaphoreTake(Uart1Semaphore,portMAX_DELAY);printf("【check】:"); printf(__VA_ARGS__);xSemaphoreGive(Uart1Semaphore);}
#define check_printfs(...) 	{xSemaphoreTake(Uart1Semaphore,portMAX_DELAY);printf("【check】:\r\n"); printf(__VA_ARGS__);xSemaphoreGive(Uart1Semaphore);}
/* 驱动头文件 */
#include "./system_task/semaphore_init.h"
#include "delay.h"
#include "watchdog.h"
/**************/
static char buffer[1500];

void Task_List(void)
{
	vTaskList(buffer);
	check_printf("//*******************任务信息********************//\r\n");
	check_printfs("%s\r\n",buffer);
	check_printf("//***********************************************//\r\n");
	vTaskGetRunTimeStats(buffer);
	check_printf("//******************cpu使用信息******************//\r\n");
	check_printfs("%s\r\n",buffer);
	check_printf("//***********************************************//\r\n");
	check_printf("//******************cpu使用信息******************//\r\n");
	check_printf("//***********************************************//\r\n");
}

//任务函数
void LY_check_task(void)
{
	whil（ WDG_NEW(u32 ticket,u32 * ID);			//创建并返回狗ID
	while(1)
    {
		
		Task_List();
		delay_ms(1000);
		
    }
}


//============================任务创建===============================//
void LY_TaskCreate_check_task(void)
{
    xTaskCreate((TaskFunction_t )LY_check_task,     	
                (const char*    )"LY_check_task",   	
                (uint16_t       )100, 
                (void*          )NULL,				
                (UBaseType_t    )30,	
                (TaskHandle_t*  )&check_Task_Handler); 					
}
//===================================================================//
