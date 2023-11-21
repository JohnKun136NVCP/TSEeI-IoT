/*
 *Universidad Nacional Autónoma de México
 *Facultad de Ciencias
 *Licenciatura en Ciencias de la Computación
 *Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas
 *
 *Escrito por: M. en I. Valente Vázquez Velázquez
 *Última modificación: 1-enero-2023
 *https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
 *
 *¡¡¡Recuerde que en este ejemplo NO hay conexión a internet!!!
*/

//Biblioteca WiFi
#include "WiFi.h"

const char* ssidESP32 = "WiFi_ESP32_Vazzvel"; //Nombre de red del ESP32
const char* passwordESP32 = "nohayinternet"; //Contraseña de red del ESP32
int channelESP32 = 1; //Número de canal de WiFi 1-13
int ssid_hidden = 0; //Nombre de red oculto, 0 = visible, 1 = oculto
int max_connection = 2; //Número de clientes conectados 1-4


void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP); //Modo Access Point
  delay(100);
  WiFi.softAP(ssidESP32, passwordESP32, channelESP32, ssid_hidden, max_connection);
  Serial.println("ESP32 en modo Access Point establecido");
}

void loop() {
  Serial.print("Dispositivos conectados: ");
  Serial.println(WiFi.softAPgetStationNum());
  delay(1000);
}
