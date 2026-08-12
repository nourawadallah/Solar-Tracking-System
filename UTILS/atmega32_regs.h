#ifndef ATMEGA32_REGS_H
#define ATMEGA32_REGS_H

#include "UTILS\STD_types.h"

// CPU STATUS REGISTER
#define SREG    (*((volatile u8*)0x5F)) // Status Register
#define SREG_I  7 // Global Interrupt Enable bit

// GPIO REGISTERS
#define PORTA   (*((volatile u8*)0x3B))
#define DDRA    (*((volatile u8*)0x3A))
#define PINA    (*((volatile u8*)0x39))

#define PORTB   (*((volatile u8*)0x38))
#define DDRB    (*((volatile u8*)0x37))
#define PINB    (*((volatile u8*)0x36))

#define PORTC   (*((volatile u8*)0x35))
#define DDRC    (*((volatile u8*)0x34))
#define PINC    (*((volatile u8*)0x33))

#define PORTD   (*((volatile u8*)0x32))
#define DDRD    (*((volatile u8*)0x31))
#define PIND    (*((volatile u8*)0x30))

// ADC REGISTERS
#define ADMUX       (*((volatile u8*)0x27))
#define ADCSRA      (*((volatile u8*)0x26))
#define ADCH        (*((volatile u8*)0x25))
#define ADCL        (*((volatile u8*)0x24))
#define ADC_DATA    (*((volatile u16*)0x24))

// ADMUX bit positions
#define MUX0    0
#define MUX1    1
#define MUX2    2
#define MUX3    3
#define MUX4    4
#define ADLAR   5
#define REFS0   6
#define REFS1   7

// ADCSRA bit positions
#define ADPS0   0
#define ADPS1   1
#define ADPS2   2
#define ADIE    3
#define ADIF    4
#define ADATE   5
#define ADSC    6
#define ADEN    7

// TIMERS GLOBAL INTERRUPT REGISTERS
#define TIMSK   (*((volatile u8*)0x59)) // Timer Interrupt Mask Register
#define TIFR    (*((volatile u8*)0x58))

// TIMER0 REGISTERS
#define TCCR0   (*((volatile u8*)0x53)) // Timer0 Control Register
#define TCNT0   (*((volatile u8*)0x52)) // Timer0 Counter Register
#define OCR0    (*((volatile u8*)0x5C)) // Timer0 Output Compare Register

// TCCR0 bit positions
#define CS00    0
#define CS01    1
#define CS02    2
#define WGM01   3
#define COM00   4
#define COM01   5
#define WGM00   6
#define FOC0    7

// TIMER1 REGISTERS
#define TCCR1A  (*((volatile u8*)0x4F)) // Timer1 Control Register A
#define TCCR1B  (*((volatile u8*)0x4E)) // Timer1 Control Register B
#define TCNT1   (*((volatile u16*)0x4C)) // Timer1 Counter Register
#define ICR1    (*((volatile u16*)0x46)) // Timer1 Input Capture Register (used as TOP in mode 14)
#define OCR1A   (*((volatile u16*)0x4A)) // Timer1 Output Compare Register A
#define OCR1B   (*((volatile u16*)0x48)) // Timer1 Output Compare Register B

// TCCR1A bit positions
#define WGM10   0
#define WGM11   1
#define FOC1B   2
#define FOC1A   3
#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7

// TCCR1B bit positions
#define CS10    0
#define CS11    1
#define CS12    2
#define WGM13   4
#define WGM12   3 // CTC Mode selection bit A

// TIMER2 REGISTERS
#define TCCR2   (*((volatile u8*)0x45)) // Timer2 Control Register
#define TCNT2   (*((volatile u8*)0x44)) // Timer2 Counter Register
#define OCR2    (*((volatile u8*)0x43)) // Timer2 Output Compare Register

// TCCR2 bit positions
#define WGM21   3 // CTC Mode selection bit

// TIMSK common bit positions
#define TOIE0   0 // Timer0 Overflow Interrupt Enable
#define OCIE0   1 // Timer0 Compare Match Interrupt Enable
#define TOIE1   2 // Timer1 Overflow Interrupt Enable
#define OCIE1A  4 // Timer1 Compare Match A Interrupt Enable
#define TOIE2   6 // Timer2 Overflow Interrupt Enable
#define OCIE2   7 // Timer2 Compare Match Interrupt Enable

// SPI REGISTERS
#define SPCR    (*((volatile u8*)0x2D))
#define SPSR    (*((volatile u8*)0x2E))
#define SPDR    (*((volatile u8*)0x2F))

// SPCR bit positions
#define SPR0    0
#define SPR1    1
#define CPHA    2
#define CPOL    3
#define MSTR    4
#define DORD    5
#define SPE     6
#define SPIE    7

// SPSR bit positions
#define SPI2X   0
#define WCOL    6
#define SPIF    7

// UART REGISTERS
#define UDR     (*((volatile u8*)0x2C))
#define UCSRA   (*((volatile u8*)0x2B))
#define UCSRB   (*((volatile u8*)0x2A))
#define UCSRC   (*((volatile u8*)0x40))
#define UBRRH   (*((volatile u8*)0x40))
#define UBRRL   (*((volatile u8*)0x29))

// UCSRA bit positions
#define MPCM    0
#define U2X     1
#define PE      2
#define DOR     3
#define FE      4
#define UDRE    5
#define TXC     6
#define RXC     7

// UCSRB bit positions
#define TXB8    0
#define RXB8    1
#define UCSZ2   2
#define TXEN    3
#define RXEN    4
#define UDRIE   5
#define TXCIE   6
#define RXCIE   7

// UCSRC bit positions
#define UCPOL   0
#define UCSZ0   1
#define UCSZ1   2
#define USBS    3
#define UPM0    4
#define UPM1    5
#define UMSEL   6
#define URSEL   7

// EXTERNAL INTERRUPT CONTROL REGISTERS
#define MCUCR   (*((volatile u8*)0x55))
#define MCUCSR  (*((volatile u8*)0x54))
#define GICR    (*((volatile u8*)0x5B))
#define GIFR    (*((volatile u8*)0x5A))

// MCUCR sense-control bits for INT0 (ISC01:ISC00)
#define ISC00   0
#define ISC01   1

// MCUCR sense-control bits for INT1 (ISC11:ISC10)
#define ISC10   2
#define ISC11   3

// MCUCSR sense-control bit for INT2 (edge only: 0=falling, 1=rising)
#define ISC2    6

// GICR enable bits
#define GICR_INT2   5
#define GICR_INT0   6
#define GICR_INT1   7

// GIFR flag bits (write 1 to clear)
#define INTF2   5
#define INTF0   6
#define INTF1   7

// twi status codes
#define START_ACK                0x08  
#define REP_START                0x10  
#define SLAVE_ADD_AND_WR_ACK     0x18  
#define SLAVE_ADD_AND_RR_ACK     0x40  
#define MASTER_WR_BYTE_ACK       0x28  
#define MASTER_RD_BYTE_WITH_ACK  0x50  
#define MASTER_RD_BYTE_WITH_NACK 0x58 
#define SLAVE_ADD_RCVD_WD_REQ    0x60

// twi registers
#define TWBR    (*((volatile u8*)0x20))
#define TWSR    (*((volatile u8*)0x21))
#define TWAR    (*((volatile u8*)0x22))
#define TWDR    (*((volatile u8*)0x23))
#define TWCR    (*((volatile u8*)0x56))

// TWCR bit positions
#define TWIE    0
#define TWEN    2
#define TWWC    3
#define TWSTO   4
#define TWSTA   5
#define TWEA    6
#define TWINT   7

// TWSR bit positions
#define TWPS0   0
#define TWPS1   1

// EEPROM REGISTERS
#define EEARL   (*((volatile u8*)0x3E))
#define EEARH   (*((volatile u8*)0x3F))
#define EEAR    (*((volatile u16*)0x3E))
#define EEDR    (*((volatile u8*)0x3D))
#define EECR    (*((volatile u8*)0x3C))

// EECR bit positions
#define EERE    0 // EEPROM Read Enable
#define EEWE    1 // EEPROM Write Enable
#define EEMWE   2 // EEPROM Master Write Enable
#define EERIE   3 // EEPROM Ready Interrupt Enable

#endif