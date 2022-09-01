/*
 * as5601.h
 *
 *  Created on: Aug 13, 2022
 *      Author: Sebastian Sokolowski - Smart Solutions for Home
 */

#ifndef INC_AS5601_H_
#define INC_AS5601_H_

#include "main.h"
#include "i2c.h"

#define AS5601_ADDRESS		0x36

/* Configuration Registers */
#define ZMCO				0x00
#define ZPOS_L				0x01
#define ZPOS_H				0x02
#define CONF_L				0x07
#define CONF_H				0x08
#define ABN					0x09
#define PUSHTHR				0x0A

/* Output Registers */
#define RAW_ANGLE_L			0x0C
#define RAW_ANGLE_H			0x0D
#define ANGLE_L				0x0E
#define ANGLE_H				0x0F

/* Status Registers */
#define STATUS				0x0B
#define AGC					0x1A
#define MAGNITUDE_L			0x1B
#define MAGNITUDE_H			0x1C

/* Burn Command */
#define BURN				0xFF
	#define BURN_ANGLE		0x80
	#define BURN_SETTING	0x40

HAL_StatusTypeDef SetResolution(uint8_t res);
HAL_StatusTypeDef BurnSettings(void);

#endif /* INC_AS5601_H_ */
