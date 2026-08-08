#include "MCAL\GPIO\GPIO.h"
#include "UTILS\common_macros.h"
#include "UTILS\atmega32_regs.h"

// register lookup tables, indexed by port_t (PORT_A..PORT_D)
static volatile u8 * const ddrRegs[]  = { &DDRA,  &DDRB,  &DDRC,  &DDRD  };
static volatile u8 * const portRegs[] = { &PORTA, &PORTB, &PORTC, &PORTD };
static volatile u8 * const pinRegs[]  = { &PINA,  &PINB,  &PINC,  &PIND  };

// sets the direction of a gpio pin (input or output)
void GPIO_configurePin(port_t port_num, pin_t pin_num, direction_t direction) {
	if (port_num > PORT_D) {
		return;
	}

	if (direction == OUTPUT) {
		SET_BIT(*ddrRegs[port_num], pin_num);
	}
	else {
		CLEAR_BIT(*ddrRegs[port_num], pin_num);
	}
}

// writes a logic level to an output pin (or enables/disables pull-up on an input pin)
void GPIO_writePin(port_t port_num, pin_t pin_num, pin_val_t value) {
	if (port_num > PORT_D) {
		return;
	}

	if (value == HIGH) {
		SET_BIT(*portRegs[port_num], pin_num);
	}
	else {
		CLEAR_BIT(*portRegs[port_num], pin_num);
	}
}

// flips the current logic level of an output pin
void GPIO_togglePin(port_t port_num, pin_t pin_num) {
	if (port_num > PORT_D) {
		return;
	}

	TOGGLE_BIT(*portRegs[port_num], pin_num);
}

// reads the current logic level of a pin
pin_val_t GPIO_readPin(port_t port_num, pin_t pin_num) {
	if (port_num > PORT_D) {
		return LOW;
	}

	return (pin_val_t)GET_BIT(*pinRegs[port_num], pin_num);
}