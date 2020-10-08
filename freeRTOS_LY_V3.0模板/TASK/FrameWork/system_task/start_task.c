#include "./system_task/start_task.h"
#include "FreeRTOS.h"
#include "task.h"
//*******************************************************//
TaskHandle_t StartTask_Handler;				//任务句柄
//****************************************************/////

/* 任务头文件 */
//SYSTEM
#include "./system_task/semaphore_init.h"
#include "./system_task/check_task.h" 
#include "./system_task/wdg_task.h" 
//驱动层

//常用可修改组件

//业务层组件


/**************/
//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           		//进入临界区
//****资源
	LY_TaskCreate_check_task();		//系统核心资源分析输出			 //优先级 ：30//特权优先级暂无意义
	LY_TaskCreate_semaphore_init();			//公共信号量资源区   
	LY_TaskCreate_wdg_task();				//看门狗程序                     //优先级 ：1   20//最高级，狗管理器
//****框架层 																					

//====常用组件修改区域                                 
	
//****业务层                                                                       
	
//****结束
    vTaskDelete(StartTask_Handler); 		//删除开始任务
    taskEXIT_CRITICAL();            		//退出临界区
}

//============================操作系统相关入口===============================//
void RTOS_START(void)
{
		//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )100,        			//任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )1,       				//任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();       
}
//===========================================================================//



