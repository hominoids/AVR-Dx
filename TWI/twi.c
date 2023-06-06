/*
 * Copyright (c) 2023 Edward Kisiel hominoid@cablemi.com All rights reserved.
 *
 * File:    twi.c
 * Author:  Edward Kisiel
 * License: GNU GPLv3
 *
 * Description: AVRDx TWI driver to control the processor's I2C interface.
 *
*/
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "twi.h"


/* 
 *  twi/i2c initialization for all ports and modes.
 *   
 *  uint8_t twi_init(uint8_t TWI_MODE, uint8_t TWIPORT, uint8_t BAUD)
 *                   TWI_MODE = TWI_MODE_HOST, TWI_MODE_CLIENT
 *                    TWIPORT = TWI0, TWI1
 *                       BAUD = bus baud rate
 */
uint8_t twi_init(uint8_t TWI_MODE, uint8_t TWIPORT, uint8_t BAUD) {

    if(TWI_MODE == TWI_MODE_HOST) {
        switch(TWIPORT) {
            case TWI0_I2C :
                // if used set SDAHOLD, FMPEN bits in TWI0_MCTRLA here

                // set baud rate
                TWI0_MBAUD = BAUD;

                // set ENABLE bit
                TWI0_MCTRLA &= 0b00000001;

                // set BUSSTATE to force idle
                TWI0_MSTATUS = 0x1;
                
                // check for idle state
                if(TWI0_MSTATUS > 0) {
                    return(0);
                }
                else {
                    return(1);
                }
            case TWI1_I2C :
                // if used set SDAHOLD, FMPEN bits in TWI1_MCTRLA here

                // set baud rate
                TWI1_MBAUD = BAUD;

                // set ENABLE bit
                TWI1_MCTRLA &= 0b00000001;

                // set BUSSTATE to force idle
                TWI1_MSTATUS = 0x1;
                
                // check for idle state
                if(TWI1_MSTATUS > 0) {
                    return(0);
                }
                else {
                    return(1);
                }
            default :
                return(1);
        }
    }
    if(TWI_MODE == TWI_MODE_CLIENT) {
        switch(TWIPORT) {
            case TWI0_I2C :
                // configure SDASETUP
                TWI0_SCTRLA &= 0b00001000;

                // set address
                TWI0_SADDR = TWI0_ADDR;

                // set ENABLE bit
                TWI0_SCTRLA &= 0b00000001;
                
                // set BUSSTATE to force idle
                TWI0_SSTATUS = 0x1;
                
                // check for idle state
                if(TWI0_SSTATUS > 0) {
                    return(0);
                }
                else {
                    return(1);
                }
            case TWI1_I2C :
                 // configure SDASETUP
                TWI1_CTRLA &= 0b00001000;

                // set address
                TWI1_SADDR = TWI1_ADDR;

                // set ENABLE bit
                TWI1_SCTRLA &= 0b00000001;
                                
                // set BUSSTATE to force idle
                TWI1_SSTATUS = 0x1;
                
                // check for idle state
                if(TWI1_SSTATUS > 0) {
                    return(0);
                }
                else {
                    return(1);
                }
            default :
                return(1);
        }
    }
}


/* error handler */
void error(uint8_t num)
{
    PORTC_DIRSET = 0x40;
    for (int i = 0; i <= num; i++) {
        PORTC_OUTSET = 0x40;
        _delay_ms(25);
        PORTC_OUTCLR = 0x40;
        _delay_ms(25);
    }
        _delay_ms(500);
}
