#include "StdTypes.h"
#include "UART.h"
#include "UART_Queue.h"

static volatile u8 Busyflag=0;
static s8 rear=-1;
static s8 front=0;
static u8 size=0;
static u8*Tx_queue[QUEUEMAX];

/************************************************************************/
/*				     		Queue Operations                            */
/************************************************************************/
static u8 IsQueueFull(void)
{
	return size==QUEUEMAX;
}

static u8 IsQueueEmpty(void)
{
	return size==0;
}

static u8 Enqueue(u8 *str)
{
	if(!IsQueueFull())
	{
		rear=(rear+1)%QUEUEMAX;
		Tx_queue[rear]=str;
		size++;
		return 1;
	}
	return 0;
}

static u8 Dequeue(u8 **pstr)
{
	if(!IsQueueEmpty())
	{
		*pstr=Tx_queue[front];
		front=(front+1)%QUEUEMAX;
		size--;
		return 1;
	}
	return 0;
}



/*********************************************************** Sending in Interrupt**************************************************************/
static void Tx_Func(void)
{
	static u8 fisrttime_flag=1;
	static u8 notempty=0;
	static u8 iterator=1;
	static u8*str=0;
	if(fisrttime_flag==1)
	{
		/*if the interrupt was not working or stopped and it start again so function send the first char */
		notempty=Dequeue(&str);
		fisrttime_flag=0;
	}
	else if(str[iterator]==0)
	{
		/*if the interrupt was working and it was not the first string in queue in this cycle*/
		notempty=Dequeue(&str);
		iterator=0;
	}
	if(notempty)
	{
		UART_SendNoBlock(str[iterator]);
		iterator++;
	}
	else
	{
		fisrttime_flag=1;
		Busyflag=0;//when the queue is empty so it need the function to start sending the first frame
		iterator=1;//if the interrupt stopped and start to work again the function will send the first so the interrupt will work from the second char
	}
	
}

void UART_SendStringAsyncInit(void)
{
	UART_Tx_SetCallBack(Tx_Func);
	UART_Tx_InterruptEnable();
}

void UART_SendStringAsync(u8*str)
{
	u8 notfull=Enqueue(str);
	if(Busyflag==0&&notfull==1)
	{
		UART_SendNoBlock(str[0]);
		Busyflag=1;//meaning that interrupt is working in background
	}

}




/***********************************************************Diverging Interrupt**************************************************************/
static volatile u8 Doneflag=1;
static void Tx_Func2(void)
{
	Doneflag=1;
}
void UART_SendStringAsyncInit2(void)
{
	UART_Tx_SetCallBack(Tx_Func2);
	UART_Tx_InterruptEnable();
}

void UART_SendStringAsync2Runnable()
{
	static u8*str;
	static u8 iterator=0;
	static u8 notempty;
	if(Doneflag)
	{
		if(iterator==0)
		{
			notempty=Dequeue(&str);
		}
		if(notempty)
		{
			UART_SendNoBlock(str[iterator]);
			iterator++;
			Doneflag=0;
		}
		
	}
	if(str[iterator]==0)
	{
		iterator=0;
	}
}


u8 UART_SendStringAsync2_Setter(u8* str)
{
	return Enqueue(str);
}

