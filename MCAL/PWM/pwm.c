#include "UTILS\STD_types.h"
#include "UTILS\COMMON_MACROS.h"
#include "UTILS\ATMEGA32_REGS.h"
#include "PWM.h"

void TIMER1_void_FastPWM_10bit_res(u8 copy_u8_pin, u8 copy_u8_duty) {
    u16 local_u16_OCR_value = 0;

    SET_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1B, WGM12);
    CLEAR_BIT(TCCR1B, WGM13);

    CLEAR_BIT(TCCR1B, 0); // CS10 = 0
    SET_BIT(TCCR1B, 1);   // CS11 = 1
    CLEAR_BIT(TCCR1B, 2); // CS12 = 0

    switch (copy_u8_pin) {
        case OC1A:
            SET_BIT(TCCR1A, 7);   // COM1A1 = 1 (Non-Inverting)
            CLEAR_BIT(TCCR1A, 6); // COM1A0 = 0
            OCR1A = (f32)copy_u8_duty * 10.23;
            break;

        case OC1B:
            SET_BIT(TCCR1A, 5);   // COM1B1 = 1 (Non-Inverting)
            CLEAR_BIT(TCCR1A, 4); // COM1B0 = 0
            OCR1B = (f32)copy_u8_duty * 10.23;
            break;
    }
}