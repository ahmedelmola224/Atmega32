#include "StdTypes.h"
#include "DIO_interface.h"
#include "MOTOR_interface.h"
#include "MOVE.h"
#include "MOVE_private.h"

void MOVE_Init()
{
	/*do nothing*/
}

void MOVE_Runnable()
{
	while(DIO_ReadPin(FORWADR_B)==LOW)
	{
		MOVE_Forward();
	}
	while(DIO_ReadPin(BACKWARD_B)==LOW)
	{
		MOVE_Backward();
	}
	while(DIO_ReadPin(LEFT_B)==LOW)
	{
		MOVE_Left();
	}
	while(DIO_ReadPin(RIGHT_B)==LOW)
	{
		MOVE_Right();
	}
	MOVE_Stop();
}


static void MOVE_Forward(void)
{
	MOTOR_Cw(FRONT_LEFT_M);
	MOTOR_Cw(FRONT_Right_M);
	MOTOR_Cw(BACK_LEFT_M);
	MOTOR_Cw(BACK_Right_M);
}

static void MOVE_Backward(void)
{
	MOTOR_Ccw(FRONT_LEFT_M);
	MOTOR_Ccw(FRONT_Right_M);
	MOTOR_Ccw(BACK_LEFT_M);
	MOTOR_Ccw(BACK_Right_M);
}

static void MOVE_Left(void)
{
	MOTOR_Ccw(FRONT_LEFT_M);
	MOTOR_Cw(FRONT_Right_M);
	MOTOR_Ccw(BACK_LEFT_M);
	MOTOR_Cw(BACK_Right_M);
}

static void MOVE_Right(void)
{
	MOTOR_Cw(FRONT_LEFT_M);
	MOTOR_Ccw(FRONT_Right_M);
	MOTOR_Cw(BACK_LEFT_M);
	MOTOR_Ccw(BACK_Right_M);
}

static void MOVE_Stop(void)
{
	MOTOR_Stop(FRONT_LEFT_M);
	MOTOR_Stop(FRONT_Right_M);
	MOTOR_Stop(BACK_LEFT_M);
	MOTOR_Stop(BACK_Right_M);
}


