#ifndef API_INC_API_DB_H_
#define API_INC_API_DB_H_

#include "API_types.h"

#define UID_SIZE			4
#define LARGO_NOMBRE		16

typedef struct {
	uint8_t uid[UID_SIZE];
	uint8_t nombre[LARGO_NOMBRE];
	bool_t accesoConcedido;
} DB_datosUsuario_t;

//DB_datosUsuario_t USUARIO_1; //= {
//	.uid = {0xC0, 0x78, 0xA8, 0xE4},
//	.nombre =  "Javier",
//	.accesoConcedido =  true
//};

bool_t DB_init(DB_datosUsuario_t *);
void DB_consultarUID(DB_datosUsuario_t *, uint8_t *);

#endif /* API_INC_API_DB_H_ */
