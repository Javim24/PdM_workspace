#ifndef API_INC_API_DB_H_
#define API_INC_API_DB_H_

#include "API_types.h"

typedef struct {
	uint8_t uid[4];
	uint8_t nombre[16];
	bool_t accesoConcedido;
} DB_datosUsuario_t;

bool_t DB_init(DB_datosUsuario_t *);
void DB_consultarUID(DB_datosUsuario_t *);

#endif /* API_INC_API_DB_H_ */
