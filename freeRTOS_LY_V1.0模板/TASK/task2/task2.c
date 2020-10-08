#include "task2.h"
#include "FreeRTOS.h"
#include "task.h"
TaskHandle_t LED1Task_Handler; //任务句柄


/* 驱动 */
#include "led.h"
/********/


//任务函数
void led1_task(void *pvParameters)
{
	while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}

//============================任务创建===============================//
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
