#include "TIMER.h"
#include "UTILS\atmega32_regs.h"
#include "UTILS\common_macros.h"

#ifndef ISR
#define ISR(vector) void vector(void) __attribute__((signal)); \
void vector(void)
#endif

#define TIMER0_OVF_vect   __vector_11
#define TIMER0_COMP_vect  __vector_10
#define TIMER1_COMPA_vect __vector_7
#define TIMER2_COMP_vect  __vector_4

// stores one callback function for each timer
static void (*g_callbacks[3])(void) = { NULL, NULL, NULL };

// converts the timer0 and timer1 prescaler value into the corresponding cs bits
#define TIMER_prescalerToCS_T01(prescaler) ((u8)(prescaler))

// converts the timer2 prescaler value into the corresponding cs bits
static const u8 T2_prescalerLUT[] = { 0, 1, 2, 4, 6, 7, 0, 0 };
#define TIMER_prescalerToCS_T2(prescaler) (T2_prescalerLUT[(prescaler)])

// assigns a callback function to the selected timer
void TIMER_setCallBack(timer_num_t timer_num, void (*callback)(void)) {
    g_callbacks[timer_num] = callback;
}

// starts the selected timer in periodic compare mode
void TIMER_startPeriodic(timer_num_t timer_num, u16 compare_value, timer_prescaler_t prescaler) {
    switch (timer_num) {
        case TIMER_0: {
            TCCR0 = 0;
            SET_BIT(TCCR0, WGM01);

            OCR0 = (u8)compare_value;

            SET_BIT(TIMSK, OCIE0);

            TCCR0 |= (TIMER_prescalerToCS_T01(prescaler) & 0x07);

            break;
        }

        case TIMER_1: {
            TCCR1A = 0;
            TCCR1B = 0;

            SET_BIT(TCCR1B, WGM12);

            OCR1A = compare_value;

            SET_BIT(TIMSK, OCIE1A);

            TCCR1B |= (TIMER_prescalerToCS_T01(prescaler) & 0x07);

            break;
        }

        case TIMER_2: {
            TCCR2 = 0;

            SET_BIT(TCCR2, WGM21);

            OCR2 = (u8)compare_value;

            SET_BIT(TIMSK, OCIE2);

            TCCR2 |= (TIMER_prescalerToCS_T2(prescaler) & 0x07);

            break;
        }

        default:
            break;
    }
}

// stops the selected timer and clears its configuration and callback
void TIMER_deInit(timer_num_t timer_num) {
    switch (timer_num) {
        case TIMER_0: {
            TCCR0 = 0;
            TCNT0 = 0;
            OCR0 = 0;

            CLEAR_BIT(TIMSK, TOIE0);
            CLEAR_BIT(TIMSK, OCIE0);

            g_callbacks[TIMER_0] = NULL;

            break;
        }

        case TIMER_1: {
            TCCR1A = 0;
            TCCR1B = 0;

            TCNT1 = 0;
            OCR1A = 0;

            CLEAR_BIT(TIMSK, TOIE1);
            CLEAR_BIT(TIMSK, OCIE1A);

            g_callbacks[TIMER_1] = NULL;

            break;
        }

        case TIMER_2: {
            TCCR2 = 0;
            TCNT2 = 0;
            OCR2 = 0;

            CLEAR_BIT(TIMSK, TOIE2);
            CLEAR_BIT(TIMSK, OCIE2);

            g_callbacks[TIMER_2] = NULL;

            break;
        }

        default:
            break;
    }
}

// handles the timer0 overflow interrupt and executes its callback
ISR(TIMER0_OVF_vect) {
    if (g_callbacks[TIMER_0] != NULL)
    {
        g_callbacks[TIMER_0]();
    }
}

// handles the timer0 compare match interrupt and executes its callback
ISR(TIMER0_COMP_vect) {
    if (g_callbacks[TIMER_0] != NULL)
    {
        g_callbacks[TIMER_0]();
    }
}

// handles the timer1 compare match interrupt and executes its callback
ISR(TIMER1_COMPA_vect) {
    if (g_callbacks[TIMER_1] != NULL)
    {
        g_callbacks[TIMER_1]();
    }
}

// handles the timer2 compare match interrupt and executes its callback
ISR(TIMER2_COMP_vect) {
    if (g_callbacks[TIMER_2] != NULL)
    {
        g_callbacks[TIMER_2]();
    }
}