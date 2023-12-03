#include "API_lcd_port.h"

static I2C_HandleTypeDef I2C_HANDLE;

static bool_t port_i2cInit();

bool_t port_init(){
	return port_i2cInit();
}


static bool_t port_i2cInit(){
	  I2C_HANDLE.Instance = I2C_INSTANCE;
	  I2C_HANDLE.Init.ClockSpeed = I2C_CLOCK_SPEED;
	  I2C_HANDLE.Init.DutyCycle = I2C_DUTYCYCLE_2;
	  I2C_HANDLE.Init.OwnAddress1 = 0;
	  I2C_HANDLE.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	  I2C_HANDLE.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	  I2C_HANDLE.Init.OwnAddress2 = 0;
	  I2C_HANDLE.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	  I2C_HANDLE.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	  bool_t estado = false;

	  if (HAL_I2C_Init(&I2C_HANDLE) == HAL_OK)
	  {
		  estado = true;
	  }

	  return estado;
}

bool_t port_i2cWriteByte(uint8_t _byte){
	if( HAL_I2C_Master_Transmit(&I2C_HANDLE, LCD_ADDRESS<<1, &_byte, 1, I2C_TIMEOUT) == HAL_OK)
		return true;
	else
		return false;
}

void port_delay(uint32_t delay){
	HAL_Delay(delay);
}

