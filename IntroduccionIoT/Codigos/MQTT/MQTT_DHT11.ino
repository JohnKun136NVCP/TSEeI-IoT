/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por: M. en I. Valente Vázquez Velázquez
  Última modificación: 20-abril-2023
  https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

//Bibliotecas
#include "EspMQTTClient.h"
#include "DHT.h"

//Definimos pines
#define pinLED 25
#define DHTPIN 32
#define DHTTYPE DHT11

//Variables de configuración del objeto MQTT cliente
const char* ssid = "Clase_IoT";
const char* password = "0123456789";
const char* broker = "test.mosquitto.org";
const char* nameClient = "ESP32_Vazzvel"; //Cambiar nombre
const int port = 1883;

//Tópicos
String T_LEDS = "ClaseIoT/Vazzvel/Leds";
String T_TEMP = "ClaseIoT/Vazzvel/DHT/Temp";
String T_HUME = "ClaseIoT/Vazzvel/DHT/Hume";

//Variables globales
long timeDHT = millis();

//Objeto cliente
DHT dht(DHTPIN, DHTTYPE);
EspMQTTClient client(ssid, password, broker, nameClient, port);


void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(pinLED, OUTPUT);

  if (!client.isConnected()) {
    Serial.println("Conectado con el broker!");
  }
  else {
    Serial.println("No Conectado, revise su conexión");
  }
  delay(5000);
}


void onConnectionEstablished() {
  //Prender y apagar LEDs
  client.subscribe(T_LEDS, [](const String & payload) {
    if (payload == "1") {
      digitalWrite(pinLED, HIGH);
      Serial.println("Led encendido");
    }
    else if (payload == "0") {
      digitalWrite(pinLED, LOW);
      Serial.println("Led apagado");
    }
    else {
      Serial.println("Dato no válido");
    }
  });
}

void loop() {
  client.loop();
  //Espero 2.5 s para leer el sensor y publicar los datos
  if (millis() - timeDHT >= 2500) { 
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    //Publica la humedad y temperatura
    client.publish(T_TEMP, String(t));
    client.publish(T_HUME, String(h));
    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.print(" %,  Temperatura: ");
    Serial.print(t);
    Serial.println(" °C");

    timeDHT = millis();
  }
}
