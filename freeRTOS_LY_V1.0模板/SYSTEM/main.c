/* �ٷ����ļ� */
#include "sys.h"
/* �������ļ� */
#include "init.h"
/* ϵͳͷ�ļ� */
#include "start_task.h"

/********* �������main *********/
int main(void)
{
	/* ���������ʼ�� */
	DEVICE_INIT();
	/* ����ϵͳ��� */
	RTOS_START();
}


