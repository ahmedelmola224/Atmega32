#include "StdTypes.h"
#include "EEPROM_interface.h"
#include "EEPROM_Service.h"

void EEPROM_WriteString(u8*str,u16 address)
{
	u8 i=0;
	while(str[i])
	{
		EEPROM_Write(str[i],address+i);
		i++;
	}
	EEPROM_Write(str[i],address+i);
}


void EEPROM_ReadString(u8*str,u16 address)
{
	u8 i=0;
	EEPROM_Read(str+i,address+i);
	for(;str[i];)
	{
		i++;
		EEPROM_Read(str+i,address+i);	
	}
}