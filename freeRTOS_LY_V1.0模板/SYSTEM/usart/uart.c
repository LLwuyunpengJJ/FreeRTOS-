#include "uart.h"
#include "sys.h"
//-------------------------------------------------------------------------
// VARIABLE DEFINITIONS
//-------------------------------------------------------------------------
uart_stack uart1 = {0};
uart_stack uart2 = {0};
uart_stack uart3 = {0};
uart_stack uart4 = {0};
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
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)uart1.DMA_Buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = blen;
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
//========================================================================================================UART2_init(void)
void UART2_init(void)//WIFI
{
    GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    USART_DeInit(USART2);  //复位串口2
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	USART_ITConfig(USART2, USART_IT_ERR, ENABLE);
    USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
    USART_Cmd(USART2, ENABLE);
	
    /* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//todo
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
    //DMA配置
    DMA_DeInit(DMA1_Channel6);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)uart2.DMA_Buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = blen;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel6, &DMA_InitStructure);

    DMA_Cmd(DMA1_Channel6, ENABLE);	
}
//========================================================================================================UART3_init(void)
void UART3_init(void)/*串口3MC20通信*/
{
	GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE); 	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	USART_DeInit(USART3);  //复位串口3
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	USART_ITConfig(USART3, USART_IT_ERR, ENABLE);
    USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);
    USART_Cmd(USART3, ENABLE);
	
		    /* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//todo
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
    //DMA配置
    DMA_DeInit(DMA1_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART3->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)uart3.DMA_Buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = blen;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);

    DMA_Cmd(DMA1_Channel3, ENABLE);
}
//========================================================================================================UART4_init(void)
void UART4_init(void) /*串口4LCD通信*///TX-PC10 RX-PC11
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 , ENABLE); 	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	USART_DeInit(UART4);  //复位串口3
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(UART4, &USART_InitStructure);
	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);
	USART_ITConfig(UART4, USART_IT_ERR, ENABLE);
	USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);
    USART_Cmd(UART4, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//todo
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	    //DMA配置
    DMA_DeInit(DMA2_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&UART4->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)uart4.DMA_Buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = blen;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA2_Channel3, &DMA_InitStructure);

    DMA_Cmd(DMA2_Channel3, ENABLE);
}
//========================================================================================================UART5_init(void)
void UART5_init(void)/*串口5GPS通信*///TX-PC12 RX-PD2
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//    USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//    
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5 , ENABLE); 	
//	USART_DeInit(UART5);  //复位串口3
//    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(GPIOD, &GPIO_InitStructure);

//    USART_InitStructure.USART_BaudRate = 115200;
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

//    USART_Init(UART5, &USART_InitStructure);
//    USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
//    USART_Cmd(UART5, ENABLE);

//	/* Enable the UART5 Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//todo
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
void USART1_IRQHandler(void)                	//串口1中断服务程序                                      //
{                                                                                                        //
    uint8_t Clear = Clear;                                                                               //
																										 //																									 //
	if (USART_GetFlagStatus(USART1, USART_FLAG_FE) != RESET) 
	{
		USART_ReceiveData(USART1); 
		USART_ClearFlag(USART1, USART_FLAG_FE);
	} 	//
	if(USART_GetFlagStatus(USART1, USART_FLAG_PE) != RESET)         
	{        
		USART_ReceiveData(USART1);  
		USART_ClearFlag(USART1, USART_FLAG_PE);  			  
	}																									 //																									 //
    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) != RESET)                                             	 //
    {                                                                                                    //
		USART_ClearFlag(USART1,USART_FLAG_ORE);                                                                                                 //
        USART_ReceiveData(USART1);                                                                    	 //
    }                                                                                                    //
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)                                             	 //
    {                                                                                                    //
        Clear=USART1->SR;                                                                             	 //
        Clear=USART1->DR;                                                                              	 //
        int IOT_Uart_Rec_Cnt = blen-DMA_GetCurrDataCounter(DMA1_Channel5);              				 //USART2_IRQHandler
        DMA_Cmd(DMA1_Channel5, DISABLE );//关闭DMA                                                 	     //
        if(IOT_Uart_Rec_Cnt>0)                                                           				 //
        {                                                                                                //
            PushUartMsg1(IOT_Uart_Rec_Cnt);                                                              //
        }                                                                                                //
        USART_ClearITPendingBit(USART1,USART_IT_IDLE);                                                 	 //
        DMA_SetCurrDataCounter(DMA1_Channel5,blen);//重新计数                           				 //
        DMA_Cmd(DMA1_Channel5, ENABLE);                                                           	     //
    }                                                                                                    //
}                                                                                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void USART2_IRQHandler(void) //USART2_IRQHandler                                                         //
{                                                                                                        //
    uint8_t Clear = Clear;                                                                               //
																										 //																									 //
	if (USART_GetFlagStatus(USART2, USART_FLAG_FE) != RESET) 
	{
		USART_ReceiveData(USART2); 
		USART_ClearFlag(USART2, USART_FLAG_FE);
	} 	//
	if(USART_GetFlagStatus(USART2, USART_FLAG_PE) != RESET)         
	{        
		USART_ReceiveData(USART2);  
		USART_ClearFlag(USART2, USART_FLAG_PE);  			  
	}																									 //																									 //
    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE) != RESET)                                             	 //
    {                                                                                                    //   
		USART_ClearFlag(USART2,USART_FLAG_ORE);		//
        USART_ReceiveData(USART2);                                                                    	 //
    }                                                                                                    //
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)                                             	 //
    {                                                                                                    //
        Clear=USART2->SR;                                                                             	 //
        Clear=USART2->DR;                                                                              	 //
        int IOT_Uart_Rec_Cnt = blen-DMA_GetCurrDataCounter(DMA1_Channel6);              				 //
        DMA_Cmd(DMA1_Channel6, DISABLE );//关闭DMA                                                 	     //USART2_IRQHandler
        if(IOT_Uart_Rec_Cnt>0)                                                           				 //
        {                                                                                                //
            PushUartMsg2(IOT_Uart_Rec_Cnt);                                                              //
        }                                                                                                //
        USART_ClearITPendingBit(USART2,USART_IT_IDLE);                                                 	 //
        DMA_SetCurrDataCounter(DMA1_Channel6,blen);//重新计数                           				 //
        DMA_Cmd(DMA1_Channel6, ENABLE);                                                           	     //
    }                                                                                                    //
}                                                                                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void USART3_IRQHandler(void) //USART3_IRQHandler                                                         //
{                                                                                                        //
    uint8_t Clear = Clear;                                                                               //
																										 //																										 //
	if (USART_GetFlagStatus(USART3, USART_FLAG_FE) != RESET) 
	{
		USART_ReceiveData(USART3); 
		USART_ClearFlag(USART3, USART_FLAG_FE);
	} 	//
	if(USART_GetFlagStatus(USART3, USART_FLAG_PE) != RESET)         
	{        
		USART_ReceiveData(USART3);  
		USART_ClearFlag(USART3, USART_FLAG_PE);  			  
	}																									 //																									 //
    if(USART_GetFlagStatus(USART3,USART_FLAG_ORE) != RESET)                                             	 //
    {                                                                                                    //                  
		USART_ClearFlag(USART3,USART_FLAG_ORE);		//
        USART_ReceiveData(USART3);                                                                    	 //
    }                                                                                                    //
    if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)                                             	 //
    {                                                                                                    //
        Clear=USART3->SR;                                                                             	 //
        Clear=USART3->DR;                                                                                //
        int IOT_Uart_Rec_Cnt = blen-DMA_GetCurrDataCounter(DMA1_Channel3);             					 //USART3_IRQHandler
        DMA_Cmd(DMA1_Channel3, DISABLE);//关闭DMA                                               		 //
        if(IOT_Uart_Rec_Cnt>0)                                                         					 //
		{                                                                                                //
			PushUartMsg3(IOT_Uart_Rec_Cnt);                                                        		 //
		}                                                                                                //
        USART_ClearITPendingBit(USART3,USART_IT_IDLE);                                                	 //
        DMA_SetCurrDataCounter(DMA1_Channel3,blen);//重新计数                          					 //
        DMA_Cmd(DMA1_Channel3, ENABLE);                                                          		 //
    }                                                                                                    //
}                                                                                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void UART4_IRQHandler(void) //USART3_IRQHandler                                                         //
{                                                                                                        //
    uint8_t Clear = Clear;                                                                               //
																										 //																										 //
	if (USART_GetFlagStatus(UART4, USART_FLAG_FE) != RESET) 
	{
		USART_ReceiveData(UART4); 
		USART_ClearFlag(UART4, USART_FLAG_FE);
	} 	//
	if(USART_GetFlagStatus(UART4, USART_FLAG_PE) != RESET)         
	{        
		USART_ReceiveData(UART4);  
		USART_ClearFlag(UART4, USART_FLAG_PE);  			  
	}																									 //																									 //
    if(USART_GetFlagStatus(UART4,USART_FLAG_ORE) != RESET)                                             	 //
    {                                                                                                    //        
		USART_ClearFlag(UART4,USART_FLAG_ORE);		//
        USART_ReceiveData(UART4);                                                                    	 //
    }                                                                                                    //
    if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)                                             	 //
    {                                                                                                    //
        Clear=UART4->SR;                                                                             	 //
        Clear=UART4->DR;                                                                                //
        int IOT_Uart_Rec_Cnt = blen-DMA_GetCurrDataCounter(DMA2_Channel3);             					 //USART4_IRQHandler
        DMA_Cmd(DMA2_Channel3, DISABLE);//关闭DMA                                               		 //
        if(IOT_Uart_Rec_Cnt>0)                                                         					 //
		{                                                                                                //
			PushUartMsg4(IOT_Uart_Rec_Cnt);                                                        		 //
		}                                                                                                //
        USART_ClearITPendingBit(UART4,USART_IT_IDLE);                                                	 //
        DMA_SetCurrDataCounter(DMA2_Channel3,blen);//重新计数                          					 //
        DMA_Cmd(DMA2_Channel3, ENABLE);                                                          		 //
    }                                                                                                    //
}                                                                                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void IOT_UART_Send_Array(USART_TypeDef* USARTx,u8 * send_array,u32 num)       //**
{                                                                             //**
    u32 i=0;                                                                  //**
    while(i<num)                                                              //**
    {                                                                         //**
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);          //**IOT_UART2_Send_Array
        USART_SendData(USARTx,send_array[i]);                                 //**
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);           //**
        i++;                                                                  //**
    }                                                                         //**
}                                                                             //**
//============================================================================//**
void PushUartMsg(uart_stack * uart,u32 Uart_Rec_Cnt)                          ////   
{                                                                             ////
	if(uart->cnt >= buff) return;                                             //// 
	if(Uart_Rec_Cnt<blen)                                                     //// 
	{                                                                         //// 
		if(uart->write >= buff) uart->write = 0;                              ////
		memset(uart->RxBuffer[uart->write],0,blen);                           //// 
		memcpy(uart->RxBuffer[uart->write],uart->DMA_Buffer,Uart_Rec_Cnt);    ////		
		uart->cnt++;                                                          //// 
		uart->write++;                                                        ////
	}                                                                         ////
}                                                                             ////
																			  ////
u8 * PopUartMsg(uart_stack * uart)                                            ////             
{                                                                             ////
	if(uart->cnt>0)                                                           //// 
	{                                                                         //// 
		uart->cnt--;                                                          //// 
		if(uart->read >= buff)                                                ////
			uart->read = 0;                                                   ////
		uart->read++;                                                         ////
		return (u8*)uart->RxBuffer[uart->read-1];                             ////
	}                                                                         ////
	else                                                                      ////
		return NULL;                                                          ////
}                                                                             ////
																			  ////
/////////////////////////////////////////////////////////////////////////////////////



