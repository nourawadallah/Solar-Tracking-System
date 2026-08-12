#ifndef TIMER_H
#define TIMER_H

#include "UTILS\STD_types.h"

// selects the timer peripheral instance
typedef enum {
    TIMER_0,
    TIMER_1,
    TIMER_2
} timer_num_t;

// selects the clock prescaler divider factor
typedef enum {
    TIMER_NO_CLOCK,
    TIMER_PRESCALER_1,
    TIMER_PRESCALER_8,
    TIMER_PRESCALER_64,
    TIMER_PRESCALER_256,
    TIMER_PRESCALER_1024,
    TIMER_EXT_CLOCK_FALLING,
    TIMER_EXT_CLOCK_RISING
} timer_prescaler_t;

// starts a timer in ctc mode with interrupt enabled
void TIMER_startPeriodic(timer_num_t timer_num, u16 compare_value, timer_prescaler_t prescaler);

// stops a timer, resets its registers, and clears its callback
void TIMER_deInit(timer_num_t timer_num);

// registers the isr callback for a timer
void TIMER_setCallBack(timer_num_t timer_num, void (*callback)(void));

#endif