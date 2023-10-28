# Resolución de práctica 2 de PdM

La práctica está resuelta utilizando una placa con el micro stm32f103.

## Respuesta a preguntas finales

### ¿Se pueden cambiar los tiempos de encendido de cada led fácilmente en un solo lugar del código o éstos están hardcodeados?
En esta implementación los valores de ciclo de trabajo están hardcodeados. Para mejorar esto se podría crear otro arreglo que contenga el ciclo de trabajo correspondiente a cada paso de la secuencia.

### ¿Qué bibliotecas estándar se debieron agregar para que el código compile? Si las funcionalidades crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usan en el ejercicio.
Se agregaron las bibliotecas estándar stdint y stdbool. Si las funcionalidaes crecieran podría crearse un nuevo archivo de encabezado (por ejemplo delay.h) e incluir ahí las bibliotecas y typedefs necesarios.

### ¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?
El programa no realiza ningún control de los parámetros ingresados.

### ¿Cuán reutilizable es el código implementado?
Se puede reutilizar para implementar varios delays no bloqueantes de manera simple.

### ¿Cuán sencillo resulta en su implementación cambiar el patrón de tiempos de parpadeo?

Es sencillo realizar el cambio de patrón de tiempos a partir de tenerlos ya ordenados en un array. La única consideración importante es que si se quiere cambiar el estado del led por 5 periodos (serían 10 veces), no se puede implementar un ciclo for, ya que el delay no bloqueante vuelve inmeadiantamente si no se cumple el tiempo del delay.
