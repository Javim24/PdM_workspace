/**
 * @brief  Implementación de funciones del
 * 		   módulo lcd.
 */

#include "API_lcd.h"
#include "API_types.h"

#define _4BIT_MODE					0x28
#define DISPLAY_CONTROL				(1<<3)
#define RETURN_HOME					(1<<1)
#define ENTRY_MODE					(1<<2)
#define AUTOINCREMENT				(1<<1)
#define DISPLAY_ON					(1<<2)
#define  CLR_LCD					1
#define COMMAND						0
#define DATA						1
#define ENABLE						(1<<2)
#define POS_BACKLIGHT				(3)
#define SET_CURSOR					(1<<7)
#define CURSOR_ON					1<<1
#define CURSOR_BLINK				1

#define NULL_CHAR					'\0'

static uint8_t back_light = 1;

static LCD_StatusTypedef LCD_sendMsg(uint8_t, uint8_t);
static LCD_StatusTypedef LCD_sendByte(uint8_t);
static LCD_StatusTypedef LCD_sendNibble(uint8_t, uint8_t);
//static LCD_StatusTypedef LCD_delay(uint32_t);

static const uint8_t LCD_INIT_CMD[] = {
_4BIT_MODE, DISPLAY_CONTROL, RETURN_HOME,
ENTRY_MODE | AUTOINCREMENT,
DISPLAY_CONTROL | DISPLAY_ON, CLR_LCD };

LCD_StatusTypedef LCD_init() {
	bool_t estadoI2C = port_init();
	if (estadoI2C == false)
		return LCD_ERROR;

	port_delay(20);
	if (LCD_sendNibble(0x03, COMMAND) == LCD_ERROR)
		return LCD_ERROR;

	port_delay(10);

	if (LCD_sendNibble(0x03, COMMAND) == LCD_ERROR)
		return LCD_ERROR;

	port_delay(1);

	if (LCD_sendNibble(0x02, COMMAND) == LCD_ERROR)
		return LCD_ERROR;

	for (uint8_t indice = 0; indice < sizeof(LCD_INIT_CMD); indice++) {
		port_delay(1);
		if (LCD_sendMsg(LCD_INIT_CMD[indice], COMMAND) == LCD_ERROR)
			return LCD_ERROR;
	}
	return LCD_OK;
}

LCD_StatusTypedef LCD_clear() {
	return LCD_sendMsg(CLR_LCD, COMMAND);
}

LCD_StatusTypedef LCD_setCursor(uint8_t fila, uint8_t posicion) {
	if (fila != LCD_FILA_1 && fila != LCD_FILA_2)
		return LCD_ERROR;

	return LCD_sendMsg(SET_CURSOR | fila, COMMAND);
}

LCD_StatusTypedef LCD_printText(char *ptrTexto) {
	if (ptrTexto == NULL)
		return LCD_ERROR;

	uint8_t contadorPosicion = 0;
	LCD_setCursor(LCD_FILA_1, 0);
	while ((*ptrTexto) != NULL_CHAR) {
		if (LCD_printChar(*ptrTexto++) == LCD_ERROR)
			return LCD_ERROR;

		contadorPosicion++;
		if (contadorPosicion == LCD_CANTIDAD_COLUMNAS)
			LCD_setCursor(LCD_FILA_2, 0);
		else if (contadorPosicion
				== (LCD_CANTIDAD_COLUMNAS * LCD_CANTIDAD_FILAS))
			break;						//CORTA EL TEXTO PERO NO DEVUELVE ERROR
	}

	return LCD_OK;
}

LCD_StatusTypedef LCD_printChar(char dato) {
	return LCD_sendMsg(dato, DATA);
}

LCD_StatusTypedef LCD_cursorOn(){
	return LCD_sendMsg(DISPLAY_CONTROL | DISPLAY_ON | CURSOR_ON | CURSOR_BLINK, COMMAND);
}

LCD_StatusTypedef LCD_cursorOff(){
	return LCD_sendMsg(DISPLAY_CONTROL | DISPLAY_ON, COMMAND);
}

static LCD_StatusTypedef LCD_sendMsg(uint8_t dato, uint8_t rs) {
	if (LCD_sendByte(rs | (back_light << POS_BACKLIGHT) | (dato & 0xF0))
			== LCD_ERROR)
		return LCD_ERROR;

	if (LCD_sendByte(rs | (back_light << POS_BACKLIGHT) | (dato & 0x0F) << 4)
			== LCD_ERROR)
		return LCD_ERROR;

	return LCD_OK;
}

/**
 * @brief Envía los 4 bits menos significativos de dato,
 * 		  junto con los bits de rs, backlight.
 */
static LCD_StatusTypedef LCD_sendNibble(uint8_t dato, uint8_t rs) {
	return LCD_sendByte(rs | (back_light << POS_BACKLIGHT) | (dato & 0x0F) << 4);

}

static LCD_StatusTypedef LCD_sendByte(uint8_t _byte) {
	if (!port_i2cWriteByte(_byte | ENABLE))
		return LCD_ERROR;

	port_delay(1);

	if (!port_i2cWriteByte(_byte))
		return LCD_ERROR;

	return LCD_OK;
}
