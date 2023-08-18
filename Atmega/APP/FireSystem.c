#include "StdTypes.h"
#include "DIO_interface.h"
#include "LCD.h"
#include "KeyPad_interface.h"
#include "KeyPad_cfg.h"
#include "EEPROM_Service.h"
#include "SPI.h"
#include "EX_Interrupt.h"
#include "FireSystem.h"
#include "FireSystem_private.h"

static volatile u8 FireFlag=0; 
u8 ActualPassword[20];
u8 TempConfig=0;
u8 SmokeConfig=0;

void FIRESYS_Init(void)
{
	u8 correct_pass=0;
	u8 rec_password[20];
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	SPI_Init();
	EXI_TriggerEdge(EX_INT0,RISING_EDGE);
	EXI_SetCallBack(EX_INT0,EX_Interrupt);
	EXI_Enable(EX_INT0);
	EEPROM_ReadString(ActualPassword,PASSADDRESS);
	LCD_SetCursor(0,4);
	LCD_WriteString("WELCOME");
	_delay_ms(1000);
	while(!correct_pass)
	{
		LCD_Clear();
		LCD_SetCursor(0,0);
		LCD_WriteString("PASSWORD: ");
		FIRESYS_ReceievePassword(rec_password);
		LCD_SetCursor(1,0);
		if(FIRESYS_CheckPassword(rec_password,ActualPassword))
		{
			correct_pass=1;
			LCD_WriteString("CORRECT PASS           ");
			_delay_ms(700);
		}
		else
		{
			LCD_SetCursor(0,0);
			LCD_WriteString("WRONG PASS             ");
			_delay_ms(500);
		}
	}
	LCD_Clear();
}



void FIRESYS_Runnable(void)
{
	u8 rec_password[20];
	static u8 key ='C';
	static u8 sensor_key=NO_KEY;
	while(FireFlag)
	{
		LCD_SetCursor(1,0);
		LCD_WriteString("                             ");
		LCD_SetCursor(0,0);
		LCD_WriteString("PASS TO UNLOCK  ");
		LCD_SetCursor(1,0);
		FIRESYS_ReceievePassword(rec_password);
		if(FIRESYS_CheckPassword(rec_password,ActualPassword))
		{
			FireFlag=0;
			SPI_SendReceieve(UNLOCKMSG);
		}
		else
		{
			LCD_Clear();
			LCD_SetCursor(0,0);
			LCD_WriteString("WRONG PASS");
		}
	}
	if(key==ENTERKEY)
	{
		LCD_SetCursor(0,0);
		LCD_WriteString("1.CHANGE PASS           ");
		LCD_SetCursor(1,0);
		LCD_WriteString("2.CONFIG               ");
		key=KEYPAD_GetKey();
		if(key==NO_KEY||key==ENTERKEY)
		key=ENTERKEY;
		else
		LCD_Clear();
	}
	if(key==CHANGEPASSKEY)
	{
		
		LCD_SetCursor(0,0);
		LCD_WriteString("OLD PASS: ");
		FIRESYS_ReceievePassword(rec_password);
		if(FIRESYS_CheckPassword(rec_password,ActualPassword))
		{
			LCD_SetCursor(0,0);
			LCD_WriteString("                           ");
			LCD_SetCursor(0,0);
			LCD_WriteString("NEW PASS: ");
			FIRESYS_ReceievePassword(rec_password);
			FIRESYS_CopyPassword(rec_password,ActualPassword);
			EEPROM_WriteString(ActualPassword,PASSADDRESS);
			LCD_SetCursor(0,0);
			LCD_WriteString("CHANGED                     ");
			_delay_ms(300);
			key=ENTERKEY;
			LCD_Clear();
		}
		else
		{
			LCD_WriteString("                           ");
			LCD_SetCursor(0,0);
			LCD_WriteString("WRONG PASS     ");
			_delay_ms(500);
		}
	}
	if(key==CONFIGKEY)
	{
		LCD_SetCursor(0,0);
		LCD_WriteString("1.TEMP SENSOR            ");
		LCD_SetCursor(1,0);
		LCD_WriteString("2.SMOKE SENSOR           ");
		sensor_key=KEYPAD_GetKey();
		if(sensor_key=='1')
		{
			key=TEMPSENSKEY;
			LCD_Clear();
		}
		if(sensor_key=='2')
		{
			key=SMOKESENSKEY;
			LCD_Clear();
		}
	}
	if(key==TEMPSENSKEY)
	{
		LCD_SetCursor(0,0);
		LCD_WriteString("MAX TEMP: ");
		FIRESYS_RecieveConfig(&TempConfig);
		SPI_SendReceieve(TEMPSENSKEY);
		_delay_ms(5);
		SPI_SendReceieve(TempConfig);
		LCD_SetCursor(0,0);
		LCD_WriteString("CHANGED                     ");
		_delay_ms(500);
		key=ENTERKEY;
	}
	if(key==SMOKESENSKEY)
	{
		LCD_SetCursor(0,0);
		LCD_WriteString("MAX SMOKE: ");
		FIRESYS_RecieveConfig(&SmokeConfig);
		SPI_SendReceieve(SMOKESENSKEY);
		_delay_ms(5);
		SPI_SendReceieve(SmokeConfig);
		LCD_SetCursor(0,0);
		LCD_WriteString("CHANGED                     ");
		_delay_ms(500);
		key=ENTERKEY;
	}
	
}


void FIRESYS_RecieveConfig(u8*degree)
{
	u8 btn;
	while(1)
	{
		btn=KEYPAD_GetKey();
		if(btn!=NO_KEY)
		{
			if(btn==ENTERKEY)
			{
				break;
			}
			*degree=(*degree)*(u8)10+(btn)-'0';
			LCD_WriteChar(btn);
		}
	}
}

void FIRESYS_ReceievePassword(u8*str)
{
	u8 i=0,btn;
	while(1)
	{
		btn=KEYPAD_GetKey();
		if(btn!=NO_KEY)
		{
			if(btn==ENTERKEY)
			{
				str[i]=0;
				break;;
			}
			str[i]=btn;
			i++;
			LCD_WriteChar('*');
		}
	}
}

u8 FIRESYS_CheckPassword(u8*str1,u8*str2)
{
	for(u8 i=0;str1[i]&&str2[i];i++)
	{
		if(str1[i]!=str2[i])
		{
			return 0;
		}
	}
	return 1;
}

void FIRESYS_CopyPassword(u8*str1,u8*str2)
{
	u8 i=0;
	str2[i]=str1[i];
	while(str2[i])
	{
		i++;
		str2[i]=str1[i];
	}
}

void EX_Interrupt(void)
{
	FireFlag=1;
}