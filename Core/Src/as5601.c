/*
 * as5601.c
 *
 *  Created on: Aug 13, 2022
 *      Author: Sebastian Sokolowski - Smart Solutions for Home
 */

#include "as5601.h"

HAL_StatusTypeDef WriteOneByte(uint8_t reg, uint8_t data)
{
	uint8_t buff[2] = {reg, data};

	return HAL_I2C_Master_Transmit(&hi2c1, AS5601_ADDRESS<<1, buff, 2, 1000);
}

/*
 * @brief  Setting the encoder resolution:
 * 		   0x00 : 8 (61Hz)
 * 		   0x01 : 16 (122Hz)
 * 		   0x02 : 32 (244Hz)
 * 		   0x03 : 64 (488Hz)
 * 		   0x04 : 128 (976Hz)
 * 		   0x05 : 256 (1.9kHz)
 * 		   0x06 : 512 (3.9kHz)
 * 		   0x07 : 1024 (7.8kHz)
 * 		   0x08-0x15 : 2048 (15kHz)
 *
 * @param  res  Resolution
 *
 * @retval HAL status
 */

HAL_StatusTypeDef SetResolution(uint8_t res)
{
	return WriteOneByte(ABN, res);
}

HAL_StatusTypeDef BurnSettings(void)
{
	return WriteOneByte(BURN, BURN_SETTING);
}
