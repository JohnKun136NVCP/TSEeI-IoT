<p align="center"> 
<img src="img/LogoSecurity.png" width="400px "height="400px" align="center"> 
</p>

## Semester project
# Intrusion detection system with ESP32
The Esp32 is a feature-rich MCU with integrated Wi-Fi and Bluetooth connectivity for a wide range of applications:

1. [Robust desing](#Robust-desing)

ESP32 is able to operate reliably in industrial environments, with operating temperatures ranging from -40 °C to +125 °C. Powered by advanced calibration circuitry, ESP32 can dynamically eliminate external circuit imperfections and adapt to changes in external conditions.

2. [Ultra low power consumption](#Ultra-low-powe-consumptiom)

Designed for mobile devices, wearable electronics and IoT applications, ESP32 achieves ultra-low power consumption with a combination of several types of proprietary software. ESP32 also includes state-of-the-art features such as fine-grained clock synchronization, multiple power modes and dynamic power scaling.

3. [High level of integration](#High-level-of-integration)

ESP32 is highly integrated with built-in antenna switches, RF balun, power amplifier, low noise receive amplifier, filters and power management modules. ESP32 adds invaluable functionality and versatility to your applications with minimal printed circuit board (PCB) requirements.

4. [Hybrid WiFi and Bluetooth chip](#Hybrid-WiFi-and-Bluetooth-chip)

ESP32 can operate as a complete stand-alone system or as a slave device to a host MCU, reducing the communications stack overhead on the main application processor. ESP32 can interface with other systems to provide Wi-Fi and Bluetooth functionality through its SPI/SDIO or I2C/UART interfaces.

## IDS (Intrusion Detection Systems)

Technological advances in the digital age have led to an exponential increase in the amount of information and data stored online. As organizations and individuals increasingly rely on the connectivity and accessibility of their systems, the threat of malicious intrusions and cyber attacks also increases. In this context, Intrusion Detection Systems (IDS) emerge as crucial elements in IT security defense.

An IDS is a tool designed to monitor and analyze network traffic for suspicious activity or anomalous behavior that may indicate an intrusion attempt or security breach. Its importance lies in several fundamental aspects that contribute to the integrity, confidentiality and availability of information systems.

1. First, IDSs play a key role in early identification of potential threats. By analyzing traffic patterns and anomalous behavior, these systems can detect intrusions in their early stages, enabling a fast and efficient response to mitigate risks before they cause significant damage.  This is crucial in a digital environment where speed of detection and response is essential to minimize the impact of attacks.

2.  IDSs are essential for data collection and forensic reporting. By recording and analyzing security events, these systems provide valuable information that can be used to understand the nature of attacks, identify recurring patterns and strengthen existing security measures. This retrospective knowledge is essential to improving an organization's long-term security posture.


3. Another crucial aspect of IDSs is their ability to reduce the workload of security teams. With the ever-increasing volume of data and threats, security analysts face significant challenges. IDSs automate event monitoring and analysis, allowing security professionals to focus on more advanced investigations and strategic decision making. This not only improves operational efficiency, but also increases responsiveness to more sophisticated threats.

4. Finally, Intrusion Detection Systems play a crucial role in protecting information systems in an increasingly interconnected digital world. Their ability to identify early threats, collect forensic data and alleviate the workload of security teams makes them indispensable tools for ensuring information integrity and security. In an environment where cybersecurity is paramount, effective implementation of IDSs is an essential measure for safeguarding digital assets and preserving trust in the information age.

## Project description 

Within the framework of this project, we have developed an Intrusion Detection System (IDS) in which the ESP32 microcontroller plays a central role. Within this architecture, we have implemented a configuration composed of three light emitting diodes (LEDs), each designed with specific functionalities. The first LED, green in color, indicates the absence of threats; the second, yellow in hue, warns of possible danger; and the last, red in color, acts as a danger alarm, simultaneously activating a buzzer for sound alerts. In parallel, when the functionality associated with the red LED is activated, it generates a notification sent to the user through the Telegram messaging platform, as well as an alert message sent to the email of the same user registered in the GMAIL account.

## Acknowledgments

For their support in the realization of this project and the material used in the project we would like to thank
 - Ma. Alejandro Pompa García
 - David Elias González García
 - Alejandro Cortes Mora

## Bibliografía

1. Ashoor, A. S., & Gore, S. (2011). Importance of intrusion detection system (IDS). International 

2. Journal of Scientific and Engineering Research, 2(1), 1-4.

3. ESP32 Wi-Fi & Bluetooth SOC | Espressif Systems. (s. f.). https://www.espressif.com/en/products/socs/esp32

In charge of the project: Physics student Juan Ángeles Hernández and Biology student Xianya Itzel Díaz de León Márquez. for the subject Internet of Things, taught by M. Ing. Valente Vázquez Velázquez.
