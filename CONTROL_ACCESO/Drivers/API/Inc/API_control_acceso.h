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
 * @brief Función de inicio del sistema
 * 		  de control de acceso.
 */
void controlAcceso_init();

/**
 * @brief Función que actualiza el estado
 * 		  del sistema según la entrada.
 */
void controlAcceso_update();


#endif /* API_INC_API_CONTROL_ACCESO_H_ */
