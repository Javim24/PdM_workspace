/**
 * @brief Implementación de funciones públicas
 * 		  definidas en API_control_acceso.h y
 * 		  declaración e implementación de funciones
 * 		  y variables privadas del módulo.
 */

#include "API_control_acceso.h"

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



void controlAcceso_init(){
	estadoFSM = ESTADO_INICIAL;
}

void controlAcceso_update(){
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
}


static FSM_STATE_enum handler_busqueda_tarjeta(){
	//buscar tarjeta y devolver el siguiente estado
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
