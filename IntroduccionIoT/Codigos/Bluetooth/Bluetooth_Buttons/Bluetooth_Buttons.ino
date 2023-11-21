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

//Definir pines
#define SW1 15 //Pull Down
#define SW2 4 //Pull Up

BluetoothSerial BT; // Objeto Bluetooth

String clientName = "ESP32_Vazzvel_Slave"; //Variable con el nombre del cliente (dispositivo a conectarse)
bool connected; //Variable de estado

//Variables para mejorar le funcionamiento del botón
long timeCounter1 = 0;
long timeCounter2 = 0;
int timeThreshold = 250;

void setup() {
  Serial.begin(115200); //Inicializar la comunicación serial
  pinMode(SW1, INPUT); //Pin de entrada
  pinMode(SW2, INPUT); //Pin de entrada

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
  if (digitalRead(SW1) == 1) {
    ledOn();
  }
  if (digitalRead(SW2) == 0) {
    ledOff();
  }
}

//Funciones
void ledOn() {
  if (millis() > timeCounter1 + timeThreshold) {
    BT.write(49); // Envía 1 en ASCII
    Serial.println("Led encendido");
    timeCounter1 = millis();
  }
}

void ledOff() {
  if (millis() > timeCounter2 + timeThreshold) {
    BT.write(48); // Envía 0 en ASCII
    Serial.println("Led apagado");
    timeCounter2 = millis();
  }
}
