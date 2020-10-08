#include "task_TIME_CHECK.h"
#include "FreeRTOS.h"
#include "task.h"
TaskHandle_t TIME_CHECK_Task_Handler;//������

static char buffer[200];
//������
void LY_TIME_CHECK_task(void *pvParameters)
{
	while(1)
    {
		vTaskList(buffer);
		printf("//*******************������Ϣ********************//\r\n");
		printf("%s\r\n",buffer);
		//printf("//***********************************************//\r\n");
		//vTaskDelay(500);
		vTaskGetRunTimeStats(buffer);
		printf("//******************cpuʹ����Ϣ******************//\r\n");
		printf("%s\r\n",buffer);
		printf("//***********************************************//\r\n");
		vTaskDelay(500);
    }
}




//============================���񴴽�===============================//
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
