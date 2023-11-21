/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por: M. en I. Valente Vázquez Velázquez
  Última modificación: 20-abril-2023
  https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

//Biblioteca para MQTT
#include "EspMQTTClient.h"

#define pinSensor 34

//Variables de configuración del objeto MQTT cliente
const char* ssid = "Clase_IoT";
const char* password = "0123456789";
const char* broker = "test.mosquitto.org";
const char* nameClient = "ESP32_Vazzvel"; //Cambiar nombre
const int port = 1883;

int count = 0; //contador

//Objeto cliente
EspMQTTClient client(ssid, password, broker, nameClient, port);

void setup() {
  Serial.begin(115200);
  pinMode(pinSensor, INPUT);
  
  if (!client.isConnected()){
    Serial.println("Conectado con el broker!");
  }
  else{
    Serial.println("No Conectado, revise su conexión");
  }
  delay(1000);  
}

//Función que se encarga de suscribirse a los tópicos
void onConnectionEstablished(){
  client.subscribe("ClaseIoT/Vazzvel/SubA", [](const String & payloadA) {
    Serial.print("El tópico en subA es: ");
    Serial.println(payloadA);
  });

  client.subscribe("ClaseIoT/Vazzvel/SubB", [](const String & payloadB) {
    Serial.print("El tópico en subB es: ");
    Serial.println(payloadB);
  });
}

void loop() {
  client.loop(); //Manejador del cliente MQTT
  count++;
  
  if(count%5 == 0){ //Si el residuo de count/5 es igual a cero (módulo)
    int val = random(0, 25); //valor aleatorio entre 0 y 25
    client.publish("ClaseIoT/Vazzvel/PubA", String(val)); //Publica la variable var en tipo String
    Serial.print("El mensaje enviado al tópico PubA, es: ");
    Serial.println(val);

    int sensor = analogRead(pinSensor);
    client.publish("ClaseIoT/Vazzvel/PubB", String(sensor)); //Publica la variable var en tipo String
    Serial.print("El mensaje enviado al tópico PubB, es: ");
    Serial.println(sensor);
  }
  delay(200);
} 
