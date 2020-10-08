#include "./start_task/start_task.h"
#include "FreeRTOS.h"
#include "task.h"
//*******************************************************//
TaskHandle_t StartTask_Handler;				//������
//****************************************************/////

/* ����ͷ�ļ� */
#include "./0TIME_CHECK_task/TIME_CHECK_task.h" 
#include "./semaphore/semaphore_init.h"
/**************/

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           	//�����ٽ���
//****
	LY_TaskCreate_semaphore_init();		//�����ź�����Դ��
//****
		/* ���񴴽��� */
//****
	LY_TaskCreate_TIME_CHECK_task();
    vTaskDelete(StartTask_Handler); 	//ɾ����ʼ����
    taskEXIT_CRITICAL();            	//�˳��ٽ���
}

//============================����ϵͳ������===============================//
void RTOS_START(void)
{
		//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )100,        			//�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )1,       				//�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();       
}
//===========================================================================//



