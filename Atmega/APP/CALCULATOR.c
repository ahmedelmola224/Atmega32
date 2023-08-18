#include "StdTypes.h"
#include "KeyPad_interface.h"
#include "KeyPad_cfg.h"
#include "LCD.h"
#include "CALCULATOR.h"

void CALCULATOR_Init()
{
	/*do nothing*/
}

void CALCULATOR_Runnable()
{
	u8 key=KEYPAD_GetKey();
	static u8 op=NO_KEY,op_flag=0,prev_key;
	static u16 num1=0,num2=0,result=0;
	if(key!=NO_KEY)
	{

		 if(key=='+'||key=='-'||key=='/'||key=='*')
		{
			op=key;
			op_flag=1;
			if(prev_key=='=')
			{
				LCD_Clear();
				num1=result;
				LCD_WriteNumber(num1);
			}
			LCD_WriteChar(key);
		}
		else if(key=='='&&prev_key!='=')
		{
			LCD_SetCursor(1,0);
			result=CALCULATOR_CheckOperation(op,num1,num2);
			LCD_WriteNumber(result);
			num1=0;
			num2=0;
			op_flag=0;
			
		}
		else if(key=='C')
		{
			LCD_Clear();
			num1=0;
			num2=0;
			
		}
		else if(key>='0'&&key<='9'&&op_flag==0)
		{
			if(prev_key=='=')
			{
				LCD_Clear();
			}
			num1=(num1*10)+(key-'0');
			LCD_WriteChar(key);
		}
		else if(key>='0'&&key<='9'&&op_flag==1)
		{
			num2=(num2*10)+(key-'0');
			LCD_WriteChar(key);
		}
		prev_key=key;
		
	}
	
}

static u16 CALCULATOR_CheckOperation(u8 op,u16 num1,u16 num2)
{
	u16 result=0;
	switch(op)
	{
		case '+':
		result=num1+num2;
		break;
		case '-':
		result=num1-num2;
		break;
		case '*':
		result=num1*num2;
		break;
		case '/':
		result=num1/num2;
		break;
	}
	return result;
}
