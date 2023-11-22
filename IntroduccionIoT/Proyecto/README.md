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


## Cybersecurity

In the rapidly evolving digital age, the importance of cybersecurity cannot be overstated. As technology permeates every aspect of our lives, from personal communications to critical infrastructure, the need to protect sensitive information from malicious actors becomes increasingly paramount. This essay explores the crucial role of cybersecurity in preserving the integrity, confidentiality, and availability of digital assets, and highlights its significance in the face of emerging cyber threats.

Firstly, cybersecurity serves as a bulwark against unauthorized access and data breaches. The digital realm is teeming with cybercriminals who seek to exploit vulnerabilities for financial gain, industrial espionage, or even political motives. Robust cybersecurity measures, including firewalls, encryption, and access controls, act as a formidable defense, preventing unauthorized individuals from infiltrating systems and pilfering sensitive information. This protection is not only essential for individuals safeguarding personal data but also for organizations entrusted with confidential business and customer information.

Secondly, cybersecurity plays a pivotal role in maintaining public trust. With the increasing reliance on digital platforms for communication, commerce, and information sharing, individuals and businesses need assurance that their data is secure. Breaches of cybersecurity erode this trust, leading to reputational damage and financial consequences. By investing in cybersecurity, organizations demonstrate their commitment to protecting the interests and privacy of their stakeholders, thereby fostering trust in the digital ecosystem.

Moreover, the importance of cybersecurity extends beyond the realm of individual and corporate interests to encompass critical infrastructure. Power grids, transportation systems, healthcare facilities, and financial institutions are interconnected and reliant on digital technologies. A breach in the cybersecurity of these critical systems can have far-reaching consequences, ranging from disruptions in essential services to potential national security threats. Thus, robust cybersecurity measures are imperative to safeguarding the resilience and functionality of the broader infrastructure that underpins modern society.

Furthermore, as cyber threats continue to evolve and become more sophisticated, the role of cybersecurity becomes dynamic. Continuous adaptation and innovation in cybersecurity strategies are essential to stay one step ahead of cyber adversaries. This requires collaboration between governments, businesses, and individuals to share threat intelligence, best practices, and invest in research and development to create resilient cybersecurity frameworks.

## IDS (Intrusion Detection Systems)

Technological advances in the digital age have led to an exponential increase in the amount of information and data stored online. As organizations and individuals increasingly rely on the connectivity and accessibility of their systems, the threat of malicious intrusions and cyber attacks also increases. In this context, Intrusion Detection Systems (IDS) emerge as crucial elements in IT security defense.

An IDS is a tool designed to monitor and analyze network traffic for suspicious activity or anomalous behavior that may indicate an intrusion attempt or security breach. Its importance lies in several fundamental aspects that contribute to the integrity, confidentiality and availability of information systems.

1. First, IDSs play a key role in early identification of potential threats. By analyzing traffic patterns and anomalous behavior, these systems can detect intrusions in their early stages, enabling a fast and efficient response to mitigate risks before they cause significant damage.  This is crucial in a digital environment where speed of detection and response is essential to minimize the impact of attacks.

2.  IDSs are essential for data collection and forensic reporting. By recording and analyzing security events, these systems provide valuable information that can be used to understand the nature of attacks, identify recurring patterns and strengthen existing security measures. This retrospective knowledge is essential to improving an organization's long-term security posture.


3. Another crucial aspect of IDSs is their ability to reduce the workload of security teams. With the ever-increasing volume of data and threats, security analysts face significant challenges. IDSs automate event monitoring and analysis, allowing security professionals to focus on more advanced investigations and strategic decision making. This not only improves operational efficiency, but also increases responsiveness to more sophisticated threats.

4. Finally, Intrusion Detection Systems play a crucial role in protecting information systems in an increasingly interconnected digital world. Their ability to identify early threats, collect forensic data and alleviate the workload of security teams makes them indispensable tools for ensuring information integrity and security. In an environment where cybersecurity is paramount, effective implementation of IDSs is an essential measure for safeguarding digital assets and preserving trust in the information age.

## Wireshark

Wireshark is a network packet analysis tool that deploys a variety of applications in the communications field. Its usefulness ranges from troubleshooting communications networks, performing security audits, to software and protocol development, in addition to its role as an educational resource. This analyzer, which incorporates all the standard features of a protocol analyzer, is used in a comprehensive and focused way to capture information passing through a connection.

Wireshark, which is freely available and open source, stands out as a versatile tool for diagnosing network problems, conducting security audits, and gaining a deeper understanding of computer networks in general. It offers the ability to examine data from both an active network and from capture files stored on disk. Captured information can be analyzed through packet-specific details and summaries. Among its features, Wireshark includes a comprehensive language for filtering the content to be viewed and the ability to display the reconstructed flow of a TCP session.

Wireshark, being free software, is compatible with a wide range of operating systems, including Unix and its variants such as Linux, Solaris, FreeBSD, NetBSD, OpenBSD, Android, and Mac OS X, as well as Microsoft Windows environments.

## Wireshark and ESP32

Wireshark and ESP32 are two distinct technologies that can be integrated to enhance network monitoring and debugging capabilities in IoT (Internet of Things) applications. Wireshark is a network protocol analyzer, while ESP32 is a versatile microcontroller commonly used in IoT projects. The integration of these technologies allows for detailed analysis and troubleshooting of network communication in ESP32-based IoT devices. By leveraging Wireshark's packet capturing and analysis capabilities, developers can monitor and inspect the network traffic generated by ESP32 devices. This integration is particularly valuable during the development and debugging phases, as it provides insights into how the ESP32 communicates over the network, helping identify issues such as packet loss, latency, or unexpected behavior.


## Install components for ESP32 (IDE)

Step 1. Connecting the board to the computer
To connect your ESP32 board to the computer you use the USB cable. Once connected, the power LED will turn on indicating that the board is properly powered. If the LED does not light up, it is possible that the cable or the USB port is damaged.

Step 2. Selecting the ESP32 board to use
Now it is necessary to indicate to the Arduino IDE software the board to use. For this it is necessary to go to *Tools > Board* and select the corresponding option. In this case *Heltec ESP32 Arduino > Wireless Stick Lite*

Step 3. Select the port
Although in many cases the IDE itself determines the port used by the board, in other cases it is necessary to specify it. To do this, go to *Tools > Port*, then select the port corresponding to the board. In Linux it starts with tty and is usually followed by the words ACM or USB with an order number.

Step 4. Upload the program to the ESP32
All that remains is to load the implemented code to the ESP32. To check that the engraving process is correct, a good option is to use the Blink example, since it does not require any external component.

Once the code is ready, it is necessary to click on the check button of the IDE to verify that there is no error in it. Then, by clicking on the load button, the code is written to the ESP32. Once the code is finished loading the LED on the board will start blinking.

## Install components for Pyton Requiremente

To install Panda:
Use the command 

*py -m pip --version*

To see if you have the *PIP package manager* installed.
Install *NumPy* with the command 

*py -m pip install numpy*

Install *Pandas* with the command

 *py -m pip install pandas*.

To add the *PySerial library*:
*Phyton -m pip intall PySerial*

## Install Wireshark (Linux)

Both the command line and Qt version of Wireshark are available to Arch Linux users in the "Community" software repository. To install the software on your Arch PC, you must manually enable "Community", as not all distributions have it enabled by default.

To enable "Community", root your terminal with 

*su -*

Once the root is obtained, open the */etc/pacman.conf* file in the Nano text editor 

*nano -w /etc/pacman.conf*

Scroll through the text editor until you find "Community" and delete the # symbol in front of it, as well as the lines directly below it. After that, save the modifications by pressing 

*Ctrl + O* , and output with *Ctrl + X* . 

Re-synchronize Pacman, so that you can add the Community packages to the program database on your PC 

*pacman -Syy*

Finally, install the latest version of Wireshark 

*pacman -S wireshark-qt*

## Project description 

Within the framework of this project, we have developed an Intrusion Detection System (IDS) in which the ESP32 microcontroller plays a central role. Within this architecture, we have implemented a configuration composed of three light emitting diodes (LEDs), each designed with specific functionalities. The first LED, green in color, indicates the absence of threats; the second, yellow in hue, warns of possible danger; and the last, red in color, acts as a danger alarm, simultaneously activating a buzzer for sound alerts. In parallel, when the functionality associated with the red LED is activated, it generates a notification sent to the user through the Telegram messaging platform, as well as an alert message sent to the email of the same user registered in the GMAIL account.

## Project operation

The project operates as follows: it uses the main.sh program, which is a program developed in the Bash language that initializes the main program, being exclusively available for Linux-based operating systems. Its execution requires administrator privileges.

The program offers five options for package installation, specifically designed for distributions such as Ubuntu, Fedora and Arch Linux. For the purpose of obtaining the IP address of the ESP32 through the serial port, the program will allow the selection of the corresponding serial port. The third option is for starting the Intrusion Detection System (IDS). The user can choose to start the IDS with the default IP address configuration or add a specific path to it. This phase displays the available network interfaces and starts the traffic analysis, thus establishing the conditions for the creation of a secure and efficient environment.

## Acknowledgments

For their support in the realization of this project and the material used in the project we would like to thank
 - Ma. Alejandro Pompa García
 - David Elias González García
 - Alejandro Cortes Mora

## Bibliography

1. Ashoor, A. S., & Gore, S. (2011). Importance of intrusion detection system (IDS). International 

2. Journal of Scientific and Engineering Research, 2(1), 1-4.

3. ESP32 Wi-Fi & Bluetooth SOC | Espressif Systems. (s. f.). https://www.espressif.com/en/products/socs/esp32

4. Nonato, N. (2022). Data acquisition system for fine surface process monitoring (Doctoral dissertation).

5. Tarter, A. (2017). Importance of cyber security. Community Policing-A European Perspective: Strategies, Best Practices and Guidelines, 213-230.

6. UCM-Proyecto de Innovación Software Libre para Ciencias e Ingenierías. (s. f.). https://www.ucm.es/pimcd2014-free-software/wireshark

In charge of the project: Physics student Juan Angeles Hernández and Biology student Xianya Itzel Díaz de León Márquez. for the subject Internet of Things, taught by M. Ing. Valente Vázquez Velázquez.
