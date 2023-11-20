#include "API_uart.h"

static UART_HandleTypeDef UartHandle;	//estructura para acceder a la uart
static bool_t uartEnabled = false;		//variable para verificar si se inició correctamente la uart

static USART_TypeDef * UART_INSTANCE = USART2;
static const uint32_t BAUD_RATE = 115200;
static const uint32_t WORD_LENGTH = UART_WORDLENGTH_8B;
static const uint32_t STOP_BITS = UART_STOPBITS_1;
static const uint32_t PARITY = UART_PARITY_NONE;
static const uint32_t MODE_TX_RX = UART_MODE_TX_RX;
static const uint32_t HW_CONTROL = UART_HWCONTROL_NONE;
static const uint32_t OVERSAMPLING = UART_OVERSAMPLING_16;

static uint8_t mensajeInicio[] = "UART2 INICIADA CON ÉXITO EN 115200 8N1\r\n";

bool_t uartInit(){
	  UartHandle.Instance = UART_INSTANCE;
	  UartHandle.Init.BaudRate = BAUD_RATE;
	  UartHandle.Init.WordLength = WORD_LENGTH;
	  UartHandle.Init.StopBits = STOP_BITS;
	  UartHandle.Init.Parity = PARITY;
	  UartHandle.Init.Mode = MODE_TX_RX;
	  UartHandle.Init.HwFlowCtl = HW_CONTROL;
	  UartHandle.Init.OverSampling = OVERSAMPLING;

	  if (HAL_UART_Init(&UartHandle) == HAL_OK)
	  {
		  uartEnabled = true;

		  //enviar mensaje de inicio correcto
		  uartSendString(mensajeInicio);
	  }
	  return uartEnabled;
}

void uartSendString(uint8_t * pstring){
	if(! uartEnabled)
		return;

	if(pstring == NULL)
		return;



	uint16_t strSize = strlen((char *) pstring);
	HAL_UART_Transmit(&UartHandle, pstring, strSize, HAL_MAX_DELAY);
}


void uartSendStringSize(uint8_t * pstring, uint16_t size){
	if(! uartEnabled)
		return;

	if(pstring == NULL)
		return;

	uint16_t strSize = strlen((char *) pstring);
	if(strSize < size){
		size = strSize;
	}

	HAL_UART_Transmit(&UartHandle, pstring, size, HAL_MAX_DELAY);
}


void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
