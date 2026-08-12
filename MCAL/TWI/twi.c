#include "twi.h"

// initializes the TWI module as master at 400kHz clock speed
void TWI_voidMasterInit(u8 copy_u8address) {
    TWBR = 12;

    CLEAR_BIT(TWSR, TWPS0);
    CLEAR_BIT(TWSR, TWPS1);

    if (copy_u8address != 0) {
        TWAR = (u8)(copy_u8address << 1);
    }

    TWCR = (1 << TWEA) | (1 << TWEN);
}

// sends a start condition on the I2C bus to initiate a transfer
Err_status TWI_Err_statusSendStartCondition(void) {
    Err_status LOC_Err = NOErr;

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    while (GET_BIT(TWCR, TWINT) == 0);

    if ((TWSR & 0xF8) != START_ACK) {
        LOC_Err = StartConditionErr;
    }

    return LOC_Err;
}

// sends a Repeated start condition to change bus direction
Err_status TWI_Err_statusSendRepeatedStart(void) {

    Err_status LOC_Err = NOErr;

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    while (GET_BIT(TWCR, TWINT) == 0);

    if ((TWSR & 0xF8) != REP_START)
    {
        LOC_Err = RepeatedStartErr;
    }

    return LOC_Err;
}

// transmits the 7-bit slave address along with a Write bit
Err_status TWI_Err_statusMasterSendSlaveAddressWithWrite(u8 copy_u8address) {

    Err_status LOC_Err = NOErr;

    TWDR = (u8)(copy_u8address << 1);

    TWCR = (1 << TWINT) | (1 << TWEN);

    while (GET_BIT(TWCR, TWINT) == 0);

    if ((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK) {
        LOC_Err = MasterSendSlaveAddressWithWriteErr;
    }

    return LOC_Err;
}

// sends a stop condition on the bus to release it
void TWI_voidSendStopCondition(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

// initializes the TWI module as a slave with a specific address
void TWI_voidSlaveInit(u8 copy_u8address) {
    TWAR = (u8)(copy_u8address << 1);
    TWCR = (1 << TWEA) | (1 << TWEN);
}

// blocks until the Slave matches its address with a write request
Err_status TWI_Err_statusSlaveACKOrNotACK(void) {

    Err_status LOC_Err = NOErr;

    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

    while (GET_BIT(TWCR, TWINT) == 0);

    if ((TWSR & 0xF8) != SLAVE_ADD_RCVD_WD_REQ) {
        LOC_Err = SlaveACKOrNotACKErr;
    }

    return LOC_Err;
}

// receives a data byte while operating as a slave device
u8 TWI_u8SlaveReciveData(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    while (GET_BIT(TWCR, TWINT) == 0);

    return TWDR;
}

// transmits a data byte from the master to the active slave
Err_status TWI_Err_statusMasterSendData(u8 copy_u8Data) {

    Err_status LOC_Err = NOErr;

    TWDR = copy_u8Data;

    TWCR = (1 << TWINT) | (1 << TWEN);

    while (GET_BIT(TWCR, TWINT) == 0);

    if ((TWSR & 0xF8) != MASTER_WR_BYTE_ACK) {
        LOC_Err = MasterSendDataErr;
    }

    return LOC_Err;
}

// transmits the 7-bit slave address along with a Read bit
Err_status TWI_Err_statusMasterSendSlaveAddressWithRead(u8 copy_u8address) {
    Err_status LOC_Err = NOErr;

    TWDR = (u8)((copy_u8address << 1) | 1);
    TWCR = (1 << TWINT) | (1 << TWEN);

    while (GET_BIT(TWCR, TWINT) == 0);

    if ((TWSR & 0xF8) != SLAVE_ADD_AND_RR_ACK) {
        LOC_Err = MasterSendSlaveAddressWithReadErr;
    }

    return LOC_Err;
}

// receives a data byte from a slave, sending an ACK (more bytes to follow)
Err_status TWI_Err_statusMasterReciveDataWithACK(u8* copy_pu8Data) {
    Err_status LOC_Err = NOErr;

    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (GET_BIT(TWCR, TWINT) == 0);

    if ((TWSR & 0xF8) != MASTER_RD_BYTE_WITH_ACK) {
        LOC_Err = MasterReciveDataErr;
    }

    *copy_pu8Data = TWDR;
    return LOC_Err;
}

// receives a data byte from a slave, sending a NACK (last byte, stop after this)
Err_status TWI_Err_statusMasterReciveDataWithNACK(u8* copy_pu8Data) {
    Err_status LOC_Err = NOErr;

    TWCR = (1 << TWINT) | (1 << TWEN); // TWEA cleared -> NACK
    while (GET_BIT(TWCR, TWINT) == 0);

    if ((TWSR & 0xF8) != MASTER_RD_BYTE_WITH_NACK) {
        LOC_Err = MasterReciveDataErr;
    }

    *copy_pu8Data = TWDR;
    return LOC_Err;
}