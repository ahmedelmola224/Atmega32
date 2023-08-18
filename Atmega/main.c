#include "DIO_interface.h"
#include "MemoryMap.h"
#include "lcd.h"
#include "Utils.h"
#include "StdTypes.h"
#include "TIMER.h"
#include "SERVO.h"





int main(void)
{
	
	DIO_Init();
	LCD_Init();
	LCD_WriteString("hello");
	UART_Init();
	u32 num=0;
	while(1)
	{
		UART_ReceieveNumber(&num);
		LCD_SetCursor(1,0);
		LCD_WriteNumber(num);
		
		
		
	}
}





