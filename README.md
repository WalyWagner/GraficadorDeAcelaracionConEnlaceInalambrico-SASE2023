# Graficador de Aceleración con Enlace Inalámbrico 
-by WSW-
Diseñado para funcionar en un Cortex M0+ del kit de desarrollo FRDMKL46Z

# Cómo utilizar:

-> Importa este proyecto en tu IDE Eclipse (para microcontroladores NXP y FLS, utiliza MCUXpresso).

	File → Import → C/C++ → Existing Code as Makefile Project 

-> Navega y selecciona la carpeta: SASE2023_WalterWagner_Graf.-Acel.-Inalambrico.

-> En "Toolchain for Indexer Settings", selecciona: NXP MCU Tools.

-> Haz clic en "Finish".

# Información Importante:

-> En la carpeta "Source" encontrarás un archivo que contiene el acuerdo de licencia.

-> En la carpeta raíz del proyecto encontrarás un PDF que contiene la documentación del mismo.

-----------------------------------------------------

# RESUMEN:

En este trabajo se aplican todos los contenidos temáticos de la asignatura Sistemas Digitales 2 (F.C.E.I.A. – U.N.R.) al utilizar el microcontrolador Cortex M0+ de la placa de desarrollo FRDM-KL46Z en una aplicación práctica con el fin de establecer una comunicación inalámbrica con otro dispositivo. Al mismo tiempo se busca explorar el uso de diversos protocolos, como I2C, SPI y UART, para realizar intercambio de mensajes con periféricos de entrada (sensor de aceleración y pulsadores en este caso) y de salida (pantalla OLED, LCD y LEDs).

El intercambio de mensajes entre los dos dispositivos es implementado utilizando estructuras de datos de tipo cola circular en la recepción y transacciones a cargo de DMA en la transmisión. En ambos casos el protocolo para comunicarse con el exterior es UART.

El funcionamiento del sistema se modela utilizando el formalismo de Máquina de Estado Finito / Statecharts UML y el código C refleja el modelo propuesto. El desarrollo de la aplicación incorpora funciones de biblioteca provistas por el fabricante. La implementación se programó y depuró utilizando el ambiente MCUXpresso.

El dispositivo desarrollado puede comunicarse con la PC por Radio Frecuencia (RF) y cuenta además, con dos modos de trabajo: en uno de ellos se interactúa con un software provisto por la cátedra “SD2_TP3_Master”. El mismo es capaz de encuestar el estado de los pulsadores, graficar la aceleración y controlar los LEDs de la placa. En el otro modo, se envían tramas periódicamente, informando la aceleración en los tres ejes, para ser procesadas en PC mediante un software para animación 3D que emula el movimiento de un avión.

Mediante el uso de los pulsadores propios de la placa se cambia de un modo de trabajo al otro y se muestra, para un correcto funcionamiento, un mensaje que informa el modo operativo actual, en un display OLED comunicado vía protocolo SPI. 

Para el primer modo antes mencionado, la placa FRDM-KL46Z es el dispositivo esclavo en la comunicación, recibiendo las peticiones del maestro y dando la respuesta correspondiente a los diferentes mensajes. El dispositivo maestro es siempre la computadora.

En el antes mencionado display OLED, comunicado por protocolo SPI, se muestra además el módulo de la aceleración con una tasa de refresco adecuada para una correcta visualización. También se imprime por pantalla, pero en un display de cristal líquido LCD comunicado al micro por protocolo I2C, mostrando los mensajes “SASE” y “2023” de manera alternada.

A lo largo del proceso de convertir el problema modelado por Máquinas de Estado Finito en una implementación en lenguaje C consistente, se trabajó en capas diferenciando aplicación de drivers, y haciendo uso de archivos y carpetas se logró una organización intuitiva del proyecto. Esto permite, por un lado, reutilizar fácilmente código de cualquier capa en un futuro, pero por el otro, también simplificar en gran medida la depuración y optimización del proyecto. 

-----------------------------------------------------
