/* �ٷ����ļ� */
#include "sys.h"
/* �������ļ� */
#include "delay.h"
#include "uart.h"
/* ϵͳͷ�ļ� */
#include "./system_task/start_task.h"

/********* �������main *********/
int main(void)
{
	/* ���������ʼ�� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	// �ж����ȼ����� 
	delay_init();	    	 						// ��ʱ������ʼ��	
	UART1_init();									// ����1��ʼ��	
	/* ����ϵͳ��� */
	RTOS_START();
	while(1){};
}


