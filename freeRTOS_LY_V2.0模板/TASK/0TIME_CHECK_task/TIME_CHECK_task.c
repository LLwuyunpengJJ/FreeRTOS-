#include "./0TIME_CHECK_task/TIME_CHECK_task.h"
#include "FreeRTOS.h"
#include "task.h"
TaskHandle_t TIME_CHECK_Task_Handler;//任务句柄

#define TIME_CHECK_printf(...) 	{xSemaphoreTake(Uart1Semaphore,portMAX_DELAY);printf("【TIME_CHECK】:"); printf(__VA_ARGS__);xSemaphoreGive(Uart1Semaphore);}
#define TIME_CHECK_printfs(...) 	{xSemaphoreTake(Uart1Semaphore,portMAX_DELAY);printf("【TIME_CHECK】:\r\n"); printf(__VA_ARGS__);xSemaphoreGive(Uart1Semaphore);}
/* 驱动头文件 */
#include "./semaphore/semaphore_init.h"
#include "delay.h"
/**************/
static char buffer[1500];

void Task_List(void)
{
	vTaskList(buffer);
	TIME_CHECK_printf("//*******************任务信息********************//\r\n");
	TIME_CHECK_printfs("%s\r\n",buffer);
	TIME_CHECK_printf("//***********************************************//\r\n");
	vTaskGetRunTimeStats(buffer);
	TIME_CHECK_printf("//******************cpu使用信息******************//\r\n");
	TIME_CHECK_printfs("%s\r\n",buffer);
	TIME_CHECK_printf("//***********************************************//\r\n");
	TIME_CHECK_printf("//******************cpu使用信息******************//\r\n");
	TIME_CHECK_printf("//***********************************************//\r\n");
}

//任务函数
void LY_TIME_CHECK_task(void *pvParameters)
{
	while(1)
    {
		Task_List();
		//IWDG_ReloadCounter();
		delay_ms(30000);
    }
}

//#include "timers.h"
//TimerHandle_t Timer1_Handle;
//TimerHandle_t Timer2_Handle;
//TimerHandle_t Timer3_Handle;
//TimerHandle_t Timer4_Handle;

//void timer1(void)
//{				

//}
//void timer2(void)
//{

//}

//void timer3(void)
//{
//	
//}

//void timer4(void)
//{
//	
//}



//============================任务创建===============================//
void LY_TaskCreate_TIME_CHECK_task(void)
{
    xTaskCreate((TaskFunction_t )LY_TIME_CHECK_task,     	
                (const char*    )"LY_TIME_CHECK_task",   	
                (uint16_t       )100, 
                (void*          )NULL,				
                (UBaseType_t    )19,	
                (TaskHandle_t*  )&TIME_CHECK_Task_Handler); 
//	Timer1_Handle =			
//	xTimerCreate((const char*		)"timer1",
//				(TickType_t			)100,
//				(UBaseType_t		)pdFALSE,
//				(void*				)1,
//				(TimerCallbackFunction_t)timer1);
//	xTimerStart(Timer1_Handle,0);	
//	Timer2_Handle =			
//	xTimerCreate((const char*		)"timer2",
//				(TickType_t			)1000,
//				(UBaseType_t		)pdTRUE,
//				(void*				)1,
//				(TimerCallbackFunction_t)timer2);
//	xTimerStart(Timer2_Handle,0);	
//	Timer3_Handle =			
//	xTimerCreate((const char*		)"timer3",
//				(TickType_t			)4000,
//				(UBaseType_t		)pdFALSE,
//				(void*				)1,
//				(TimerCallbackFunction_t)timer3);
//	xTimerStart(Timer3_Handle,0);	
//	Timer4_Handle =			
//	xTimerCreate((const char*		)"timer4",
//				(TickType_t			)8000,
//				(UBaseType_t		)pdFALSE,
//				(void*				)1,
//				(TimerCallbackFunction_t)timer4);
//	xTimerStart(Timer4_Handle,0);					
}
//===================================================================//
