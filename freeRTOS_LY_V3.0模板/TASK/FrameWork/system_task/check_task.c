#include "./system_task/check_task.h"
#include "FreeRTOS.h"
#include "task.h"
TaskHandle_t check_Task_Handler;//������

#define check_printf(...) 	{xSemaphoreTake(Uart1Semaphore,portMAX_DELAY);printf("��check��:"); printf(__VA_ARGS__);xSemaphoreGive(Uart1Semaphore);}
#define check_printfs(...) 	{xSemaphoreTake(Uart1Semaphore,portMAX_DELAY);printf("��check��:\r\n"); printf(__VA_ARGS__);xSemaphoreGive(Uart1Semaphore);}
/* ����ͷ�ļ� */
#include "./system_task/semaphore_init.h"
#include "delay.h"
#include "watchdog.h"
/**************/
static char buffer[1500];

void Task_List(void)
{
	vTaskList(buffer);
	check_printf("//*******************������Ϣ********************//\r\n");
	check_printfs("%s\r\n",buffer);
	check_printf("//***********************************************//\r\n");
	vTaskGetRunTimeStats(buffer);
	check_printf("//******************cpuʹ����Ϣ******************//\r\n");
	check_printfs("%s\r\n",buffer);
	check_printf("//***********************************************//\r\n");
	check_printf("//******************cpuʹ����Ϣ******************//\r\n");
	check_printf("//***********************************************//\r\n");
}

//������
void LY_check_task(void)
{
	whil�� WDG_NEW(u32 ticket,u32 * ID);			//���������ع�ID
	while(1)
    {
		
		Task_List();
		delay_ms(1000);
		
    }
}


//============================���񴴽�===============================//
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
