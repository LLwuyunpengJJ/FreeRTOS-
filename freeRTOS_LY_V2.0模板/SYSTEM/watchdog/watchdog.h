#ifndef __WATCH_H
#define __WATCH_H	
#include "sys.h"

void IWDG_Config(uint8_t prv ,uint16_t rlv);
void IWDG_Feed(void);// Î¹¹·
	
//void WWDG_Init(u8 tr,u8 wr,u32 fprer);
//void WWDG_IRQHandler(void);
#endif
