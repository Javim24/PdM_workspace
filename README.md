# Programación de microcontroladores - CESE - FIUBA
Autor: Ing. Mosconi Javier \
Año 2023

## Resumen de prácticas
### Práctica 1:
Práctica para familiarizarse con el entorno de trabajo y con la placa. Consiste en la implementación de una secuencia periódica de encendido de tres leds. Esta prática fue realizada con la placa Blue Pill, que tiene un microcontrolador stm32f103CB ([info de la placa](https://stm32-base.org/boards/STM32F103C8T6-Blue-Pill.html)) y se le conectaron tres leds en una protoboard.

### Práctica 2:
Consiste en la implementación de un delay no bloqueante. Se utiliza el SysTick para verificar si se ha cumplido el tiempo de delay. Esta práctica fue realizada con la placa Blue Pill.

### Práctica 3:
Esta práctica consiste en la modularización de las funciones de delay no bloqueantes utilizadas en la práctica 2. La práctica fue realizada con la placa NUCLEO-F401RE.

### Práctica 4:
Esta práctica consiste en la creación de una máquina de estados para eliminar el rebote al pulsar un botón. Esta realizada de manera modular, y también integra el módulo de retardo no bloqueante de las prácticas anteriores. La práctica fue realizada con la placa NUCLEO-F401RE.

### Práctica 5:
Esta práctica implementa un módulo con funciones para facilitar la utilización de la uart del microcontrolador. En la parte 2 de la práctica se integra con el programa de la práctica anterior para envíar un mensaje cuando se presiona y suelta el botón de la placa.

### TP final - Control de acceso
El trabajo final para la materia consiste en un sistema de control de acceso que utiliza tarjetas RFID.
