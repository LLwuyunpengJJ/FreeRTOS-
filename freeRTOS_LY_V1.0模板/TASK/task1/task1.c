#include "task1.h"
#include "FreeRTOS.h"
#include "task.h"
TaskHandle_t LED0Task_Handler;//������



/* ���� */
#include "led.h"
/********/


//������
void led0_task(void *pvParameters)
{
	while(1)
    {
        LED1=0;
        vTaskDelay(200);
        LED1=1;
        vTaskDelay(800);
    }
}
//============================���񴴽�===============================//
void LY_TaskCreate_led0_task(void)
{
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )50, 
                (void*          )NULL,				
                (UBaseType_t    )2,	
                (TaskHandle_t*  )&LED0Task_Handler);    
}
//===================================================================//
