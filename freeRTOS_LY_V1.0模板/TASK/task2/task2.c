#include "task2.h"
#include "FreeRTOS.h"
#include "task.h"
TaskHandle_t LED1Task_Handler; //������


/* ���� */
#include "led.h"
/********/


//������
void led1_task(void *pvParameters)
{
	while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}

//============================���񴴽�===============================//
void LY_TaskCreate_led1_task(void)
{
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )50, 
                (void*          )NULL,
                (UBaseType_t    )3,
                (TaskHandle_t*  )&LED1Task_Handler); 
}

//===================================================================//
