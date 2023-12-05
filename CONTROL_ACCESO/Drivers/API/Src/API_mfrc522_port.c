/*
 * API_mfrc522_port.c
 *
 *  Created on: Nov 27, 2023
 *      Author: javi
 */

#include "API_mfrc522_port.h"

static SPI_HandleTypeDef SPI;

static bool_t SPI_Init();
static void GPIO_Init();

bool_t portInit() {
	bool_t estado = SPI_Init();
	GPIO_Init();
	return estado;
}

static bool_t SPI_Init() {
	SPI.Instance = SPI_INSTANCE;
	SPI.Init.Mode = SPI_MODE_MASTER;
	SPI.Init.Direction = SPI_DIRECTION_2LINES;
	SPI.Init.DataSize = SPI_DATASIZE_8BIT;
	SPI.Init.CLKPolarity = SPI_POLARITY_LOW;
	SPI.Init.CLKPhase = SPI_PHASE_1EDGE;
	SPI.Init.NSS = SPI_NSS_SOFT;
	SPI.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SPI.Init.TIMode = SPI_TIMODE_DISABLE;
	SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI.Init.CRCPolynomial = 10;

	bool_t estado = true;

	if (HAL_SPI_Init(&SPI) != HAL_OK) {
		estado = false;
	}

	return estado;
}

static void GPIO_Init() {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
//   __HAL_RCC_GPIOC_CLK_ENABLE();
//   __HAL_RCC_GPIOH_CLK_ENABLE();
//   __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : CS_Pin */
	GPIO_InitStruct.Pin = CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CS_GPIO_Port, &GPIO_InitStruct);
}

void spiWrite(uint8_t reg_addr, uint8_t *txData, uint16_t size) {
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&SPI, &reg_addr, 1, SPI_TIMEOUT);
	HAL_SPI_Transmit(&SPI, txData, size, SPI_TIMEOUT);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

void spiRead(uint8_t reg_addr, uint8_t *rxData, uint16_t size) {
	uint8_t dummyTx[size];
	for (uint16_t i = 0; i < size; i++) {
		dummyTx[i] = 0;
	}
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&SPI, &reg_addr, 1, SPI_TIMEOUT);
	HAL_SPI_TransmitReceive(&SPI, dummyTx, rxData, size, SPI_TIMEOUT);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}
