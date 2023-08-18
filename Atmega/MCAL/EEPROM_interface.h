

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_Write(u8 data,u16 address);

u8 EEPROM_Read(u8 *data,u8 address);





#endif /* EEPROM_INTERFACE_H_ */