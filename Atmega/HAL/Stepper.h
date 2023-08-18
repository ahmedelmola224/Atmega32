

#ifndef STEPPER_H_
#define STEPPER_H_

/************************************ Cfg****************************************/


#define COIL1A PINC0
#define COIL1B PINC1
#define COIL2A PINC2
#define COIL2B PINC3

/********************************************************************************/
#define STEPRESOLUTION  (u8)5
#define DELAY 100
/********************************************************************************/

void Stepper_Init(void);
void Stepper_Bipolar_CW(void);
void Stepper_Bipolar_CCW(void);
void Stepper_Unipolar_CW(void);
void Stepper_Unipolar_CCW(void);
void Stepper_Unipolar_CW_Hs(void);
void Stepper_Uipolar_Angle(u16 angle);
void Stepper_Uipolar_Cycles(u16 cycle);

#endif 