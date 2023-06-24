# PdM_Ejercicio_2
Implementación mediante el modelo de Máquina de Estados Finitos (MEF) el antirrebote de teclas y la lógica de funcionamiento de un semáforo.

## Integrantes
   Alex Eduardo Guerrero Morocho
   Vicente Paúl Jiménez Ávila
   UNIVERSIDAD DE CUENCA
   Facultad de Ingeniería
   Ingeniería en Telecomunicaciones

## Descripción del Programa 
### main.cpp
   En la implementación del código principal solo se declaran los pines a utilizar. En el void setup se indican dichos pines como INPUT u OUTPUT. 
   Se incluye las librerías necesarias: teclas.h, semaforo.h, Arduino.h, stdio.h y uart.h. Se declara constantes y variables, como las asignaciones de los pines y la declaración de una estructura de datos dbn_t. En la función setup(), configura los pines como entradas o salidas utilizando la función pinMode(). En la función loop(), se lleva a cabo lo siguiente: Se llama a la función InicializarMEF(), que inicializa la Máquina de Estados Finitos (MEF) para los modos del semáforo. Se inicializan dos máquinas de estados finitos para los botones (fsmButtonInit(&dbnSW1) y fsmButtonInit(&dbnSW2)), utilizando la estructura de datos dbn_t. Se inicializa la MEF para el semáforo utilizando la función fsmTrafficLightInit(). Se ejecuta un bucle infinito en el que se actualizan las máquinas de estados finitos para los botones y el semáforo utilizando las funciones fsmButtonUpdate() y fsmTrafficLightUpdate() respectivamente. En cada iteración del bucle, se verifica el estado de los botones y se actualiza el estado del semáforo.

### semaforo.c
   Se declaran las funciones utilizadas en el archivo semaforo.h necesarios para el funcionamiento del semáforo.

### semaforo.h 
   El código proporcionado incluye varias funciones relacionadas con una máquina de estados finitos (MEF) que controla el comportamiento de un semáforo. Aquí está la descripción de cada función:

   fsmTrafficLightInit: Esta función inicializa la MEF del semáforo. Establece el modo de funcionamiento en NORMAL_MODE y apaga todos los LEDs.

   setTrafficLightMode: Esta función establece el modo de funcionamiento del semáforo a un valor específico. Apaga todos los LEDs y establece el modo deseado.

   changeTrafficLightMode: Esta función cambia el modo de funcionamiento del semáforo en función del modo actual. Si el modo actual es NORMAL_MODE, cambia al modo DISCONNECTED_MODE. Si el modo actual es DISCONNECTED_MODE, cambia al modo ALARM_MODE. Si el modo actual es ALARM_MODE, cambia de nuevo al modo NORMAL_MODE.

   InicializarMEF: Esta función inicializa la MEF del semáforo en el modo NORMAL_MODE. Establece el estado actual en ESTADO_INICIAL.

   ActualizarMEF: Esta función actualiza el estado de la MEF del semáforo en el modo NORMAL_MODE. Dependiendo del estado actual, enciende y apaga los LEDs en un patrón específico.

   fsmTrafficLightUpdate: Esta función actualiza la MEF del semáforo en función del modo de funcionamiento. En el modo NORMAL_MODE, llama a la función ActualizarMEF para actualizar el estado. En el modo DISCONNECTED_MODE, parpadea el LED amarillo con un retardo de tiempo baseTime.

   En el modo ALARM_MODE, parpadea el LED rojo con un retardo de tiempo baseTime.

### Teclas.c
   Dentro de la configuración de este archivo se encuentra la declaración de las librerías necesario para la ejecución del archivo main.cpp. A demás, se realiza la modularización de las funciones de las teclas para el antirebote y para el retardo no bloqueante, como también las funciones consideradas cuando el usuario presiona cada uno de los pulsantes y deja de presionarlo dado que cambia los estados dependiendo la acción del usuario. En este archivo dentro de los prototipos de las funciones se declara cada una de las variables o estados usados en las funciones.
### Teclas.h
   En la configuración de este archivo se empieza declarando las librerías y extensión de archivos que van a ser utilizados, como también definimos las variables y los estados que van a ser utilizados dentro de las funciones de este archivo ya sean enumeradas o tipo estructura. Siguiendo la programación se detallan variables globales que están ubicadas en otros documentos de forma que puedan ser utilizadas dentro de las funciones de este archivo para ello es importante detallarlas como extern. A demás, se definen prototipos de funciones de forma que las funciones que se encuentren dentro del archivo puedan utilizar valores de funciones de otros archivos. Se crea diferentes funciones como la del retardo no bloqueante, dentro de esta función permite ejecutar más acciones sin esperar que se cumpla el retardo. También se hace el uso de funciones donde si el botón está en estado "UP" y se presiona, cambia al estado "FALLING", mientras que cuando el botón está en estado "FALLING", espera 40 ms y vuelve a leer el estado del botón. Si el botón sigue presionado, cambia al estado "DOWN" y llama a la función buttonPressed(). Si el botón ya no está presionado, vuelve al estado "UP". Cuando el botón está en estado "DOWN" y se suelta, cambia al estado "RISING", en cuanto el botón está en estado "RISING", espera 40 ms y vuelve a leer el estado del botón. En el caso de que el botón sigue sin estar presionado, cambia al estado "UP" y llama a la función buttonReleased(). Finalmente, si el botón sigue presionado, vuelve al estado "DOWN". 
   
   Se definen la función en el caso de que los pulsantes son presionados, estos pulsantes en el caso de que sean inmediatamente presionados cambias de estado ya sea aumentando el valor de velocidad del encendido de las secuencias de leds o en el cambio de modo de la secuencia integrada normal, alarma o desconectado.  Finalmente se encuentra el detalle de la función de los estados cuando los pulsantes cambian de estado.
### Uart.c 
   En este archivo se declaran las librerias y un uso especial de declaración de archivos donde se conoce comúnmente como un "include guard" o "guardia de inclusión". Es una técnica utilizada en archivos de encabezado (.h) para prevenir problemas de inclusión múltiple cuando un archivo se incluye en varios lugares de un proyecto.
### Uart.h 
   Dentro de este archivo se declaran las librerias de Arduino para poder realizar la impresión del estado de las teclas en el momento que son presionadas. La función myPrint se encarga de imprimir el estado de una tecla en la comunicación UART. Toma como argumento un puntero a una estructura dbn_t, que parece contener información sobre la tecla y su estado. La función verifica el estado de la tecla a través del campo estado de la estructura dbn_t. Si el estado es igual a 1, imprime el mensaje "Tecla: X Estado: Presionado" en la comunicación UART, donde X es el valor de tecla en la estructura restado en 1. Si el estado es igual a 0, imprime el mensaje "Tecla: X Estado: Liberado".