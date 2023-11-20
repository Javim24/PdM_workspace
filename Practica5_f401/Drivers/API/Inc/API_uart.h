/**
 * Este módulo permite manejar con mayor facilidad
 * la uart que está conectada al stlink en la placa NUCLEOF401RE.
 */

#ifndef API_UART_H
#define API_UART_H

#include "stm32f4xx.h"

//Librerias para usar tipos de datos bool y enteros de tamaño fijo
#include "stdbool.h"
#include "stdint.h"

//Librerias para facilitar el uso de strings
#include "stdio.h"
#include "string.h"

typedef bool bool_t;		//Tipo de dato booleano


/**
 * Función necesaria para configurar la
 * comunicación por uart. Si no se llama,
 * no se pueden utilizar las demás funciones.
 * Devuelve un valor booleano que indica si se
 * inició correctamente la uart. Además imprime un
 * mensaje de inicio por la uart, en caso de que se
 * haya iniciado correctamente.
 */
bool_t uartInit();

/**
 * Envía una cadena de caracteres por la uart.
 * Esta cadena debe estar terminada con el
 * caracter nulo (\0). Recibe un puntero al
 * comienzo de la cadena.
 */
void uartSendString(uint8_t * pstring);

/**
 * Envía una cadena de caracteres por la uart
 * pero permite limitar la cantidad de caracteres
 * que se envían. Recibe un puntero al comienzo de la cadena
 * y un entero que indica el tamaño.
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size);

/**
 * Recibe por la uart una cantidad de caracteres definida.
 * Como parametros recibe un puntero a la dirección en la que se
 * guardan los caracteres, y un entero que indica la cantidad a recibir.
 */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);



#endif
