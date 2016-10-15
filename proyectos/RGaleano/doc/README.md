PiGuardian
===================
Resumen
-------------

**PiGuardian** es un sistema embebido que detecta movimiento. Su objetivo es alertar al usuario, a través de un e-mail, cuando exista una intrusión.
Descripción
-------------

**PiGuardian** consiste de los siguientes componentes:



> - Raspberry Pi 3
> - Sensor de movimiento PIR HC-SR501
> - 2 Leds (1 rojo y 1 verde)
#### Raspberry Pi 3

Es la unidad central del sistema embebido. Recibirá y manejará la entrada del sensor PIR para producir las salidas correspondientes de acuerdo al programa.

#### Sensor de movimiento PIR

A través del sensor PIR (Passive Infrared), detecta el movimiento de objetos grandes, incluyendo personas. El módulo integra toda la electrónica necesaria para el soporte del sensor PIR propiamente dicho y entrega un pulso configurable y compatible con TTL que puede ser aceptado por la mayoría de los microcontroladores.

##### Características del sensor
>- Dimensiones: 3.2cm x 2.4cm x 1.8cm (approx)
>- Circuitos de control incluidos en el módulo
>- Tiempo de activación y sensibilidad ajustable
>- Voltaje de operación: 4.5 – 20 V
>- Corriente de operación: <60uA
>- Salida: Pulso lógico 3.3V
>- Tiempo de retardo: 5 – 200 Segundos (ajustable)
>- Distancia de detección: 3 – 7 Metros (ajustable)

#### Leds

Ambos Leds seran indicadores de estados:
>- El led verde indica que todo está OK.
>- El led rojo indica una intrusión.

Funcionamiento
-------------------
**PiGuardian** tiene como entradas la salida del sensor PIR. Si la entrada es *false*, la rp3 (Raspberry Pi 3) entenderá que no hay intrusión; mientras que una salida *true* del sensor, la rp3 alertará al usuario con un email, indicando que hubo una intrusión. El envio del correo se realizará mediante un script en python.

El siguiente diagrama ilustra el funcionamiento descrito:

<IMG https://github.com/galeanounam/diplo_embebidos_3/blob/proy1/proyectos/RGaleano/doc/diagrama_bloques.jpeg widht="480" height="270"/>
