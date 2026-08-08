#include "UTILS\common_macros.h"
#include "UTILS\common_macros.h"
#include "UTILS\atmega32_regs.h"
#include "MCAL\ICU\icu.h"

void ICU_void_Init(u8 copy_u8_edge) {
    // ICP1 (PD6) n3mlo input
    CLEAR_BIT(DDRD, 6);

    // normal mode
    CLEAR_BIT(TCCR1A, WGM10);
    CLEAR_BIT(TCCR1A, WGM11);
    CLEAR_BIT(TCCR1B, WGM12);
    CLEAR_BIT(TCCR1B, WGM13);

    //  clkI/O/8 (from prescaler)
    CLEAR_BIT(TCCR1B, CS10);
    SET_BIT(TCCR1B, CS11);
    CLEAR_BIT(TCCR1B, CS12);
}

void ICU_void_SetEdge(u8 copy_u8_edge) {
    if (copy_u8_edge == ICU_RISING_EDGE) {
        SET_BIT(TCCR1B, ICES1);
    }
    else if (copy_u8_edge == ICU_FALLING_EDGE) {
        CLEAR_BIT(TCCR1B, ICES1);
    }
}

u16 ICU_u16_ReadCapture(void) {
    return ICR1;
}