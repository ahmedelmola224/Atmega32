


#ifndef MOVE_H_
#define MOVE_H_

#define FRONT_LEFT_M     M1
#define FRONT_Right_M    M2
#define BACK_LEFT_M      M3
#define BACK_Right_M     M4



#define  FORWADR_B       PIND0
#define  BACKWARD_B      PIND1
#define  LEFT_B          PIND2
#define  RIGHT_B         PIND3


extern void MOVE_Init();
extern void MOVE_Runnable();


#endif 