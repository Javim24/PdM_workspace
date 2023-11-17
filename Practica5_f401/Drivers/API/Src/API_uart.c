#include "API_uart.h"
#include "inttypes.h"

static UART_HandleTypeDef UartHandle;

bool_t uartInit(){
	  UartHandle.Instance = USART2;
	  UartHandle.Init.BaudRate = 115200;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits = UART_STOPBITS_1;
	  UartHandle.Init.Parity = UART_PARITY_NONE;
	  UartHandle.Init.Mode = UART_MODE_TX_RX;
	  UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	  bool_t estado = false;
	  if (HAL_UART_Init(&UartHandle) == HAL_OK)
	  {
		  estado = true;
		  //enviar mensaje
		  char mensaje[64] = "Uart inicializada con exito.\r\n";
		  uartSendString((uint8_t*) mensaje);

		  snprintf(mensaje, 64, "Baudrate: %lu\r\n", (unsigned long) UartHandle.Init.BaudRate);
		  uartSendString((uint8_t*) mensaje);

		  snprintf(mensaje, 64, "Largo de palabra: %lu\r\n", (unsigned long) UartHandle.Init.WordLength);
		  uartSendString((uint8_t*) mensaje);

		  snprintf(mensaje, 64, "Bits de stop: %lu\r\n", (unsigned long) UartHandle.Init.StopBits);
		  uartSendString((uint8_t*) mensaje);

		  snprintf(mensaje, 64, "Bit paridad: %lu\r\n", (unsigned long) UartHandle.Init.Parity);
		  uartSendString((uint8_t*) mensaje);

	  }


	  return estado;
}

void uartSendString(uint8_t * pstring){
	if(pstring == NULL){
		return;
	}

	uint16_t strSize = strlen((char *) pstring);
	HAL_UART_Transmit(&UartHandle, pstring, strSize, HAL_MAX_DELAY);
}


void uartSendStringSize(uint8_t * pstring, uint16_t size){
	if(pstring == NULL){
		return;
	}

	uint16_t strSize = strlen((char *) pstring);
	if(strSize < size){
		size = strSize;
	}

	HAL_UART_Transmit(&UartHandle, pstring, size, HAL_MAX_DELAY);
}


void uartReceiveStringSize(uint8_t * pstring, uint16_t size);



