/**
 * @brief Módulo que controla el lector RFID
 * 		  MFRC522. Permite  el  acceso a funciones
 * 		  para inicializar el módulo y detectar la
 * 		  presencia de una tarjeta en  el campo RF
 * 		  del lector.
 */

#ifndef API_INC_API_MFRC522_H_
#define API_INC_API_MFRC522_H_

#include "API_types.h"

void mfrc522_init();
void mfrc522_reset();
bool_t mfrc522_leerUIDTarjeta(uint8_t * uid);



#endif /* API_INC_API_MFRC522_H_ */
