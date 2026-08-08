#ifndef ICU_H_
#define ICU_H_

#include "UTILS\STD_types.h"

// Capture Edge options
#define ICU_FALLING_EDGE    0
#define ICU_RISING_EDGE     1

void ICU_void_Init(u8 copy_u8_edge);
void ICU_void_SetEdge(u8 copy_u8_edge);
u16  ICU_u16_ReadCapture(void);

#endif