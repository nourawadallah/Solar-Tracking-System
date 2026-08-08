#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

// set the bit to 1
#define SET_BIT(REG, BIT_NO) (REG |= (1 << BIT_NO))

// clear the bit to 0
#define CLEAR_BIT(REG,BIT_NO) (REG &= ~(1<<BIT_NO))

// toggle the bit
#define TOGGLE_BIT(REG,BIT_NO) (REG ^= (1<<BIT_NO))

// get the bit value
#define GET_BIT(REG,BIT_NO) ((REG >> BIT_NO) & 1)

#endif