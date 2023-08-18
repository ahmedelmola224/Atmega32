#include "StdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "EEPROM_interface.h"

void EEPROM_Write(u8 data,u16 address)
{
	if(address<1024)
	{
		while(READ_BIT(EECR,EEWE));
		EEAR=address;
		EEDR=data;
		SET_BIT(EECR,EEMWE);
		SET_BIT(EECR,EEWE);
	}
}


u8 EEPROM_Read(u8 *data,u8 address)
{
	if((address)<1024)
	{
		while(READ_BIT(EECR,EEWE));
		EEAR=address;
		SET_BIT(EECR,EERE);
		*data=EEDR;
		return 1;
	}
	return 0;	
}
