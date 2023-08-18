#include "StdTypes.h"
#include "KeyPad_interface.h"
#include "KeyPad_cfg.h"
#include "LCD.h"
#include "CONVERTER.h"
#include "CONVERTER_private.h"

CONVERTER_MODE from ,to;
u8 mode=0,num=0;

void CONVERTER_Init(void)
{
	/*do nothing*/
}

void CONVERTER_Mode0(void)
{
	static u8 mode0=0;
	u8 key;
	if(mode0==0)
	{
		LCD_SetCursor(0,0);
		LCD_WriteString("From:");
		LCD_SetCursor(1,0);
		LCD_WriteString("1.Dec ");
		LCD_WriteString("2.Bin");
		LCD_WriteString("3.Hex");
		key=KEYPAD_GetKey();
		if((key>='1')&&(key<='3'))
		{
			from=key-'0';
			mode0++;
			LCD_Clear();
		}
	}
	else if(mode0==1)
	{
		key=KEYPAD_GetKey();
		LCD_SetCursor(0,0);
		LCD_WriteString("To:    ");
		LCD_SetCursor(1,0);
		if(from==DEC)
		{
			
			LCD_WriteString("1.BIN     ");
			LCD_WriteString("2.Hex  ");
			if(key>='1'&&key<='2')
			{
				to=key-'0'+1;
				mode0--;
				mode++;
				LCD_Clear();
			}
		}
			
			else if(from==BIN)
			{
				LCD_WriteString("1.DEC     ");
				LCD_WriteString("2.Hex   ");
				if(key>='1'&&key<='2')
				{
					to=key-'0'+1;
					mode0--;
					mode++;
					LCD_Clear();
					if(key=='1')
					to--;
				}
					
			}
		else if(from==HEX)
		{
			LCD_WriteString("1.DEC     ");
			LCD_WriteString("2.BIN  ");
			if(key>='1'&&key<='2')
			{
				to=key-'0';
				mode0--;
				mode++;
				LCD_Clear();
			}
			
		}		
		
		
	}
	
}

void CONVERTER_Runnable(void)
{
	u8 key;
	static u8 counter=0;
	if(mode==0)
	{
		CONVERTER_Mode0();
	}
	else if(mode==1)
	{
		
		key=KEYPAD_GetKey();
		if(key=='=')
		{
			num=0;
			LCD_Clear();
			counter=0;
		}
		if(key=='O')
		{
			LCD_Clear();
			mode=0;
			num=0;
			counter=0;
		}
		if(from==DEC)
		{
			LCD_SetCursor(0,0);
			LCD_WriteString("DEC:");
			if(key>='0'&&key<='9')
			{
				READ_Decimal(key);
				LCD_SetCursor(0,4+counter);
				LCD_WriteChar(key);
				counter++;
			}
		}
		else if(from==BIN)
		{

			LCD_SetCursor(0,0);
			LCD_WriteString("BIN:");
			if(key>='0'&&key<='1')
			{
				
				READ_Binary(key);
				LCD_SetCursor(0,4+counter);
				LCD_WriteChar(key);
				counter++;
			}
		}
		else if(from==HEX)
		{
			LCD_SetCursor(0,0);
			LCD_WriteString("HEX:");
			if((key>='0'&&key<='9')||(key>='A'&&key<='F'))
			{
				READ_HEX(key);
				LCD_SetCursor(0,4+counter);
				LCD_WriteChar(key);
				counter++;
			}
		}
		CONVERTER_Transform();
		
		
	}
	
	
}

void CONVERTER_Transform(void)
{
	switch(to)
	{
		case DEC:
		LCD_SetCursor(1,0);
		LCD_WriteString("DEC:");
		LCD_WriteNumber(num);
		break;
		case BIN:
		LCD_SetCursor(1,0);
		LCD_WriteString("BIN:");
		LCD_WriteBinary(num);
		break;
		case HEX:
		LCD_SetCursor(1,0);
		LCD_WriteString("HEX:");
		LCD_WriteHex(num);
		break;
		
	}
}

void READ_Decimal(u8 key)
{
	num=(num*10)+(key-'0');
}

void READ_Binary(u8 key)
{
	num=(num*2)+(key-'0');
}
void READ_HEX(u8 key)
{
	if(key>='0'&&key<='9')
	{
		num=(num*16)+(key-'0');
	}
	else if(key>='A'&&key<='F')
	{
		num=num*16+(key-'A'+10);
	}
	
}