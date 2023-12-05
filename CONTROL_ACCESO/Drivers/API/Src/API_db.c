#include "API_db.h"

#define LARGO_USUARIOS_AUTORIZADOS				4

static DB_datosUsuario_t usuariosAutorizados[LARGO_USUARIOS_AUTORIZADOS];

DB_datosUsuario_t USUARIO_1;
static uint8_t USUARIO_UID[UID_SIZE] =  {0xC0, 0x78, 0xA8, 0xE4};

bool_t DB_init(DB_datosUsuario_t * datosUsuario){
	for(uint8_t indice=0; indice<UID_SIZE; indice++){
			USUARIO_1.uid[indice] = USUARIO_UID[indice];
		}
	USUARIO_1.nombre[0] =  "Javier";
	USUARIO_1.accesoConcedido =  true;

	usuariosAutorizados[0] = USUARIO_1;

	for(uint8_t indice=0; indice<UID_SIZE; indice++){
		datosUsuario->uid[indice] = 0;
	}

	datosUsuario->nombre[0] = "";
	datosUsuario->accesoConcedido = false;

	return true;
}

void DB_consultarUID(DB_datosUsuario_t * datosUsuario, uint8_t * uid){
	bool_t accesoConcedido = false;

	for(uint8_t indice=0; indice<UID_SIZE; indice++){
		datosUsuario->uid[indice] = uid[indice];
	}

	for(uint8_t indice=0; indice < LARGO_USUARIOS_AUTORIZADOS; indice++){
		if( (uint32_t) datosUsuario->uid == (uint32_t) usuariosAutorizados[indice].uid){
			accesoConcedido = true;
			break;
		}
	}

	datosUsuario->nombre[0] = "Hola";
	datosUsuario->accesoConcedido = accesoConcedido;
}


