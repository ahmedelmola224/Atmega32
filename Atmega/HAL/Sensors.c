#include "StdTypes.h"
#include "ADC_interface.h"
#include "Sensors.h"
#include "Sensors_private.h"

static u16 temp_read[10]={0};
static u16 temp;
static u8 TEMPF_AdcRead(u16*pdata)
{
	u16 adc;
	ADC_StartConversion(LM35_CH);
	if(ADC_PeriodicRead(&adc))
	{
		*pdata=(adc*(u32)1500)/307;
		return 1;
	}
	return 0;
	
}

void TempF_Init(void)
{
	for(u8 i=0;i<10;i++)
	{
		while(!TEMPF_AdcRead(temp_read+i));
	}
	TEMPF_Avg();
	
}
void TEMPF_Runnable(void)
{
	static u8 counter=0;
	if(TEMPF_AdcRead(temp_read+(counter%10)))
	{
		counter++;
		TEMPF_Avg();
	}	
}

u16 TEMPF_GetRead(void)
{
	return temp;
}

static void TEMPF_Avg(void)
{
	u32 sum=0;
	for(u8 i=0;i<10;i++)
	{
		sum+=temp_read[i];
	}
	temp=sum/10;
}

u16 PRESSURE_Read()
{
	u16 adc;
	u16 pressure;
	adc=ADC_Read(MPX4115_CH);
	pressure=(((u32)(adc-55)*1000)/921)+150;
	return pressure;
}
u16 TEMP_Read(void)
{
	u16 temp ,adc;
	adc=ADC_Read(LM35_CH);
	temp=(adc*(u32)1500)/307;
	return temp;
}