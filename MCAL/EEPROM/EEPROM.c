#include "UTILS\STD_types.h"
#include "UTILS\common_macros.h"
#include "UTILS\atmega32_regs.h"
#include "EEPROM\EEPROM.h"

#include <util/delay.h>

// writes a byte of data to the specified eeprom address
void EEPROM_writeByte(u16 address, u8 data) {
    while (GET_BIT(EECR, EEWE));

    EEAR = address;

    EEDR = data;

    SET_BIT(EECR, EEMWE);

    SET_BIT(EECR, EEWE);

    _delay_ms(4);
}

// reads a byte of data from the specified eeprom address
u8 EEPROM_readByte(u16 address) {
    while (GET_BIT(EECR, EEWE));

    EEAR = address;

    SET_BIT(EECR, EERE);

    return EEDR;
}