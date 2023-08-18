


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "StdTypes.h"
#include "DIO_interface.h"
#include "Timers.h"
#define  F_CPU  8000000UL
#include <util/delay.h>

#define TIMER_TOP (u16)20000

#define US1 PIND7
#define US2 PIND2
#define US3 PIND3
#define US4 PIND5

typedef DIO_Pin_type ULTRASONIC_type;

//another way for config
typedef enum
{
	ULTRASONIC1=PIND7,
	ULTRASONIC2=PIND2,
	ULTRASONIC3=PIND3,
	ULTRASONIC4=PIND5
	}ULTRASONIC_type2;

void ULTRASONIC_Init(void);
u8 ULTRASONIC_GetDistance(ULTRASONIC_type2 us ,u16*pdistance);
void ULTRASONIC_Start(ULTRASONIC_type2 us);
u8 ULTRASONIC_GetDistance_Periodic(u16*pdistance);






#endif 