#include "watchdog.h"
void IWDG_Config(uint8_t prv ,uint16_t rlv)
{    
    // ʹ�� Ԥ��Ƶ�Ĵ���PR����װ�ؼĴ���RLR��д
    IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
    
    // ����Ԥ��Ƶ��ֵ
    IWDG_SetPrescaler( prv );
    
    // ������װ�ؼĴ���ֵ
    IWDG_SetReload( rlv );
    
    // ����װ�ؼĴ�����ֵ�ŵ���������
    IWDG_ReloadCounter();
    
    // ʹ�� IWDG
    IWDG_Enable();    
}
//===================================================================================
//���Ź�����
//===================================================================================
typedef struct {
	u32 ticket_ms_delay;
	u32 ticket_ms_start;
} WTDOG;
static WTDOG dog[dog_max_cnt] = {0};

_Bool WDG_CHECK(void)						//���Ź�������
{
	u32 i = 0;
	u32 ticket 			= 	get_ticket();
	for(i = 0;i<dog_max_cnt;i++)
	{
		if(dog[i].ticket_ms_start > 0)
		{
			u32 ticket_dekay 	= 	ticket > dog[i].ticket_ms_start ? (ticket - dog[i].ticket_ms_start ):(0XFFFFFFFF - dog[i].ticket_ms_start + ticket);
			if(ticket_dekay > dog[i].ticket_ms_delay) return false;//��ʧ��
		}
	}
	return true;
}	

/*	�û�����	*/
_Bool WDG_NEW(u32 ticket,u32 * ID)			//���������ع�ID
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

/* ɾ���� */
void WDG_DELETE(u32 ID) 	{dog[ID].ticket_ms_start = 0;}
/* ι������ */
void WDG_FEED(u32 ID)		{dog[ID].ticket_ms_start = get_ticket();}	




