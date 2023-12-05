/**
 * @brief Módulo que implementa el sistema de
 * 		  control de acceso por rfid. Se encarga de
 * 		  englobar los periféricos como el lector rfid y
 * 		  el display lcd, e implementa una máquina de estados
 * 		  para controlar la lógica de funcionamiento del
 * 		  sistema. Permite el acceso a funciones públicas
 * 		  del módulo.
 */


#ifndef API_INC_API_CONTROL_ACCESO_H_
#define API_INC_API_CONTROL_ACCESO_H_

/**
 * @brief Enumeración para control de errores.
 */
typedef enum {
	API_OK,
	API_ERROR
} API_StatusTypedef;

/**
 * @brief Función de inicio del sistema
 * 		  de control de acceso.
 * @retval API_StatusTypedef
 */
API_StatusTypedef controlAcceso_init();

/**
 * @brief Función que actualiza el estado
 * 		  del sistema según la entrada.
 * @retval API_StatusTypedef
 */
API_StatusTypedef controlAcceso_update();


#endif /* API_INC_API_CONTROL_ACCESO_H_ */
