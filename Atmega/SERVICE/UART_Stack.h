


#ifndef UART_STACK_H_
#define UART_STACK_H_

#define STACKSIZE 10
typedef enum
{
	STACKFULL,
	STACKEMPTY,
	DONE
	}EN_stack_status_t;

EN_stack_status_t UART_StackPush(u8 data);
EN_stack_status_t UART_StackPop(u8 *data);

#endif 