/*
 *Universidad Nacional Autónoma de México
 *Facultad de Ciencias
 *Licenciatura en Ciencias de la Computación
 *Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas
 *
 *Escrito por: M. en I. Valente Vázquez Velázquez
 *Última modificación: 1-enero-2023
 *https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

//Incluir librería de bluetooth
#include "BluetoothSerial.h"

//Condición para habilitar el bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial BT; // Objeto Bluetooth

//Variable con el nombre del cliente (dispositivo a conectarse - esclavo)
String clientName = "ESP32_Vazzvel_Slave"; 
bool connected;

void setup() {
  Serial.begin(115200); //Inicializar la comunicación serial
  BT.begin("ESP32_Vazzvel_Master", true); //Nombre de su dispositivo Bluetooth y en modo maestro
  Serial.println("El dispositivo Bluetooth está en modo maestro.\n Conectando con el anfitrión ...");

  connected = BT.connect(clientName); //Inicializar la conexión vía bluetooth
  if (connected) {
    Serial.println("¡Conectado exitosamente!");
  } else {
    while (!BT.connected(10000)) {
      Serial.println("No se pudo conectar. \n Asegúrese de que el dispositivo remoto esté disponible y dentro del alcance, \n luego reinicie la aplicación.");
    }
  }
}
void loop() {
  BT.write(49); // Envía 1 en ASCII
  delay(200);
  BT.write(48); // Envía 0 en ASCII
  delay(200);
}
