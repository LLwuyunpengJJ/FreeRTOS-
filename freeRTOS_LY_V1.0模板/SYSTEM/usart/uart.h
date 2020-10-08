#ifndef _IOT_UART_H_
#define _IOT_UART_H_
#include "stm32f10x.h"    

#define buff 10
#define blen 350

typedef struct {
	char DMA_Buffer[blen];
	char RxBuffer[buff][blen];
	char read;
	char write;
	char cnt;
}uart_stack;

extern uart_stack uart1;
extern uart_stack uart2;
extern uart_stack uart3;

void UART1_init(void);
void UART2_init(void);
void UART3_init(void);	
void UART4_init(void);
void UART5_init(void);	

//======================================Õ»»º´æ
void PushUartMsg(uart_stack * uart,u32 Uart_Rec_Cnt); 
#define PushUartMsg1(n) PushUartMsg(&uart1,n)
#define PushUartMsg2(n) PushUartMsg(&uart2,n)
#define PushUartMsg3(n) PushUartMsg(&uart3,n)
#define PushUartMsg4(n) PushUartMsg(&uart4,n)

u8 * PopUartMsg(uart_stack * uart);
#define PopUartMsg1() PopUartMsg(&uart1)
#define PopUartMsg2() PopUartMsg(&uart2)
#define PopUartMsg3() PopUartMsg(&uart3)
#define PopUartMsg4() PopUartMsg(&uart4)

//======================================´®¿Ú
void IOT_UART_Send_Array(USART_TypeDef* USARTx,u8 * send_array,u32 num);
#define Uart1send(tx_buf,buflen)   IOT_UART_Send_Array(USART1,(u8 *)tx_buf, buflen)
#define Uart2send(tx_buf,buflen)   IOT_UART_Send_Array(USART2,(u8 *)tx_buf, buflen)
#define Uart3send(tx_buf,buflen)   IOT_UART_Send_Array(USART3,(u8 *)tx_buf, buflen)
#define Uart4send(tx_buf,buflen)   IOT_UART_Send_Array(USART4,(u8 *)tx_buf, buflen)
#define Uart5send(tx_buf,buflen)   IOT_UART_Send_Array(USART5,(u8 *)tx_buf, buflen)
#define Uart1sends(tx_buf)   IOT_UART_Send_Array(USART1,(u8 *)tx_buf, strlen((const char *)tx_buf))
#define Uart2sends(tx_buf)   IOT_UART_Send_Array(USART2,(u8 *)tx_buf, strlen((const char *)tx_buf))
#define Uart3sends(tx_buf)   IOT_UART_Send_Array(USART3,(u8 *)tx_buf, strlen((const char *)tx_buf))
#define Uart4sends(tx_buf)   IOT_UART_Send_Array(USART4,(u8 *)tx_buf, strlen((const char *)tx_buf))
#define Uart5sends(tx_buf)   IOT_UART_Send_Array(USART5,(u8 *)tx_buf, strlen((const char *)tx_buf))
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
#endif

