#ifndef TWI_H_
#define TWI_H_

#include "UTILS\STD_types.h"
#include "UTILS\atmega32_regs.h"
#include "UTILS\common_macros.h"

typedef enum {
    NOErr,
    StartConditionErr,
    RepeatedStartErr,
    MasterSendSlaveAddressWithWriteErr,
    MasterSendSlaveAddressWithReadErr,
    MasterSendDataErr,
    MasterReciveDataErr,
    SlaveACKOrNotACKErr,
} Err_status;

// initializes the TWI module as master at 400kHz clock speed
void TWI_voidMasterInit(u8 copy_u8address);

// sends a start condition on the I2C bus to initiate a transfer
Err_status TWI_Err_statusSendStartCondition(void);

// ends a repeated start condition to change bus direction
Err_status TWI_Err_statusSendRepeatedStart(void);

// transmits the 7-bit slave address along with a write bit
Err_status TWI_Err_statusMasterSendSlaveAddressWithWrite(u8 copy_u8address);

// sends a stop condition on the bus to release it
void TWI_voidSendStopCondition(void);

// initializes the TWI module as a slave with a specific address
void TWI_voidSlaveInit(u8 copy_u8address);

// blocks until the slave matches its address with a write request
Err_status TWI_Err_statusSlaveACKOrNotACK(void);

// receives a data byte while operating as a slave device
u8 TWI_u8SlaveReciveData(void);

// transmits the 7-bit slave address along with a read bit
Err_status TWI_Err_statusMasterSendSlaveAddressWithRead(u8 copy_u8address);

// transmits a data byte from the master to the active slave
Err_status TWI_Err_statusMasterSendData(u8 copy_u8Data);

// receives a data byte from a slave and returns it via a pointer, sending an ACK
// (use for all bytes except the last one in a multi-byte read)
Err_status TWI_Err_statusMasterReciveDataWithACK(u8* copy_pu8Data);

// receives a data byte from a slave and returns it via a pointer, sending a NACK
// (use for the last byte in a multi-byte read, to tell the slave to stop)
Err_status TWI_Err_statusMasterReciveDataWithNACK(u8* copy_pu8Data);

#endif