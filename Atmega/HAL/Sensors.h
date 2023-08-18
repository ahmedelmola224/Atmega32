


#ifndef SENSORS_H_
#define SENSORS_H_

#define LM35_CH  CH_0
#define MPX4115_CH CH_1

/*temp C * 10 */


void TempF_Init(void);
extern void TEMPF_Runnable(void);
extern u16 TEMPF_GetRead(void);
extern u16 PRESSURE_Read();
extern u16 TEMP_Read(void);

#endif 