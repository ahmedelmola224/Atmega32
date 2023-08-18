


#ifndef UART_SERVICE_H_
#define UART_SERVICE_H_

void UART_SendString(u8*str);
void UART_ReceieveString(u8*str);
void UART_ReceieveNumber(u32 *pnum);
void UART_SendNumber(u32 num);
void UART_SendStringCheckSum(u8*str);
u8 UART_ReceieveStringCheckSum(u8*str);
void UART_SendStringAsyncInit(void);
void UART_SendStringAsync(u8*str);
void UART_SendStringAsyncInit2(void);
void UART_SendStringAsyncRunnable();
u8 UART_SendStringAsync2_Setter(u8* str);

u8 UART_ReceieveAsyncGetter(u8*str);
void UART_ReceieveAsyncInit(void);

#endif 