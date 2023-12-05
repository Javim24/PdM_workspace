/*
 * API_mfrc522_port.h
 *
 *  Created on: Nov 26, 2023
 *      Author: javi
 */

#ifndef API_INC_API_MFRC522_PORT_H_
#define API_INC_API_MFRC522_PORT_H_

#include "stm32f4xx.h"
#include "API_types.h"

#define SPI_INSTANCE        SPI1
#define CS_Pin              GPIO_PIN_6
#define CS_GPIO_Port        GPIOB
#define SPI_TIMEOUT		10

bool_t portInit();
void spiWrite(uint8_t reg_addr, uint8_t *txData, uint16_t size);
void spiRead(uint8_t reg_addr, uint8_t *rxData, uint16_t size);

#endif /* API_INC_API_MFRC522_PORT_H_ */
