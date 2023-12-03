/**
 * @brief Implementación de funciones públicas
 * 		  definidas en API_control_acceso.h y
 * 		  declaración e implementación de funciones
 * 		  y variables privadas del módulo.
 */

#include "API_control_acceso.h"
#include "API_delay.h"
#include "API_lcd.h"
#include "API_mfrc522.h"
#include "string.h"


/**
 * @brief Enumeración de estados posibles del sistema.
 */
typedef enum {
	BUSQUEDA_TARJETA,
	TARJETA_CORRECTA,
	TARJETA_INCORRECTA
} FSM_STATE_enum;

static FSM_STATE_enum estadoFSM;								//variable privada para almacenar el estado.
static const FSM_STATE_enum ESTADO_INICIAL = BUSQUEDA_TARJETA;	//definición del estado inicial del sistema.

static FSM_STATE_enum handler_busqueda_tarjeta();
static FSM_STATE_enum handler_tarjeta_correcta();
static FSM_STATE_enum handler_tarjeta_incorrecta();



API_StatusTypedef controlAcceso_init(){
	estadoFSM = ESTADO_INICIAL;
	if (LCD_init() == API_ERROR)
		return API_ERROR;
	if (LCD_printText("OK") == API_ERROR)
		return API_ERROR;

	mfrc522_init();
	//db init
	//delay init

	return API_OK;
}

API_StatusTypedef controlAcceso_update(){
	FSM_STATE_enum nuevoEstado;
	switch(estadoFSM){
	case BUSQUEDA_TARJETA:
		nuevoEstado = handler_busqueda_tarjeta();
		break;
	case TARJETA_CORRECTA:
		nuevoEstado = handler_tarjeta_correcta();
		break;
	case TARJETA_INCORRECTA:
		nuevoEstado = handler_tarjeta_incorrecta();
		break;
	default:
		//manejar error
		//handler_default();
		break;
	}

	estadoFSM = nuevoEstado;
	return API_OK;
}


static FSM_STATE_enum handler_busqueda_tarjeta(){
	//buscar tarjeta y devolver el siguiente estado
	uint8_t uid[4];
	if ( mfrc522_leerUIDTarjeta(uid) ){
		char strBuffer[16];
		sprintf(strBuffer, "%X", *uid);
		LCD_printText(strBuffer);
	}

	return BUSQUEDA_TARJETA;
}

static FSM_STATE_enum handler_tarjeta_correcta(){
	//mostrar en pantalla resultado por un tiempo
	return TARJETA_CORRECTA;
}

static FSM_STATE_enum handler_tarjeta_incorrecta(){
	//mostrar en pantalla resultado por un tiempo
	return TARJETA_INCORRECTA;
}
