#ifndef EEPROM_H
#define EEPROM_H

#include "UTILS\STD_types.h"

void EEPROM_writeByte(u16 address, u8 data);
u8 EEPROM_readByte(u16 address);

#endif