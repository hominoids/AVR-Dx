/*
 * Copyright (c) 2023 Edward Kisiel hominoid@cablemi.com All rights reserved.
 *
 * File:    twi.h
 * Author:  Edward Kisiel
 * License: GNU GPLv3
 *
 * Description: AVRDx TWI driver to control the processor's I2C interface.
 *
*/
 
/* TWI0 setttings */
#define TWI0_I2C            0
#define TWI0_ADDR           0x00
#define TWI0_BAUD           128

/* TWI1 setttings */
#define TWI1_I2C            1
#define TWI1_ADDR           0x69
#define TWI1_BAUD           128

#define TWI_MODE_HOST       0
#define TWI_MODE_CLIENT     1
#define TWI_READ_ACK        1
#define TWI_READ_NACK       0

/* error messages */
#define TWI_ERROR_NOHOST    10

uint8_t twi_init(uint8_t TWI_MODE, uint8_t TWIPORT, uint8_t BAUD);

void error(uint8_t num);