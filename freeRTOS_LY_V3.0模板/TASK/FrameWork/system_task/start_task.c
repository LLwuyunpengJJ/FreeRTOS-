#include "./system_task/start_task.h"
#include "FreeRTOS.h"
#include "task.h"
//*******************************************************//
TaskHandle_t StartTask_Handler;				//������
//****************************************************/////

/* ����ͷ�ļ� */
//SYSTEM
#include "./system_task/semaphore_init.h"
#include "./system_task/check_task.h" 
#include "./system_task/wdg_task.h" 
//������

//���ÿ��޸����

//ҵ������


/**************/
//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           		//�����ٽ���
//****��Դ
	LY_TaskCreate_check_task();		//ϵͳ������Դ�������			 //���ȼ� ��30//��Ȩ���ȼ���������
	LY_TaskCreate_semaphore_init();			//�����ź�����Դ��   
	LY_TaskCreate_wdg_task();				//���Ź�����                     //���ȼ� ��1   20//��߼�����������
//****��ܲ� 																					

//====��������޸�����                                 
	
//****ҵ���                                                                       
	
//****����
    vTaskDelete(StartTask_Handler); 		//ɾ����ʼ����
    taskEXIT_CRITICAL();            		//�˳��ٽ���
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



