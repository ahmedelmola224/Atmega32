
#ifndef ULTRASONIC_SERVICE_H_
#define ULTRASONIC_SERVICE_H_
#include "StdTypes.h"
#include "ULTRASONIC.h"

/*config*/
#ifdef ULTRASERVICE
#define ULTRASONIC_NUMBER 4
const ULTRASONIC_type2 UltraSonicArray[ULTRASONIC_NUMBER]={ULTRASONIC1,ULTRASONIC2,ULTRASONIC3,ULTRASONIC4};
#endif

void ULTRASONIC_Group_Init(void);
void UltraSonic_Runnable(void);
void UltraSonic_Group_GetRead(u16* usarray);


#endif 