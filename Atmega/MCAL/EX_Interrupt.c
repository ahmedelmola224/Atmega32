#include "StdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "EX_Interrupt.h"

static void (* INT0_Fptr)(void)=NULL_PTR;
static void (* INT1_Fptr)(void)=NULL_PTR;
static void (* INT2_Fptr)(void)=NULL_PTR;

void EXI_Init()
{
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT1,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
}

void EXI_Enable(EXInterruptSource_type interrupt)
{
	switch(interrupt)
	{
		case EX_INT0:
		SET_BIT(GICR,INT0);
		break;
		case EX_INT1:
		SET_BIT(GICR,INT1);
		break;
		case EX_INT2:
		SET_BIT(GICR,INT2);
		break;
	}
}

void EXI_Disable(EXInterruptSource_type interrupt)
{
	switch(interrupt)
	{
		case EX_INT0:
		CLR_BIT(GICR,INT0);
		break;
		case EX_INT1:
		CLR_BIT(GICR,INT1);
		break;
		case EX_INT2:
		CLR_BIT(GICR,INT2);
		break;
	}
	
}

void EXI_TriggerEdge(EXInterruptSource_type interrupt,TRIGGEREdge_type edge)
{
	switch(interrupt)
	{
		case EX_INT0:
		switch(edge)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC01);
			CLR_BIT(MCUCR,ISC00);
			break;
			case ANY_LOGIC_CHANGE:
			CLR_BIT(MCUCR,ISC01);
			SET_BIT(MCUCR,ISC00);
			break;
			case FALLING_EDGE:
			SET_BIT(MCUCR,ISC01);
			CLR_BIT(MCUCR,ISC00);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC01);
			SET_BIT(MCUCR,ISC00);
			break;
		}
		break;
		
		case EX_INT1:
		switch(edge)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC11);
			CLR_BIT(MCUCR,ISC10);
			break;
			case ANY_LOGIC_CHANGE:
			CLR_BIT(MCUCR,ISC11);
			SET_BIT(MCUCR,ISC10);
			break;
			case FALLING_EDGE:
			SET_BIT(MCUCR,ISC11);
			CLR_BIT(MCUCR,ISC10);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC11);
			SET_BIT(MCUCR,ISC10);
			break;
		}
		break;
		case EX_INT2:
		switch(edge)
		{
			case LOW_LEVEL:
			break;
			case ANY_LOGIC_CHANGE:
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCSR,ISC2);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC2);
			break;
		}
		break;
	}
}

void EXI_SetCallBack(EXInterruptSource_type interrupt,void(*funcptr)(void))
{
	switch(interrupt)
	{
		case EX_INT0:
		INT0_Fptr=funcptr;
		break;
		case EX_INT1:
		INT1_Fptr=funcptr;
		break;
		case EX_INT2:
		INT2_Fptr=funcptr;
		break;
	}
}


ISR(INT0_vect)
{
	if(INT0_Fptr!=NULL_PTR)
	{
		INT0_Fptr();
	}
}
ISR(INT1_vect)
{
	if(INT1_Fptr!=NULL_PTR)
	{
		INT1_Fptr();
	}
}
ISR(INT2_vect)
{
	if(INT2_Fptr!=NULL_PTR)
	{
		INT2_Fptr();
	}
}