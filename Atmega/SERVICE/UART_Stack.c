#include "StdTypes.h"
#include "UART.h"
#include "UART_Stack.h"


static u8 Stack[STACKSIZE];
static u8 Sp=0;

EN_stack_status_t UART_StackPush(u8 data)
{
	EN_stack_status_t state =STACKFULL;
	if(Sp<STACKSIZE)
	{
		Stack[Sp]=data;
		Sp++;
		state=DONE;
	}
	return state;
}

EN_stack_status_t UART_StackPop(u8 *data)
{
	EN_stack_status_t state =STACKEMPTY;
	if(Sp>0)
	{
		Sp--;
		*data=Stack[Sp];
		state=DONE;
	}
	return state;
}

