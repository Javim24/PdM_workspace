# Práctica 4
## Objetivo:
Implementar un MEF para trabajar con anti-rebotes por software.

## Punto 1:
Se implementa una máquina de estados para realizar la lectura de un botón de manera que se eliminen los rebotes producidos. Al presionar el botón se enciende el led presente en la placa nucleo f401.
La máquina de estados utiliza el módulo de delay no bloqueante creado en la práctica anterior.

## Punto 2:
Se adapta el código realizado en el punto anterior para implementar un módulo API_debounceFSM que encapsula las funciones internas de la máquina de estados para que el usuario utilice una API pública para leer el estado del botón. En este programa se varía periodo de conmutación del led de la placa entre 100ms y 500ms cada vez que se presiona el botón.
