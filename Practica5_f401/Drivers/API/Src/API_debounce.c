/*
 * API_debounce.c
 *
 * En este archivo se encuentran las variables privadas,
 * estructuras y funciones que utiliza la máquina de estados.
 *
 *  Created on: Nov 11, 2023
 *      Author: javi
 */

#include "API_debounce.h"

/**
 * Enum para almacenar los estados que puede
 * tomar el botón
 */
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

static debounceState_t debounceState;			//variable de estado global

/**
 * Estructura para almacenar el pin
 * y el puerto del micro en el que
 * se encuentra el botón.
 */
typedef struct{
	uint16_t pin;
	GPIO_TypeDef * port;
} button_typedef;

static button_typedef button;			//estructura para almacenar el botón que se debe leer

static delay_t debounceDelay;			//estructura utilizada para llevar a cabo el delay no bloqueante para eliminar rebotes
static const uint8_t DELAY_TIME = 40;	//constante para el tiempo de anti-rebote

static bool_t isButtonPressed = false;	//variable que indica si el botón fue presionado

/**
 * Función que ejecuta una acción cuando
 * se presiona el botón.
 */
static void buttonPressed();
static void buttonReleased();

/**
 * Función que lee el estado
 * del botón.
 */
static bool_t readButton();


/**
 * Inicializa la FSM. Configura el estado inicial,
 *  inicializa el delay no bloqueante y guarda
 *  los datos del pin y puerto en que está conectado
 *  el botón.
 */
void debounceFSM_init(GPIO_TypeDef * buttonPort, uint16_t buttonPin){
	uartInit();
	debounceState = BUTTON_UP;
	delayInit(&debounceDelay, DELAY_TIME);
	button.pin = buttonPin;
	button.port = buttonPort;
}


/**
 * Lee la entrada y actualiza el estado
 * y actúa en consecuencia.
 * Cuando se detecta que se ha presionado el botón
 * llama a la función buttonPressed.
 */
void debounceFSM_update(){
	bool_t isButtonPressed;

	switch(debounceState){

		case BUTTON_UP:
				isButtonPressed = readButton();

				if(isButtonPressed){
					debounceState = BUTTON_FALLING;
				}
			break;

		case BUTTON_FALLING:
				if(delayRead(&debounceDelay)){
					isButtonPressed = readButton();
					if(isButtonPressed){
						buttonPressed();			//llamo a la función buttonPressed
						debounceState = BUTTON_DOWN;
					}
					else{
						debounceState = BUTTON_UP;
					}
				}

			break;

		case BUTTON_DOWN:

				isButtonPressed = readButton();

				if(! isButtonPressed){
					debounceState = BUTTON_RAISING;
				}
			break;

		case BUTTON_RAISING:
			if(delayRead(&debounceDelay)){
				isButtonPressed = readButton();
				if(! isButtonPressed){
						buttonReleased();
						debounceState = BUTTON_UP;
					}
				else{
					debounceState = BUTTON_DOWN;
				}
			}

			break;

		default:
			debounceFSM_init(button.port, button.pin);
			break;
	}

}

/**
 * Setea la variable privada isButtonPressed en
 * verdadero.
 */
static void buttonPressed(){
	isButtonPressed = true;
	uartSendString((uint8_t*) "El botón ha sido presionado\r\n");
}

/**
 * envía por uart cuando se suelta el botón
 */
static void buttonReleased(){
	uartSendString((uint8_t*) "El botón ha sido soltado\r\n");
}

/**
 * Lee el estado de la variable isButtonPressed,
 * y luego la pone como falso.
 */
bool_t readKey(){
	bool_t key = isButtonPressed;
	isButtonPressed = false;
	return key;
}

/**
 * Función que utiliza la HAL para leer el estado
 * del botón.
 */
static bool_t readButton(){
	return ! (bool_t) HAL_GPIO_ReadPin(button.port, button.pin);
}
