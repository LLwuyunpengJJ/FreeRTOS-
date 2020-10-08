#include "watchdog.h"
u8 WWDG_CNT=0X7F;
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

void IWDG_Feed(void)// 喂狗
{
    // 把重装载寄存器的值放到计数器中，喂狗，防止IWDG复位
    // 当计数器的值减到0的时候会产生系统复位
    IWDG_ReloadCounter();
}

//=================================================================================

//void WWDG_Init(u8 tr,u8 wr,u32 fprer)
//{
//		NVIC_InitTypeDef NVIC_InitStructure;
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE); //使能窗口看门狗时钟

//		WWDG_CNT=tr&WWDG_CNT; //初始化WWDG_CNT. 
//		WWDG_SetPrescaler(fprer); //设置分频值
//		WWDG_SetWindowValue(wr); //设置窗口值
//		//WWDG_SetCounter(WWDG_CNT);//设置计数值
//		WWDG_Enable(WWDG_CNT); //开启看门狗

//		NVIC_InitStructure.NVIC_IRQChannel=WWDG_IRQn; //窗口看门狗中断
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //抢占优先级为2
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级为3
//		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //使能窗口看门狗
//		NVIC_Init(&NVIC_InitStructure);

//		WWDG_ClearFlag();//清除提前唤醒中断标志位
//		WWDG_EnableIT();//开启提前唤醒中断
//}
////窗口看门狗中断服务程序 
//void WWDG_IRQHandler(void)
//{
//		WWDG_SetCounter(WWDG_CNT); //重设窗口看门狗值
//		WWDG_ClearFlag();//清除提前唤醒中断标志位
//}

/*
STM32F4的WWDG库 
WWDG计数器输入时钟是由 APB1时钟分频而来： 
WWDG 计数器时钟 = PCLK1 / Prescaler 
WWDG 溢出时间 = (WWDG counter clock) * (counter value) 
最大最小溢出时间： @42 MHz(PCLK1): ~97.5 us / 49.9 ms 
如何使用看门狗驱动 
·通过函数RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE)使能窗口看门狗时钟 
·通过函数WWDG_SetPrescaler()设置看门狗分频。 
·设置WWDG计数器数值，通过函数WWDG_Enable（）启动WWDG，情动WWDG以后，计数器的数值设置要大于0x40，防止立即产生复位 
·用户可以悬着是否产生EWI中断，在此中断计数器到0x40时产生，一旦是能。系统复位时将无法将其关闭 
·在阻止系统产生福诶的正常操作期间，用户需要在每个时间间隔通过函数WWDG_SetCounter（）刷新计数器没刷新操作只能在计数器值小于设定窗口只时进行，窗口只通过函数WWDG_SetWindowValue()设定。

分频器，窗口刷新，计数器配置函数 
void WWDG_DeInit(void) 
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler) 
void WWDG_SetWindowValue(uint8_t WindowValue) 
void WWDG_EnableIT(void) 
void WWDG_SetCoounter(uint8_t Counter) 
独立看门狗激活函数 
void WWDG_Enable(uint8_t Counter) 
中断标志管理 
FlagStatus WWDG_GetFlagStatue(void) 
void WWDG_CLearFlag(void)
--------------------- 
版权声明：本文为CSDN博主「大大大大熊ovo」的原创文章，遵循CC 4.0 by-sa版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/z312811966/article/details/51394154
*/
