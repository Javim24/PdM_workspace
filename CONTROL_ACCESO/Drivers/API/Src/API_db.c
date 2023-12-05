/**
 * @brief Módulo que simula una base de datos.
 *        En este archivo se encuentra la implementación
 *		  de funciones de la base de datos y las variables privadas.
 */

#include "API_db.h"

#define LARGO_USUARIOS_AUTORIZADOS				4					//cantidad de usuarios que pueden ser guardados

static uint32_t * usuariosAutorizados[LARGO_USUARIOS_AUTORIZADOS];	//arreglo de punteros a UIDs autorizados

static const uint8_t USUARIO_1[] = {0xC0, 0x78, 0xA8, 0xE4};		//definición de una tarjeta autorizada

/**
*   @brief Inicializa la base de datos. 
*		   Copia el UID de USUARIO_1 en el 
*		   arreglo de UIDs autorizados. Como el UID son
*		   4 bytes, esto puede ser interpretado como un uint32_t.
*   @retval Estado de ejecución.
*/
bool_t DB_init(){
	usuariosAutorizados[0] = (uint32_t *) USUARIO_1;
	
	return true;
}


/**
*   @brief Realiza una consulta a la base
*          de datos a partir de un UID. Recorre el vector
*		   de usuarios autorizados y compara el UID como uint32_t.
*			Si el UID coincide con alguno en el vector, devuelve verdadero.
*   @retval Devuelve verdadero si el UID se
*           encuentra en la base de datos, o falso
*           si no se encuentra.
*/
bool_t DB_consultarUID(uint8_t * uid){
	bool_t accesoConcedido = false;

	uint32_t uid_uint32 = * ((uint32_t *) uid);

	for(uint8_t indice=0; indice < LARGO_USUARIOS_AUTORIZADOS; indice++){
		if (usuariosAutorizados[indice] == NULL)							//verificación para evitar errores al leer un puntero NULL
            continue;
		if( uid_uint32 == *usuariosAutorizados[indice]){
			accesoConcedido = true;
			break;
		}
	}

	return accesoConcedido;
}


