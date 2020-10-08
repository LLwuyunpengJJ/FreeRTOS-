#include "task_TIME_CHECK.h"
#include "FreeRTOS.h"
#include "task.h"
TaskHandle_t TIME_CHECK_Task_Handler;//任务句柄

static char buffer[200];
//任务函数
void LY_TIME_CHECK_task(void *pvParameters)
{
	while(1)
    {
		vTaskList(buffer);
		printf("//*******************任务信息********************//\r\n");
		printf("%s\r\n",buffer);
		//printf("//***********************************************//\r\n");
		//vTaskDelay(500);
		vTaskGetRunTimeStats(buffer);
		printf("//******************cpu使用信息******************//\r\n");
		printf("%s\r\n",buffer);
		printf("//***********************************************//\r\n");
		vTaskDelay(500);
    }
}




//============================任务创建===============================//
void LY_TaskCreate_TIME_CHECK_task(void)
{
    xTaskCreate((TaskFunction_t )LY_TIME_CHECK_task,     	
                (const char*    )"LY_TIME_CHECK_task",   	
                (uint16_t       )50, 
                (void*          )NULL,				
                (UBaseType_t    )2,	
                (TaskHandle_t*  )&TIME_CHECK_Task_Handler);    
}
//===================================================================//
