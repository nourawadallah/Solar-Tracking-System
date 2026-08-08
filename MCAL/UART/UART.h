#ifndef UART_H
#define UART_H

#include "UTILS\STD_types.h"

// initialize uart peripheral
void UART_init(u32 baud_rate);

// send one byte
void UART_sendByte(u8 data);

// send buffer of bytes
void UART_send(const u8 *buffer, u16 size);

// send null-terminated string
void UART_sendString(const char *str);

// receive one byte (blocking)
u8 UART_receive(void);

// enable/disable receive interrupt
void UART_setRxInterrupt(u8 enable);

// register receive callback
void UART_setCallBack(void (*callback)(u8));

// disable uart and clear callback
void UART_deInit(void);

#endif