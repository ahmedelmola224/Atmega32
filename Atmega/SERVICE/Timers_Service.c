#include "Timers_Service.h"
#include "LCD.h"

/**************************************************Set Interrupt Time*****************************************************************/

/*works on ctc mode*/
static void Timer1_Func(void);
static u16 NumOfOvf=0;
static void (*fptrtimer)(void);

void Timer1_SetInterrupt_s(u16 time,void(*LocalFptr)(void))
{
	OCR1A=999;
	NumOfOvf=time*1000;
	fptrtimer=LocalFptr;
	Timer1_OCA_SetCallBack(Timer1_Func);
	Timer1_OCA_InterruptEnable();
	
}

static void Timer1_Func(void)
{
	static u32 c=0;
	c++;
	if(c==NumOfOvf)
	{
		c=0;
		fptrtimer();
	}
	
}


/*works on ctc mode*/
void Timer1_SetInterrupt_ms(u16 time,void(*LocalFptr)(void))
{
	OCR1A=(time*1000)-1;
	Timer1_OCA_SetCallBack(LocalFptr);
	Timer1_OCA_InterruptEnable();
	
}
/*works on ctc mode*/
void Timer1_SetInterrupt_us(u16 time,void(*LocalFptr)(void))
{
	OCR1A=time-1;
	Timer1_OCA_SetCallBack(LocalFptr);
	Timer1_OCA_InterruptEnable();
}


/**************************************************PWM*****************************************************************/


void PWM_Init(void)
{
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);
	 Timer1_OCRB1Mode(OCRB_INVERTING);
}

void PWM_Freq_HZ(u16 freq)
{
	if(freq==0);
	else
	{
		u16 Ttotal=(u32)1000000/freq;
		if(Ttotal>0)
		OCR1A=Ttotal-1;
		else
		OCR1A=0;
	}
}

void PWM_Freq_KHZ(u16 freq)
{
	if(freq==0);
	else
	{
		u16 Ttotal=(u16)1000/freq;
		if(Ttotal>0)
		OCR1A=Ttotal-1;
		else
		OCR1A=0;
	}
}

void PWM_Duty(u16 duty)
{
	if(duty<=100)
	{
		u16 Ton=(u32)(duty)*(OCR1A+1)/100;
		if(Ton>0)
		OCR1B=Ton-1;
		else
		OCR1B=0;
	}
}


static void Timer1_OVF_Func(void);
static void Timer1_ICU_Func(void);
static volatile u16 t1,t2,t3,c,con,coff;
static volatile u8 flag;

void PWM_Measure(u32 *pfreq ,u8 *pduty)
{
	u16 Ton,Toff;
	OCR1A=timer1_top;
	Timer1_ICU_SetCallBack(Timer1_ICU_Func);
	Timer1_OVF_SetCallBack(Timer1_OVF_Func);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	Timer1_OVF_InterruptEnable();
	flag=0;
	while(flag<3);
	Ton=((u32)con*timer1_top)+(t2-t1);
	Toff=((u32)coff*timer1_top)+(t3-t2);
	*pduty=((u32)Ton*100)/((u32)Ton+Toff);
	*pfreq=(u32)1000000/((u32)Ton+Toff);
}


static void Timer1_ICU_Func(void)
{	
	if(flag==0)
	{
		
		Timer1_InputCaptureEdge(FALLING);
		t1=ICR1;
		c=0;
		flag=1;
		
	}
	else if(flag==1)
	{
		Timer1_InputCaptureEdge(RISING);
		t2=ICR1;
		con=c;
		c=0;
		flag=2;
		
	}
	else if(flag==2)
	{
		t3=ICR1;
		coff=c;
		flag=3;
		Timer1_OVF_InterruptDisable();
		Timer1_ICU_InterruptDisable();
	}
	
}


static void Timer1_OVF_Func(void)
{
	c++;
}


