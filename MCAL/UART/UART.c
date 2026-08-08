#include "MCAL\UART\UART.h"
#include "UTILS\atmega32_regs.h"
#include "UTILS\common_macros.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef F_CPU
#error "F_CPU must be defined in project settings (toolchain symbols) before building UART.c"
#endif

#ifndef ISR
#define ISR(vector) \
void vector(void) __attribute__((signal)); \
void vector(void)
#endif

#define USART_RXC_vect __vector_13

static void (*g_rxCallback)(u8) = NULL;

// sets baud rate and enables 8N1 tx/rx using double-speed mode
void UART_init(u32 baud_rate) {
	u16 ubrrValue;
	ubrrValue = (u16)((F_CPU / (8UL * baud_rate)) - 1);

	UCSRA = 0;
	SET_BIT(UCSRA, U2X);

	UCSRB = 0;
	SET_BIT(UCSRB, RXEN);
	SET_BIT(UCSRB, TXEN);

	UBRRH = (u8)(ubrrValue >> 8);
	UBRRL = (u8)ubrrValue;

	UCSRC = 0;
	SET_BIT(UCSRC, URSEL);
	SET_BIT(UCSRC, UCSZ0);
	SET_BIT(UCSRC, UCSZ1);
}

// blocks until the data register is free, then sends one byte
void UART_sendByte(u8 data) {
	while (GET_BIT(UCSRA, UDRE) == 0);
	UDR = data;
}

// sends a fixed-size buffer of bytes
void UART_send(const u8 *buffer, u16 size) {
	u16 i;
	for (i = 0; i < size; i++) {
		UART_sendByte(buffer[i]);
	}
}

// sends a null-terminated string
void UART_sendString(const char *str) {
	while (*str != '\0') {
		UART_sendByte(*str);
		str++;
	}
}

// blocks until a byte arrives, then returns it
u8 UART_receive(void) {
	while (GET_BIT(UCSRA, RXC) == 0);
	return UDR;
}

// enables or disables the receive-complete interrupt
void UART_setRxInterrupt(u8 enable) {
	if (enable == TRUE) {
		SET_BIT(UCSRB, RXCIE);
	}
	else {
		CLEAR_BIT(UCSRB, RXCIE);
	}
}

// registers the callback invoked on each received byte
void UART_setCallBack(void (*callback)(u8)) {
	g_rxCallback = callback;
}

// resets all uart registers and clears the callback
void UART_deInit(void) {
	UCSRA = 0;
	UCSRB = 0;
	UCSRC = (1 << URSEL);
	UBRRH = 0;
	UBRRL = 0;
	g_rxCallback = NULL;
}

// receive-complete interrupt: forwards the received byte to the callback
ISR(USART_RXC_vect) {
	u8 receivedByte = UDR;
	if (g_rxCallback != NULL) {
		g_rxCallback(receivedByte);
	}
}