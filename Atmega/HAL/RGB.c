#define RGBFILE 
#include "RGB.h"

void RGB_Init(void)
{
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	TIMER0_OC0Mode(OC0_INVERTING);
	Timer1_OCRB1Mode(OCRB_INVERTING);
	Timer1_OCRA1Mode(OCRA_INVERTING);
	ICR1=255;
}




void RGB_SetDuty(u8 r,u8 g,u8 b)
{
	if((r<=(u8)255)&&(g<=(u8)255)&&(b<=(u8)255))
	{
		REDPIN=r;
		GREENPIN=g;
		BLUEPIN=b;
	}
}


void RGB_SetColor(u8 color)
{
	REDPIN=ArrayOfColors[color][R];
	GREENPIN=ArrayOfColors[color][G];
	BLUEPIN=ArrayOfColors[color][B];
}


void RGB_RelaxMode(u8 color1,u8 color2)
{
	u8 currentrgb[3]={ArrayOfColors[color1][0],ArrayOfColors[color1][1],ArrayOfColors[color1][2]};
	RGB_SetColor(color1);
	_delay_ms(10);
	while(currentrgb[0]!=ArrayOfColors[color2][0]||currentrgb[1]!=ArrayOfColors[color2][1]||currentrgb[2]!=ArrayOfColors[color2][2])
	{
		
		if(currentrgb[0]>ArrayOfColors[color2][0])
		{
			currentrgb[0]--;
		}
		else if(currentrgb[0]<ArrayOfColors[color2][0])
		{
			currentrgb[0]++;
		}
		if(currentrgb[1]>ArrayOfColors[color2][1])
		{
			currentrgb[1]--;
		}
		else if(currentrgb[1]<ArrayOfColors[color2][1])
		{
			currentrgb[1]++;
		}
		if(currentrgb[2]>ArrayOfColors[color2][2])
		{
			currentrgb[2]--;
		}
		else if(currentrgb[2]<ArrayOfColors[color2][2])
		{
			currentrgb[2]++;
		}
		RGB_SetDuty(currentrgb[0],currentrgb[1],currentrgb[2]);
		_delay_us(1500);//last edit here _delay_ms(10);
	}
	
}