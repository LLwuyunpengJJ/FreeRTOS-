#include "watchdog.h"
u8 WWDG_CNT=0X7F;
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

void IWDG_Feed(void)// ι��
{
    // ����װ�ؼĴ�����ֵ�ŵ��������У�ι������ֹIWDG��λ
    // ����������ֵ����0��ʱ������ϵͳ��λ
    IWDG_ReloadCounter();
}

//=================================================================================

//void WWDG_Init(u8 tr,u8 wr,u32 fprer)
//{
//		NVIC_InitTypeDef NVIC_InitStructure;
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE); //ʹ�ܴ��ڿ��Ź�ʱ��

//		WWDG_CNT=tr&WWDG_CNT; //��ʼ��WWDG_CNT. 
//		WWDG_SetPrescaler(fprer); //���÷�Ƶֵ
//		WWDG_SetWindowValue(wr); //���ô���ֵ
//		//WWDG_SetCounter(WWDG_CNT);//���ü���ֵ
//		WWDG_Enable(WWDG_CNT); //�������Ź�

//		NVIC_InitStructure.NVIC_IRQChannel=WWDG_IRQn; //���ڿ��Ź��ж�
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //��ռ���ȼ�Ϊ2
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�Ϊ3
//		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //ʹ�ܴ��ڿ��Ź�
//		NVIC_Init(&NVIC_InitStructure);

//		WWDG_ClearFlag();//�����ǰ�����жϱ�־λ
//		WWDG_EnableIT();//������ǰ�����ж�
//}
////���ڿ��Ź��жϷ������ 
//void WWDG_IRQHandler(void)
//{
//		WWDG_SetCounter(WWDG_CNT); //���贰�ڿ��Ź�ֵ
//		WWDG_ClearFlag();//�����ǰ�����жϱ�־λ
//}

/*
STM32F4��WWDG�� 
WWDG����������ʱ������ APB1ʱ�ӷ�Ƶ������ 
WWDG ������ʱ�� = PCLK1 / Prescaler 
WWDG ���ʱ�� = (WWDG counter clock) * (counter value) 
�����С���ʱ�䣺 @42 MHz(PCLK1): ~97.5 us / 49.9 ms 
���ʹ�ÿ��Ź����� 
��ͨ������RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE)ʹ�ܴ��ڿ��Ź�ʱ�� 
��ͨ������WWDG_SetPrescaler()���ÿ��Ź���Ƶ�� 
������WWDG��������ֵ��ͨ������WWDG_Enable��������WWDG���鶯WWDG�Ժ󣬼���������ֵ����Ҫ����0x40����ֹ����������λ 
���û����������Ƿ����EWI�жϣ��ڴ��жϼ�������0x40ʱ������һ�����ܡ�ϵͳ��λʱ���޷�����ر� 
������ֹϵͳ�������������������ڼ䣬�û���Ҫ��ÿ��ʱ����ͨ������WWDG_SetCounter����ˢ�¼�����ûˢ�²���ֻ���ڼ�����ֵС���趨����ֻʱ���У�����ֻͨ������WWDG_SetWindowValue()�趨��

��Ƶ��������ˢ�£����������ú��� 
void WWDG_DeInit(void) 
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler) 
void WWDG_SetWindowValue(uint8_t WindowValue) 
void WWDG_EnableIT(void) 
void WWDG_SetCoounter(uint8_t Counter) 
�������Ź������ 
void WWDG_Enable(uint8_t Counter) 
�жϱ�־���� 
FlagStatus WWDG_GetFlagStatue(void) 
void WWDG_CLearFlag(void)
--------------------- 
��Ȩ����������ΪCSDN�������������ovo����ԭ�����£���ѭCC 4.0 by-sa��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/z312811966/article/details/51394154
*/
