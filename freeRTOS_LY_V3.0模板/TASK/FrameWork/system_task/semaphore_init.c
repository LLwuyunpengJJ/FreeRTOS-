#include "./system_task/semaphore_init.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "semphr.h"

#define blen 3

SemaphoreHandle_t 	Uart1Semaphore;			//��ֵ�ź������
QueueHandle_t     	Uart1_Message_Queue;	//��Ϣ���о��


SHEET 			DATA_SHEET = {0};			//���ݴ洢��
STORE_SHEET 	DATA_STORE = {0};			//�������ݴ洢��
void LY_TaskCreate_semaphore_init(void)
{
																		
	Uart1Semaphore 			= 	xSemaphoreCreateMutex();					//��ֵ�ź���
	Uart1_Message_Queue		=	xQueueCreate(2,100); 						//uart2�������
	
}






