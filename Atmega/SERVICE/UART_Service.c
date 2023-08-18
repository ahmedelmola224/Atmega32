#include "StdTypes.h"
#include "UART.h"
#include "UART_Service.h"
#include "LCD.h"


//sync
void UART_SendString(u8*str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
}

//sync
void UART_ReceieveString(u8*str)
{
	u8 i;
	str[0]=Uart_Receieve();
	for(i=0;str[i]!=0x0D;)
	{
		i++;
		str[i]=Uart_Receieve();
	}
	str[i]=0;
}

void UART_SendNumber(u32 num)
{
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));
	/*using char pointer*/
	/*u8*ptr=&num;
	UART_Send(ptr[0]);
	UART_Send(ptr[1]);
	UART_Send(ptr[2]);
	UART_Send(ptr[3]);*/
}

void UART_ReceieveNumber(u32 *pnum)
{
	u32 num=0;
	u8 b1=Uart_Receieve()-'0';
	u8 b2=Uart_Receieve()-'0';
	u8 b3=Uart_Receieve()-'0';
	u8 b4=Uart_Receieve()-'0';
	num=(u32)(b1)|(u32)(b2)<<8|(u32)(b3)<<16|(u32)(b4)<<24;
	*pnum=num;
	/*using char pointer*/
	/*u8*ptr=&num;
	ptr[0]=Uart_Receieve();
	ptr[1]=Uart_Receieve();
	ptr[2]=Uart_Receieve();
	ptr[3]=Uart_Receieve();*/
}

void UART_SendStringCheckSum(u8*str)
{
	u8 len=0;
	u16 sum=0;
	for(len=0;str[len];len++);
	UART_Send(len);
	for(u8 i=0;str[i];i++)
	{
		UART_Send(str[i]);
		sum+=str[i];
	}
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
}

u8 UART_ReceieveStringCheckSum(u8*str)
{
	u8 b0,b1,i;
	u8 len=Uart_Receieve();
	u16 sum_rec=0,sum_calc=0;
	for(i=0;i<len;i++)
	{
		str[i]=Uart_Receieve();
		sum_calc+=str[i];
	}
	str[i]=0;
	b0=Uart_Receieve();
	b1=Uart_Receieve();
	sum_rec=(u16)b0|((u16)b1<<8);
	if(sum_calc==sum_rec)
	{
		return 1;
	}
	return 0;
}


u8 checkendian(void)
{
	u8 x=1;
	if(*(u8*)&x==1)
	{
		return 1;//little
	}
	else
	{
		return 0;//big
	}
}

u32 convertindian(u32 num)
{
	return num<<24|num>>24|((num<<8)&0x00ff0000)|((num>>8)&0x0000ff00);
}




/*********************************************************Uart Rx Double Buffer**************************************************/
static volatile u8 ReadyFlag=0;
static u8 UartBuffer[2][8];
static volatile u8 BufferNumber=0;
static void Rx_Func(void)
{
	static u8 i=0;
	UartBuffer[BufferNumber][i]=UART_ReceieveNoBlock();
	i++;
	if(i==8)
	{
		ReadyFlag=1;
		BufferNumber^=1;
		i=0;
	}
}

void UART_ReceieveAsyncInit(void)
{
	UART_Rx_SetCallBack(Rx_Func);
	UART_Rx_InterruptEnable();
}

u8 UART_ReceieveAsyncGetter(u8*str)
{
	/*the problem happens if the double buffer is full and you didn't take the data the interrupt will overwrite*/
	u8 i;
	if(ReadyFlag==0)
	{
		return 0;
	}
	for(i=0;i<8;i++)
	{
		str[i]=UartBuffer[BufferNumber^1][i];
	}
	ReadyFlag=0;
	return 1;
}