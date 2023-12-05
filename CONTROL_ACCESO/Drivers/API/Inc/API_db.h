/**
 * @brief Módulo que simula una base de datos.
 *        Implementa una interfaz pública para que
 *        la aplicación que lo utilice no conozca los detalles
 *        internos del funcionamiento de la base de datos.
 */

#ifndef API_INC_API_DB_H_
#define API_INC_API_DB_H_

#include "API_types.h"


#define UID_SIZE			4           //tamaño en bytes del UID de las tarjetas RFID

/**
*   @brief Inicializa la base de datos.
*   @retval Estado de ejecución.
*/
bool_t DB_init();

/**
*   @brief Realiza una consulta a la base
*          de datos a partir de un UID.
*   @retval Devuelve verdadero si el UID se
*           encuentra en la base de datos, o falso
*           si no se encuentra.
*/
bool_t DB_consultarUID(uint8_t *);

#endif /* API_INC_API_DB_H_ */
