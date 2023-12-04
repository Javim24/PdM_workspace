#include "API_db.h"

bool_t DB_init(DB_datosUsuario_t *  datosUsuario){
	for(uint8_t indice=0; indice<4; indice++){
		datosUsuario->uid[indice] = 0;
	}

	datosUsuario->nombre[0] = "";
	datosUsuario->accesoConcedido = false;

	return true;
}


