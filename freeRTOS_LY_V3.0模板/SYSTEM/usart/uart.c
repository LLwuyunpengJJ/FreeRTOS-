#include "uart.h"
#include "stdio.h"
#include "./system_task/semaphore_init.h"
#include "FreeRTOS.h"
#include "semphr.h"
//======================================================================================================UART1_init(void)
#pragma import(__use_no_semihosting)                            
struct __FILE {int handle;}__stdout;
void _sys_exit(int x){x = x; } 
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1 , (uint8_t) ch);
    while (USART_GetFlagStatus(USART1 , USART_FLAG_TC) == RESET){}
    return ch;
}
#define debug_uart_buffer_len 100
static char DMA_Buffer[debug_uart_buffer_len];
static char uart_Buffer[debug_uart_buffer_len];
void UART1_init(void)//调试
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_USART1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	USART_DeInit(USART1);  //复位串口1
	

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate   = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;
    USART_InitStructure.USART_Parity     = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;

    /* Enable the USART1 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn ;//todo
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Init(USART1 , &USART_InitStructure);
    USART_ITConfig(USART1 , USART_IT_IDLE, ENABLE);
	USART_ITConfig(USART1, USART_IT_ERR, ENABLE);
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
    USART_Cmd(USART1 , ENABLE);
	
    //DMA配置
    DMA_DeInit(DMA1_Channel5);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)DMA_Buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = debug_uart_buffer_len;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);
	
    DMA_Cmd(DMA1_Channel5, ENABLE);
}

void USART1_IRQHandler(void)                	//串口1中断服务程序                             
{                                                                                               
    uint8_t Clear = Clear;                                                                      
	if (USART_GetFlagStatus(USART1, USART_FLAG_FE) != RESET) 
	{
		USART_ReceiveData(USART1); 
		USART_ClearFlag(USART1, USART_FLAG_FE);
	} 	//
	if(USART_GetFlagStatus(USART1, USART_FLAG_PE) != RESET)         
	{        
		USART_ReceiveData(USART1);  
		USART_ClearFlag(USART1, USART_FLAG_PE);  			  
	}									
    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) != RESET)                                     
    {                                                                                           
        USART_ReceiveData(USART1);
		USART_ClearFlag(USART1,USART_FLAG_ORE);                                                 
    }                                                                                           
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)                                       
    {                                                                                           
        Clear=USART1->SR;                                                                       
        Clear=USART1->DR;                                                                       
        int IOT_Uart_Rec_Cnt = debug_uart_buffer_len-DMA_GetCurrDataCounter(DMA1_Channel5);              		
        DMA_Cmd(DMA1_Channel5, DISABLE );//关闭DMA                                              
        if(IOT_Uart_Rec_Cnt>0)                                                           		
        {                                                                                       
			#if SYSTEM_SUPPORT_OS			
			BaseType_t xHigherPriorityTaskWoken;
			xQueueSendFromISR(Uart1_Message_Queue,DMA_Buffer,&xHigherPriorityTaskWoken);//向队列中发送数据
			memset(DMA_Buffer,0,debug_uart_buffer_len);//清除数据接收缓冲区USART_RX_BUF,用于下一次数据接收
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//如果需要的话进行一次任务切换    
			#endif														
        }                                                                                       
        USART_ClearITPendingBit(USART1,USART_IT_IDLE);                                          
        DMA_SetCurrDataCounter(DMA1_Channel5,debug_uart_buffer_len);//重新计数                           		
        DMA_Cmd(DMA1_Channel5, ENABLE);                                                         
    }                                                                                           
}   

u8 * PopUartMsg1(u32 delay_t)                                               
{
	 if(Uart1_Message_Queue != NULL)
	 {
		memset(uart_Buffer,0,debug_uart_buffer_len);
		if(xQueueReceive(Uart1_Message_Queue,uart_Buffer,delay_t))//请求消息Key_Queue
			return (u8 *)uart_Buffer;
	 }	
	 return NULL;
}  
