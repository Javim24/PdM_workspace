/*
 * API_delay.c
 *
 *  Created on: Nov 5, 2023
 *      Author: javi
 */

#include "API_delay.h"

void delayInit( delay_t * delay, tick_t duration ) {
	if(delay != NULL){
		delay->duration = duration;
		delay->running = false;
	}
}


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


void delayWrite( delay_t * delay, tick_t duration ){
	if(delay != NULL)
		delay->duration = duration;
}
