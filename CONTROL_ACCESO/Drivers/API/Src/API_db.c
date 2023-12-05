#include "API_db.h"

bool_t DB_init(DB_datosUsuario_t *  datosUsuario){
	for(uint8_t indice=0; indice<4; indice++){
		datosUsuario->uid[indice] = 0;
	}

	datosUsuario->nombre[0] = "";
	datosUsuario->accesoConcedido = false;

	return true;
}

void DB_consultarUID(DB_datosUsuario_t * datosUsuario, uint8_t * uid){
	for(uint8_t indice=0; indice<4; indice++){
		datosUsuario->uid[indice] = uid[indice];
	}
	datosUsuario->nombre[0] = "Hola";
	datosUsuario->accesoConcedido = false;
}


