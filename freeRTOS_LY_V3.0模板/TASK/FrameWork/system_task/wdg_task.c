#include "./system_task/wdg_task.h" 
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t wdg_task_Handler;			//������
#define wdg_printf(...)  {xSemaphoreTake(Uart1Semaphore,portMAX_DELAY); printf("��WDG��:");printf(__VA_ARGS__);xSemaphoreGive(Uart1Semaphore);}

/* �����ļ� */
#include "./system_task/semaphore_init.h"
#include "delay.h"
#include "watchdog.h"
/**************/

//��ʼ����������
void wdg_task(void)
{
	IWDG_Config(IWDG_Prescaler_128 ,4090); 			//���빷
	while(1)
	{
		if(!WDG_CHECK())
			vTaskSuspend(wdg_task_Handler);
		IWDG_ReloadCounter();
	    delay_ms(100);
	}
}

//============================����ϵͳ������===============================//
void LY_TaskCreate_wdg_task(void)
{
    xTaskCreate((TaskFunction_t )wdg_task,              //������
                (const char*    )"wdg_task",            //��������
                (uint16_t       )50,        			//�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )20,       				//�������ȼ�
                (TaskHandle_t*  )&wdg_task_Handler);    //������ 				
}
//===========================================================================//



