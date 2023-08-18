
/*All functions work on 1us tick time*/

#ifndef TIMERS_SERVICE_H_
#define TIMERS_SERVICE_H_
#include "StdTypes.h"
#include "MemoryMap.h"
#include "Timers.h"

extern u16 timer1_top;//you need to define the top of the timer1 

void Timer1_SetInterrupt_s(u16 time,void(*LocalFptr)(void));
void Timer1_SetInterrupt_ms(u16 time,void(*LocalFptr)(void));//ctc mode
void Timer1_SetInterrupt_us(u16 time,void(*LocalFptr)(void));//ctc mode
void PWM_Init(void);//fast pwm
void PWM_Freq_HZ(u16 freq);//fast pwm
void PWM_Freq_KHZ(u16 freq);//fast pwm
void PWM_Duty(u16 duty);//output on timer 1
void PWM_Measure(u32 *pfreq ,u8 *pduty);



#endif 