#include "./semaphore/semaphore_init.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "semphr.h"

SemaphoreHandle_t 	Uart1Semaphore;			//���⴮��1�ź���
QueueHandle_t     	Uart1_Message_Queue;	//��Ϣ���о��
SemaphoreHandle_t 	TestSemaphore;			//���Զ�ֵ�ź���
EventGroupHandle_t  Test_Group;				//�����¼���־��

SHEET 			DATA_SHEET = {0};			//���ݴ洢��
STORE_SHEET 	DATA_STORE = {0};			//�������ݴ洢��
void LY_TaskCreate_semaphore_init(void)
{
																		
	Uart1Semaphore 			= 	xSemaphoreCreateMutex();					//���⴮��1�ź���
	Uart1_Message_Queue		=	xQueueCreate(2,100); 						//uart1�������
	TestSemaphore			= 	xSemaphoreCreateBinary();					//���Զ�ֵ�ź���		
	Test_Group 				=  	xEventGroupCreate();						//�����¼���־��	
}






