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
#include <ESP32Ping.h> //https://github.com/marian-craciunescu/ESP32Ping

const char* ssid_STA = "PapimeIoT";
const char* password_STA = "P4p1m3_IoT";
const char* ssid_AP = "WiFi_ESP32_Vazzvel"; //Nombre de red del ESP32
const char* password_AP = "nohayinternet"; //Contraseña de red del ESP32
//int channelAP = 1; //Número de canal de WiFi 1-13
//int ssid_hidden = 0; //Nombre de red oculto, 0 = visible, 1 = oculto
//int max_connection = 2; //Número de clientes conectados 1-4
int number = 4;


void setup() {
  Serial.begin(115200);
  
  //Modo dual: Access Point y Station
  WiFi.mode(WIFI_AP_STA); 

  //Conexión modo AP
//  WiFi.softAP(ssid_AP, password_AP, channelAP, ssid_hidden, max_connection);
  WiFi.softAP(ssid_AP, password_AP);
  Serial.println("\nESP32 en modo Access Point establecido");
  Serial.print("Dirección IP del modo AP: ");
  Serial.println(WiFi.softAPIP());
  delay(100);

  //Conexión modo STA
  WiFi.begin(ssid_STA, password_STA);
  Serial.print("Conectado al WiFi... ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("\n¡Conexión establecida!");
  Serial.print("Dirección IP del modo STA: ");
  Serial.println(WiFi.localIP()); //Se obtiene la dirección IP del ESP32
  delay(1000);
  
}

void loop() {
  Serial.print("\nEnviando ");
  Serial.print(number);
  Serial.print(" pings a Google... ");
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
  delay(1000);

  Serial.print("\nDispositivos conectados: ");
  Serial.println(WiFi.softAPgetStationNum());
  delay(1000);
}
