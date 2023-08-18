
#include "ULTRASONIC.h"

static volatile u16 t1,t2,c;
static volatile u8 flag=0;
static u8 Periodicflag=0;

static void OVF_Interrupt(void);
static void Ultrasonic_Interrupt(void);

void ULTRASONIC_Init(void)
{
	Timer1_ICU_SetCallBack(Ultrasonic_Interrupt);
	Timer1_OVF_SetCallBack(OVF_Interrupt);
	
}
u8 ULTRASONIC_GetDistance(ULTRASONIC_type2 us ,u16* pdistance)
{
	u16 t=0,count=0;//max 4m->23200us "run time out for busy wait" ;
	flag=0;
	Timer1_ICU_InterruptEnable();
	Timer1_OVF_InterruptEnable();
	Timer1_InputCaptureEdge(RISING);
	DIO_WritePin(us,HIGH);
	_delay_us(10);
	DIO_WritePin(us,LOW);
	while((flag<2)&&(count<23200))
	{
		count++;
		_delay_us(1);
	}
	
	if(flag==2)
	{
		t=c*TIMER_TOP+((s32)t2-t1);
		*pdistance=t/58;
		return 1;
	}
	return 0;
}

void ULTRASONIC_Start(ULTRASONIC_type2 us)
{
	if(Periodicflag==0)
	{
	flag=0;
	Timer1_ICU_InterruptEnable();
	Timer1_OVF_InterruptEnable();
	Timer1_InputCaptureEdge(RISING);
	DIO_WritePin(us,HIGH);
	_delay_us(10);
	DIO_WritePin(us,LOW);
	Periodicflag=1;
	}
}

u8 ULTRASONIC_GetDistance_Periodic(u16*pdistance)
{
	u16 t;
	if(flag==2)
	{
		t=c*TIMER_TOP+(s32)((s32)t2-t1);
		*pdistance=t/58;
		Periodicflag=0;
		return 1;
	}
	return 0;
}



static void OVF_Interrupt(void)
{
	c++;
}

static void Ultrasonic_Interrupt(void)
{
	
	if(flag==0)
	{
		t1=ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
		c=0;
	}
	else if(flag==1)
	{
		t2=ICR1;
		flag=2;
		Timer1_ICU_InterruptDisable();
		Timer1_OVF_InterruptDisable();
	}
	
}
