#define ULTRASERVICE
#include "UltraSonic_service.h"

static u16 DistanceArray[2][ULTRASONIC_NUMBER]={{0,0,0,0},{0,0,0,0}};
u8 ArrayFlag=3;
u8 UltrasonicFlag=0;


void ULTRASONIC_Group_Init(void)
{
	u8 i=0;
	ULTRASONIC_Init();
	while(i<ULTRASONIC_NUMBER)
	{
		ULTRASONIC_GetDistance(UltraSonicArray[i],&DistanceArray[0][i]);
		i++;
		_delay_ms(20);
	}
	ArrayFlag=0;
}

void UltraSonic_Runnable(void)
{
	u16 distance=0;
	ULTRASONIC_Start(UltraSonicArray[UltrasonicFlag]);
	if(ULTRASONIC_GetDistance_Periodic(&distance))
	{
		DistanceArray[ArrayFlag^(u8)1][UltrasonicFlag]=distance;
		UltrasonicFlag++;
	}
	if(UltrasonicFlag>=ULTRASONIC_NUMBER)
	{
		ArrayFlag=ArrayFlag^1;
		UltrasonicFlag=0;
	}
	
}



void UltraSonic_Group_GetRead(u16* usarray)
{
	
	for(u8 i=0;i<ULTRASONIC_NUMBER;i++)
	usarray[i]=DistanceArray[ArrayFlag][i];
}