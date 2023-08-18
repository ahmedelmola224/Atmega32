
#ifndef EX_INTERRUPT_H_
#define EX_INTERRUPT_H_

typedef enum
{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}TRIGGEREdge_type;

typedef enum
{
	EX_INT0=0,
	EX_INT1,
	EX_INT2
}EXInterruptSource_type;

void EXI_Init();
void EXI_Enable(EXInterruptSource_type interrupt);
void EXI_Disable(EXInterruptSource_type interrupt);
void EXI_TriggerEdge(EXInterruptSource_type interrupt,TRIGGEREdge_type edge);
void EXI_SetCallBack(EXInterruptSource_type interrupt,void(*funcptr)(void));




#endif 