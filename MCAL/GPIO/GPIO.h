#ifndef GPIO_H
#define GPIO_H

#include "UTILS\STD_types.h"

// Available GPIO ports on ATmega32
typedef enum {
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D    
} port_t;

// Pin numbers within a port
typedef enum {
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7
} pin_t;

// Pin data direction
typedef enum {
    INPUT,
    OUTPUT
} direction_t;

// Pin logic level
typedef enum {
    LOW = 0,
    HIGH
} pin_val_t;

// Set the direction of a GPIO pin (input or output)
void GPIO_configurePin(port_t port_num, pin_t pin_num, direction_t direction);

// Write a logic level to an output pin
void GPIO_writePin(port_t port_num, pin_t pin_num, pin_val_t value);

// Toggle the current logic level of an output pin
void GPIO_togglePin(port_t port_num, pin_t pin_num);

// Read the current logic level of a pin
pin_val_t GPIO_readPin(port_t port_num, pin_t pin_num);

#endif