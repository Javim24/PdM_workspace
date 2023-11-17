/*
 * API_debounce.h
 *
 * Este módulo realiza la lectura de un botón
 * eliminando el efecto de rebote que se produce
 * al presionarlo. Para esto utiliza una
 * máquina de estados que se encarga de detectar
 * los cambios en el estado del botón.
 *
 *  Created on: Nov 11, 2023
 *      Author: javi
 */


#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "stm32f4xx_hal.h"
#include "API_delay.h"
#include "API_uart.h"


/**
 * Esta función inicializa la máquina de estados
 * que se encarga de leer el estado del botón.
 * Para inicializarla se le debe envíar como argumentos
 * un puntero al GPIO_TypeDef del puerto y el pin del botón
 * que se desea leer.
 */
void debounceFSM_init(GPIO_TypeDef * buttonPort, uint16_t buttonPin);

/**
 * Esta función se debe llamar periodicamente
 * para que la máquina de estados actualize el
 * estado del botón.
 */
void debounceFSM_update();

/**
 * La función readKey devuelve true o false
 * si la tecla fue presionada.
 */
bool_t readKey();

#endif /* API_INC_API_DEBOUNCE_H_ */
