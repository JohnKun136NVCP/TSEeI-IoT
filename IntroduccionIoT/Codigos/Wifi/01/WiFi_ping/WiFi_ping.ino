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

//Bibliotecas
#include "WiFi.h"
#include <ESP32Ping.h> //https://github.com/marian-craciunescu/ESP32Ping

//Variables
int number = 4;

//Conexión a la red WiFi
void Setup_WiFi(const char* ssid, const char* password) {
  WiFi.mode(WIFI_STA); //Modo de WiFi tipo "station" (dispositivo)
  WiFi.begin(ssid, password); //Credenciales
  Serial.print("Conectado al WiFi... ");
  //Mientras se conecta escribir puntos
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("\n¡Conexión establecida!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP()); //Se obtiene la dirección IP del ESP32
  delay(2000);
}

void setup() {
  Serial.begin(115200);
  Setup_WiFi("Clase_IoT", "0123456789");
}

void loop() {
  Serial.print("\nEnviando ");
  Serial.print(number);
  Serial.println(" pings a Google...");
  
  //Envía un número prederteminados de pings
  bool success = Ping.ping("www.google.com", number);
  //Si no hay ping se envía un error
  if (!success) {
    Serial.println("Error, ping no enviado");
    return;
  }
  
  //Tiempo promedio de los pings enviados
  Serial.println("¡Pings enviados!");
  float time_ping = Ping.averageTime();
  Serial.print("Tiempo promedio: ");
  Serial.print(time_ping);
  Serial.println(" ms");
}
