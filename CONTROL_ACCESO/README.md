# Trabajo final para las materias Programación de Microcontroladores y Protocolos de Comunicación en Sistemas Embebidos
El trabajo consiste en un sistema de control de acceso que utiliza tarjetas RFID. Se conecta al microcontrolador
un lector RFID-RC522. Al acercar una tarjeta RFID del tipo MIFARE Classic al lector, este obtiene su código de identificación único (UID).
A partir de este código, el microcontrolador consulta en la base de datos para ver si el código se encuentra guardado. En caso afirmativo
muestra un mensaje de acceso concedido en un display LCD. En caso de que el UID no se encuentre guardado en la base de datos, se muestra
el mensaje de acceso denegado en el LCD.
## Autor
Ing. Javier Mosconi

Carrera de Especialización en Sistemas Embebidos - FIUBA

Año 2023
