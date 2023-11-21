
<p align="center">
 <img src="img/LogoSecurity.png" width="120px" height="120px" align="center"
</p>


## Proyecto semestral IoT

# Sistema de detección de intrusiones con ESP32
El Esp32 es una MCU rica en funciones con Wi-Fi integrado y Conectividad Bluetooth para una amplia gama de aplicaciones. dentro de su documentación se destacan las características: 

1. [Diseño robusto](#Diseño-robusto)

ESP32 es capaz de funcionar de forma fiable en entornos industriales, con una temperatura de funcionamiento que oscila entre –40 °C y +125 °C. Alimentado por circuitos de calibración avanzados, ESP32 puede eliminar dinámicamente imperfecciones de circuitos externos y adaptarse a cambios en las condiciones externas.

2. [Consumo de energía ultra bajo](#consumo-de-energía-ultrabajo)

Diseñado para dispositivos móviles, electrónica portátil y aplicaciones de IoT, ESP32 logra un consumo de energía ultrabajo con una combinación de varios tipos de software propietario. ESP32 también incluye características de última generación, como sincronización de reloj de grano fino, varios modos de energía y escalado dinámico de energía.

3. [Alto nivel de integración](#Alto-nivel-de-integración)

ESP32 está altamente integrado con interruptores de antena incorporados, balun RF, amplificador de potencia, amplificador de recepción de bajo ruido, filtros y módulos de administración de energía. ESP32 agrega funcionalidad y versatilidad invaluables a sus aplicaciones con requisitos mínimos de placa de circuito impreso (PCB).

4. [Chip híbrido WiFi y Bluetooth](#chip-hibrido-wifi-y-bluetooth)

ESP32 puede funcionar como un sistema independiente completo o como un dispositivo esclavo de una MCU host, lo que reduce la sobrecarga de la pila de comunicaciones en el procesador de aplicaciones principal. ESP32 puede interactuar con otros sistemas para proporcionar funcionalidad Wi-Fi y Bluetooth a través de sus interfaces SPI/SDIO o I2C/UART.

## IDS (Sistemas de Detección de Intrusiones)

Los avances tecnológicos en la era digital han llevado a un aumento exponencial en la cantidad de información y datos almacenados en línea. A medida que las organizaciones y los individuos dependen cada vez más de la conectividad y la accesibilidad de sus sistemas, también aumenta la amenaza de intrusiones maliciosas y ataques cibernéticos. En este contexto, los Sistemas de Detección de Intrusiones (IDS) emergen como elementos cruciales en la defensa de la seguridad informática.

Un IDS es una herramienta diseñada para monitorear y analizar el tráfico de red en busca de actividades sospechosas o comportamientos anómalos que puedan indicar un intento de intrusión o violación de la seguridad. Su importancia radica en varios aspectos fundamentales que contribuyen a la integridad, confidencialidad y disponibilidad de los sistemas de información.


1. En primer lugar, los IDS desempeñan un papel clave en la identificación temprana de posibles amenazas. Al analizar patrones de tráfico y comportamientos anómalos, estos sistemas pueden detectar intrusiones en sus fases iniciales, permitiendo una respuesta rápida y eficiente para mitigar los riesgos antes de que causen daño significativo.  Esto es crucial en un entorno digital donde la velocidad de detección y respuesta es esencial para minimizar el impacto de los ataques.

2.  Los IDS son esenciales para la recopilación de datos y la generación de informes forenses. Al registrar y analizar eventos de seguridad, estos sistemas proporcionan información valiosa que puede ser utilizada para comprender la naturaleza de los ataques, identificar patrones recurrentes y fortalecer las medidas de seguridad existentes. Este conocimiento retrospectivo es esencial para mejorar la postura de seguridad de una organización a largo plazo.


3. Otro aspecto crucial de los IDS es su capacidad para reducir la carga de trabajo de los equipos de seguridad. Con el volumen cada vez mayor de datos y amenazas, los analistas de seguridad enfrentan desafíos significativos. Los IDS automatizan la monitorización y análisis de eventos, permitiendo a los profesionales de seguridad centrarse en investigaciones más avanzadas y en la toma de decisiones estratégicas. Esto no solo mejora la eficiencia operativa, sino que también aumenta la capacidad de respuesta ante amenazas más sofisticadas.

4. Por último, los Sistemas de Detección de Intrusiones desempeñan un papel crucial en la protección de los sistemas de información en un mundo digital cada vez más interconectado. Su capacidad para identificar amenazas tempranas, recopilar datos forenses y aliviar la carga de trabajo de los equipos de seguridad los convierte en herramientas indispensables para garantizar la integridad y seguridad de la información. En un entorno donde la ciberseguridad es fundamental, la implementación efectiva de IDS se presenta como una medida esencial para salvaguardar los activos digitales y preservar la confianza en la era de la información.

## Descripción del proyecto

En el marco de este proyecto, hemos desarrollado un Sistema de Detección de Intrusiones (IDS) en el cual el microcontrolador ESP32 desempeña un papel central. Dentro de esta arquitectura, hemos implementado una configuración compuesta por tres diodos emisores de luz (LEDs), cada uno diseñado con funcionalidades específicas. El primer LED, de color verde, indica la ausencia de amenazas; el segundo, de tonalidad amarilla, advierte sobre un posible peligro; y el último, de color rojo, actúa como una alarma de peligro, activando simultáneamente un dispositivo emisor de sonido (buzzer) para la emisión de alertas sonoras. En paralelo, al activarse la funcionalidad asociada al LED rojo, se genera una notificación enviada al usuario a través de la plataforma de mensajería Telegram, así como un mensaje de alerta enviado al correo electrónico del mismo usuario registrado en la cuenta de GMAIL.

<p align="center">
 <img src="img/" width="120px" height="120px" align="center"
</p>

## Agradecimientos

Por su apoyo en la realizacipon de este proyecto y el material utilizado en el mismo queremos agradecer a 
 - Ma. Alejandro Pompa García
 - David Elias González García
 - Alejandro Cortes Mora

## Bibliografía

1. Ashoor, A. S., & Gore, S. (2011). Importance of intrusion detection system (IDS). International 

2. Journal of Scientific and Engineering Research, 2(1), 1-4.


3. ESP32 Wi-Fi & Bluetooth SOC | Espressif Systems. (s. f.). https://www.espressif.com/en/products/socs/esp32



Encargados del proyecto: Est. de Física Juan Ángeles Hernández y Est. de Biología Xianya Itzel Díaz de León Márquez. para la materia Internet de las Cosas, impartida por el M. Ing. Valente Vázquez Velázquez

