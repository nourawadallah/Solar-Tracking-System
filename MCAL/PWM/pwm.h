#ifndef PWM_H_
#define PWM_H_

#include "UTILS\STD_types.h"

#define OC1A 1
#define OC1B 2

// initializes timer1 for fast pwm with 10-bit resolution
void TIMER1_void_FastPWM_10bit_res(u8 copy_u8_pin, u8 copy_u8_duty);

// initializes timer1 for fast pwm using icr1 as the top value for servo control
void TIMER1_void_FastPWM_ICR_Init(u8 copy_u8_pin);

// sets the pwm compare value for the selected timer1 output channel
void TIMER1_void_FastPWM_ICR_SetCompare(u8 copy_u8_pin, u16 copy_u16_compare);

#endif