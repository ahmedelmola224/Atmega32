


#ifndef UART_QUEUE_H_
#define UART_QUEUE_H_

#define QUEUEMAX (u8)10 


void UART_SendStringAsyncInit(void);
void UART_SendStringAsync(u8*str);

void UART_SendStringAsyncInit2(void);
void UART_SendStringAsync2Runnable();
u8 UART_SendStringAsync2_Setter(u8* str);

#endif 