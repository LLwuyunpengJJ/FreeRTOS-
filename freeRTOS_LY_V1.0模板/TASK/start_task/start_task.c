#include "start_task.h"
#include "FreeRTOS.h"
#include "task.h"
//*******************************************************//
TaskHandle_t StartTask_Handler;				//任务句柄
//****************************************************/////

/* 任务头文件 */
#include "task1.h"
#include "task2.h"
/**************/

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
	LY_TaskCreate_led0_task();
	LY_TaskCreate_led1_task();
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//============================操作系统相关入口===============================//
void RTOS_START(void)
{
		//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )50,        			//任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )1,       				//任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();       
}
//===========================================================================//



