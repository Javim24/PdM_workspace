/*
 * API_lcd_port.h
 *
 *  Created on: Nov 28, 2023
 *      Author: javi
 */

#ifndef API_INC_API_LCD_PORT_H_
#define API_INC_API_LCD_PORT_H_

#include "stm32f4xx.h"
#include "API_types.h"

#define I2C_INSTANCE				I2C1
#define I2C_CLOCK_SPEED				100000
#define I2C_TIMEOUT					10
#define LCD_ADDRESS					0x27

bool_t port_init();
bool_t port_i2cWriteByte(uint8_t);
void port_delay(uint32_t);


#endif /* API_INC_API_LCD_PORT_H_ */
