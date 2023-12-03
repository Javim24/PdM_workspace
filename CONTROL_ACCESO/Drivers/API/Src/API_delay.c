/*
 * API_delay.c
 *
 *  Created on: Nov 5, 2023
 *      Author: javi
 */

#include "API_delay.h"

/*
	*	Esta función sirve para inicializar la estructura que maneja	
	* el delay no bloqueante.
*/

void delayInit( delay_t * delay, tick_t duration ) {
	if(delay != NULL){
		delay->duration = duration;
		delay->running = false;
	}
}

/*
	*	Esta función se utiliza para consultar si el delay 
	*	ha completado la duración requerida. En caso afirmativo,
	*	devuelve Verdadero, caso contrario devuelve Falso.
	*	Si es la primera vez que se llama a la función,
	* se pone delay->running = Verdadero. 
*/

bool_t delayRead( delay_t * delay ){
	tick_t actualTime = HAL_GetTick();
	bool_t status = false;

	if(delay != NULL){
		if (delay->running) {
			if ((actualTime - delay->startTime) >= delay->duration) {
				delay->running = false;
				status = true;
			}
		}
		else {
			delay->running = true;
			delay->startTime = actualTime;
		}
	}

	return status;
}

/*
	*	Esta función se utiliza para cambiar la duración de un delay ya inicializado.
*/

void delayWrite( delay_t * delay, tick_t duration ){
	if(delay != NULL)
		delay->duration = duration;
}
