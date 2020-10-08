#include "./system_task/wdg_task.h" 
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t wdg_task_Handler;			//任务句柄
#define wdg_printf(...)  {xSemaphoreTake(Uart1Semaphore,portMAX_DELAY); printf("【WDG】:");printf(__VA_ARGS__);xSemaphoreGive(Uart1Semaphore);}

/* 驱动文件 */
#include "./system_task/semaphore_init.h"
#include "delay.h"
#include "watchdog.h"
/**************/

//开始任务任务函数
void wdg_task(void)
{
	IWDG_Config(IWDG_Prescaler_128 ,4090); 			//加入狗
	while(1)
	{
		if(!WDG_CHECK())
			vTaskSuspend(wdg_task_Handler);
		IWDG_ReloadCounter();
	    delay_ms(100);
	}
}

//============================操作系统相关入口===============================//
void LY_TaskCreate_wdg_task(void)
{
    xTaskCreate((TaskFunction_t )wdg_task,              //任务函数
                (const char*    )"wdg_task",            //任务名称
                (uint16_t       )50,        			//任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )20,       				//任务优先级
                (TaskHandle_t*  )&wdg_task_Handler);    //任务句柄 				
}
//===========================================================================//



