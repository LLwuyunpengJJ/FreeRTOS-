#ifndef __WATCH_H
#define __WATCH_H	
#include "sys.h"
#include "./system_task/semaphore_init.h"
#define get_ticket()	xTaskGetTickCount()
#define dog_max_cnt 100
/* �ܹ��ӿ� */
_Bool WDG_CHECK(void);						//���Ź�������	
/*	�û�����	*/
_Bool WDG_NEW(u32 ticket,u32 * ID);			//���������ع�ID
void WDG_DELETE(u32 ID);					//ɾ����
void WDG_FEED(u32 ID);						//ι��
#endif
