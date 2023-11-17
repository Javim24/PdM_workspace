#ifndef API_UART_H
#define API_UART_H

#include "stm32f4xx.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

typedef bool bool_t;

bool_t uartInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);



#endif
