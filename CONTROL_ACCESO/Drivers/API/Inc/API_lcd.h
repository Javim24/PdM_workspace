/**
 * @brief Módulo que controla las funcionalidades
 * 		  del display LCD.
 */

#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_

#include "API_lcd_port.h"


#define LCD_FILA_1						0x00
#define LCD_FILA_2						0x40
#define LCD_CANTIDAD_COLUMNAS			16
#define LCD_CANTIDAD_FILAS				2

/**
 * @brief Enum para devolver resultado de acciones del LCD.
 */
typedef enum {
	LCD_OK,
	LCD_ERROR
} LCD_StatusTypedef;


LCD_StatusTypedef LCD_init();
LCD_StatusTypedef LCD_clear();
LCD_StatusTypedef LCD_printText(char *);
LCD_StatusTypedef LCD_printChar(char);
LCD_StatusTypedef LCD_setCursor(uint8_t, uint8_t);
LCD_StatusTypedef LCD_cursorOn();
LCD_StatusTypedef LCD_cursorOff();


#endif /* API_INC_API_LCD_H_ */
