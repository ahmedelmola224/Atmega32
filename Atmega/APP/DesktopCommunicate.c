#include "StdTypes.h"
#include "DIO_interface.h"
#include "UART.h"
#include "UART_Service.h"
#include "RGB.h"
#include "DesktopCommunicate.h"
#include "DesktopCommunicate_private.h"



static Element_type ArrayOfActions[NUMBEROFFUNCTIONS]={{LedOn,"ledon"},{LedOff,"ledoff"},{RelayOn,"relayon"},{RelayOff,"relayoff"},{RGB,"rgb"}};
void DesktopCommunicate_Init(void)
{
	RGB_Init();
	UART_Init();
}

void DesktopCommunicate_Runnable(void)
{
	u8 str[20];
	u8 numInStr;
	s8 functionindex;
	UART_ReceieveString(str);
	StringSplit(str,&numInStr);
	functionindex=GetFunctionIndex(str);
	if(functionindex>=0)
	ArrayOfActions[functionindex].pf(numInStr);
}

static u8 GetFunctionIndex(u8*str)
{
	u8 i,index=-1;
	for(i=0;i<NUMBEROFFUNCTIONS;i++)
	{
		if(StringCmp(str,(*(ArrayOfActions+i)).pstr)==1)
		{
			index=i;
			break;
		}
	}
	return index;
}

static void StringSplit(u8*str,u8*num)
{
	u8 i;
	*num=0;
	for( i=0;str[i]!=' ';i++);
	str[i]=0;
	i++;
	for(;str[i];i++)
	{
		if(str[i]>='0'&&str[i]<='9')
		{
			*num=(*num)*10+str[i]-'0';
		}
	}
}

static u8 StringCmp(u8*str1,u8*str2)
{
	for(u8 i=0;str1[i]||str2[i];i++)
	{
		if(str1[i]!=str2[i])
		{
			return 0;
		}
	}
	return 1;
	
}

static void LedOn(u8 lednumber)
{
	if(lednumber>=0&&lednumber<8)
	DIO_WritePin(FIRSTLEDPIN+lednumber,HIGH);
}

static void LedOff(u8 lednumber)
{
	if(lednumber>=0&&lednumber<8)
	DIO_WritePin(FIRSTLEDPIN+lednumber,LOW);
}

static void RelayOn(u8 relaynumber)
{
	if(relaynumber==0||relaynumber==1)
	{
		DIO_WritePin(RELAYPIN+relaynumber,HIGH);
	}
}

static void RelayOff(u8 relaynumber)
{
	if(relaynumber==0||relaynumber==1)
	{
		DIO_WritePin(RELAYPIN+relaynumber,LOW);
	}
}

static void RGB(u8 color)
{
	
	RGB_SetColor(color);
}