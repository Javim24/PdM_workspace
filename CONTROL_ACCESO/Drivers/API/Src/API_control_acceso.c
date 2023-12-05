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
#include "API_db.h"
#include "string.h"
#include "stdio.h"


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

static DB_datosUsuario_t datosUsuario;

API_StatusTypedef controlAcceso_init(){
	estadoFSM = ESTADO_INICIAL;
	if (LCD_init() == API_ERROR)
		return API_ERROR;
	if (LCD_printText("Aproxime tarjeta...") == API_ERROR)
		return API_ERROR;

	mfrc522_init();
	//db init
	if ( DB_init(&datosUsuario) == false)
		return API_ERROR;
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

	if (estadoFSM == nuevoEstado)
		return API_OK;

	estadoFSM = nuevoEstado;
	//actualizar salida
	switch(estadoFSM){
		case BUSQUEDA_TARJETA:
			LCD_printText("Aproxime tarjeta...");
			break;
		case TARJETA_CORRECTA:{
					char strBuffer[64];
					sprintf(strBuffer, "Tarjeta:\n");
					for(uint8_t indice=0; indice<4; indice++){
						char tmp[15];
						sprintf(tmp, "%X:", datosUsuario.uid[indice]);
						strcat(strBuffer, tmp);
					}
					LCD_printText(strBuffer);
			break;
		}
		case TARJETA_INCORRECTA:
			LCD_printText("Tarjeta incorrecta");
			break;
		default:
			//manejar error
			//handler_default();
			break;
		}

	return API_OK;
}


static FSM_STATE_enum handler_busqueda_tarjeta(){
	//buscar tarjeta y devolver el siguiente estado
	uint8_t uid[4];
	if ( mfrc522_leerUIDTarjeta(uid) ){
//		memcpy(datosUsuario.uid, uid, 4);
		DB_consultarUID(&datosUsuario, uid);
		if (datosUsuario.accesoConcedido)
			return TARJETA_CORRECTA;
		else
			return TARJETA_INCORRECTA;

		//		char strBuffer[16];
//		sprintf(strBuffer, "Tarjeta:\n");
//		for(uint8_t indice=0; indice<4; indice++){
//			char tmp[15];
//			sprintf(tmp, "%X:", uid[indice]);
//			strcat(strBuffer, tmp);
//		}
//		LCD_printText(strBuffer);
	}

	return BUSQUEDA_TARJETA;
}

static FSM_STATE_enum handler_tarjeta_correcta(){
	//mostrar en pantalla resultado por un tiempo


	return BUSQUEDA_TARJETA;
}

static FSM_STATE_enum handler_tarjeta_incorrecta(){
	//mostrar en pantalla resultado por un tiempo
	HAL_Delay(5000);
	return BUSQUEDA_TARJETA;
}
