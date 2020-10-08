#ifndef __WATCH_H
#define __WATCH_H	
#include "sys.h"
#include "./system_task/semaphore_init.h"
#define get_ticket()	xTaskGetTickCount()
#define dog_max_cnt 100
/* 架构接口 */
_Bool WDG_CHECK(void);						//看门狗管理器	
/*	用户程序	*/
_Bool WDG_NEW(u32 ticket,u32 * ID);			//创建并返回狗ID
void WDG_DELETE(u32 ID);					//删除狗
void WDG_FEED(u32 ID);						//喂狗
#endif
