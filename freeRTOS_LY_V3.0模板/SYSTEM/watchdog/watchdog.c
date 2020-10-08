#include "watchdog.h"
void IWDG_Config(uint8_t prv ,uint16_t rlv)
{    
    // 使能 预分频寄存器PR和重装载寄存器RLR可写
    IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
    
    // 设置预分频器值
    IWDG_SetPrescaler( prv );
    
    // 设置重装载寄存器值
    IWDG_SetReload( rlv );
    
    // 把重装载寄存器的值放到计数器中
    IWDG_ReloadCounter();
    
    // 使能 IWDG
    IWDG_Enable();    
}
//===================================================================================
//看门狗工具
//===================================================================================
typedef struct {
	u32 ticket_ms_delay;
	u32 ticket_ms_start;
} WTDOG;
static WTDOG dog[dog_max_cnt] = {0};

_Bool WDG_CHECK(void)						//看门狗管理器
{
	u32 i = 0;
	u32 ticket 			= 	get_ticket();
	for(i = 0;i<dog_max_cnt;i++)
	{
		if(dog[i].ticket_ms_start > 0)
		{
			u32 ticket_dekay 	= 	ticket > dog[i].ticket_ms_start ? (ticket - dog[i].ticket_ms_start ):(0XFFFFFFFF - dog[i].ticket_ms_start + ticket);
			if(ticket_dekay > dog[i].ticket_ms_delay) return false;//狗失控
		}
	}
	return true;
}	

/*	用户程序	*/
_Bool WDG_NEW(u32 ticket,u32 * ID)			//创建并返回狗ID
{
	u32 i = 0;
	for(i = 0;i<dog_max_cnt;i++)
	{
		if(dog[i].ticket_ms_start == 0)
		{
			dog[i].ticket_ms_delay = ticket;
			dog[i].ticket_ms_start = get_ticket();
			*ID = i;
			return true;
		}
	}
	return false;
}

/* 删除狗 */
void WDG_DELETE(u32 ID) 	{dog[ID].ticket_ms_start = 0;}
/* 喂狗程序 */
void WDG_FEED(u32 ID)		{dog[ID].ticket_ms_start = get_ticket();}	




