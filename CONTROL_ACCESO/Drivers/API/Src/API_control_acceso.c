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

/**
 * @brief Enumeración de estados posibles de
 *		  la máquina de estados.
 */
typedef enum {
	BUSQUEDA_TARJETA,		//el sistema se encuentra buscando una tarjeta RFID
	TARJETA_CORRECTA,//se detectó una tarjeta que está guardada en la base de datos
	TARJETA_INCORRECTA				//la tarjeta no está en la base de datos
} FSM_STATE_enum;

static FSM_STATE_enum estadoFSM;//variable global privada para almacenar el estado actual.
static const FSM_STATE_enum ESTADO_INICIAL = BUSQUEDA_TARJETA;//definición del estado inicial del sistema.

/**
 *	@brief Declaración de funciones privadas para el manejo
 *		   de cada estado. Cada una devuelve un nuevo estado
 *		   que es el siguiente estado al que pasa la máquina
 *		   de estados.
 */
static FSM_STATE_enum handler_busqueda_tarjeta();
static FSM_STATE_enum handler_tarjeta_correcta();
static FSM_STATE_enum handler_tarjeta_incorrecta();

//función para mostrar un mensaje de error en la pantalla
static void errorHandler();

/**
 *	@brief Variables globales privadas.
 */
static uint8_t uid[UID_SIZE]; //en esta variable se guarda el UID de la última tarjeta leída.
static delay_t delayFSM;	//estructura para controlar el delay no bloqueante
static const tick_t DELAY_MENSAJE = 3000;//tiempo en ms que se muestra un mensaje en el LCD

//mensajes para mostrar en el LCD para cada estado
static const char mensajeBusquedaTarjeta[] = "APROXIME UN TAG";
static const char mensajeTarjetaCorrecta[] = "ACCESO CONCEDIDO";
static const char mensajeTarjetaIncorrecta[] = "ACCESO DENEGADO";

/**
 *	@brief Función que inicializa todos los módulos
 *		   y variables necesarias para el funcionamiento
 *		   del sistema.
 *	@retval Estado de ejecución.
 */
API_StatusTypedef controlAcceso_init() {
	estadoFSM = ESTADO_INICIAL;
	if (LCD_init() == API_ERROR)
		return API_ERROR;

	mfrc522_init();

	//db init
	if (DB_init() == false)
		return API_ERROR;

	//delay init
	delayInit(&delayFSM, DELAY_MENSAJE);//configura el delay no bloqueante para que dure DELAY_MENSAJE = 3 segundos

	if (LCD_printText(mensajeBusquedaTarjeta) == API_ERROR)
		return API_ERROR;

	return API_OK;
}

/**
 *	@brief Función que actualiza el estado de la
 *		   máquina de estados, dependiendo de la
 *		   lectura de una tarjeta en el lector RFID.
 *	@retval Estado de ejecución.
 */
API_StatusTypedef controlAcceso_update() {
	FSM_STATE_enum nuevoEstado;

	switch (estadoFSM) {
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
		nuevoEstado = ESTADO_INICIAL;
		break;
	}

	if (estadoFSM == nuevoEstado)
		return API_OK;		//si no hay cambio de estado, la función finaliza.

	//se actualiza la salida luego de que haya un cambio de estado
	estadoFSM = nuevoEstado;
	switch (estadoFSM) {
	case BUSQUEDA_TARJETA:
		LCD_printText(mensajeBusquedaTarjeta);
		break;
	case TARJETA_CORRECTA: {
		LCD_printText(mensajeTarjetaCorrecta);
		break;
	}
	case TARJETA_INCORRECTA:
		LCD_printText(mensajeTarjetaIncorrecta);
		break;
	default:
		errorHandler();
		break;
	}

	return API_OK;
}

/**
 *	@brief Implementa la lógica para manejar el
 *		   estado BUSQUEDA_TARJETA. Se encarga de consultarle
 *		   al lector RFID si detecta una tarjeta, y en caso afirmativo
 *		   verifica si el UID se encuentra en la base de datos.
 *	@retval Nuevo estado.
 */
static FSM_STATE_enum handler_busqueda_tarjeta() {
	if (mfrc522_leerUIDTarjeta(uid)) {
		if (DB_consultarUID(uid))
			return TARJETA_CORRECTA;
		else
			return TARJETA_INCORRECTA;
	}

	return BUSQUEDA_TARJETA;
}

/**
 *	@brief Implementa la lógica para manejar el
 *		   estado TARJETA_CORRECTA. Utiliza un delay
 *		   no bloqueante para esperar un tiempo determinado por
 *		   la constante DELAY_MENSAJE y luego volver al estado BUSQUEDA_TARJETA.
 *	@retval Nuevo estado.
 */
static FSM_STATE_enum handler_tarjeta_correcta() {
	if (delayRead(&delayFSM))
		return BUSQUEDA_TARJETA;

	return TARJETA_CORRECTA;
}

/**
 *	@brief Implementa la lógica para manejar el
 *		   estado TARJETA_INCORRECTA. Utiliza un delay
 *		   no bloqueante para esperar un tiempo determinado por
 *		   la constante DELAY_MENSAJE y luego volver al estado BUSQUEDA_TARJETA.
 *	@retval Nuevo estado.
 */
static FSM_STATE_enum handler_tarjeta_incorrecta() {
	if (delayRead(&delayFSM))
		return BUSQUEDA_TARJETA;

	return TARJETA_INCORRECTA;
}

/**
 * @brief Muestra un mensaje de error en el LCD.
 */
static void errorHandler() {
	LCD_printText("Error");
}
