/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por: M. en I. Valente Vázquez Velázquez
  Última modificación: 23-octubre-2023

  https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

//----------Bibliotecas
#include <SPIFFS.h>           //SPIFFS
#include <WiFiClientSecure.h> //Conexión al WiFi, SSL
#include <PubSubClient.h>     //MQTT
#include <ArduinoJson.h>      //Dato tipo Json
#include <WiFi.h>             //Conexión al WiFi
#include <DHT.h>              //Sensor de temperatura y humedad

//----------Definiciones de pines y palabras clave
#define PinLED 25             //Pin de LED
#define DHTPIN 32             //Pin digital de DHT
#define DHTTYPE DHT11         //Tipo de sensor DHT
#define THINGNAME "Vazzvel_ESP32"   //Nombre del dispositivo

//----------Tópicos de AWS
#define AWS_IOT_PUBLISH_TOPIC   "ClaseIoT/Vazzvel/Sensor"    //Tópico de publicación
#define AWS_IOT_SUBSCRIBE_TOPIC "ClaseIoT/Vazzvel/Leds"       //Tópico de suscripción

//---------Variables de conexión
const char WIFI_SSID[] = "Clase_IoT";         //Nombre de red
const char WIFI_PASSWORD[] = "0123456789";         //Contraseña de red
const char AWS_IOT_ENDPOINT[] = "amazonaws.com"; //Broker

//---------Variables para archivos de cifrados AWS
String AWS_CERT_CA;           //Variable para certificado de raíz tipo String
String AWS_CERT_CRT;          //Variable para certificado String
String AWS_CERT_PRIVATE;      //Variable para llave privada tipo String
char* _AWS_CERT_CA;           //Apuntador para certificado de raíz tipo Char
char* _AWS_CERT_CRT;          //Apuntador para certificado Char
char* _AWS_CERT_PRIVATE;      //Apuntador para llave privada tipo Char

//---------Variables globales
float h;                      //Humedad
float t;                      //Temperatura
long ti = millis();           //Tiempo de lectura del sensor

//---------Objetos del sensor, WiFi SSL y MQTT
DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);


void FilesSPIFFS() {
  //---------Leer archivos subidos a la memoria flash
  if (!SPIFFS.begin(true)) {
    Serial.println("Error al leer SPIFFS");
    return;
  }

  //---------Abrir e imprimir Root CA
  File file2 = SPIFFS.open("/AmazonRootCA1.pem", "r");
  if (!file2) {
    Serial.println("Error al abrir el archivo Root");
    return;
  }
  while (file2.available()) {
    AWS_CERT_CA = file2.readString();
  }

  //---------Abrir e imprimir Certificate
  File file4 = SPIFFS.open("/certificate.pem.crt", "r");
  if (!file4) {
    Serial.println("Error al abrir el archivo Certificate");
    return;
  }
  while (file4.available()) {
    AWS_CERT_CRT = file4.readString();
  }

  //---------Abrir e imprimir Privatekey
  File file6 = SPIFFS.open("/private.pem.key", "r");
  if (!file6) {
    Serial.println("Error al abrir el archivo Privatekey");
    return;
  }
  while (file6.available()) {
    AWS_CERT_PRIVATE = file6.readString();
  }

  //---------Punteros
  _AWS_CERT_CA = (char *)malloc(sizeof(char) * (AWS_CERT_CA.length() + 1));
  strcpy(_AWS_CERT_CA, AWS_CERT_CA.c_str());
  _AWS_CERT_CRT = (char *)malloc(sizeof(char) * (AWS_CERT_CRT.length() + 1));
  strcpy(_AWS_CERT_CRT, AWS_CERT_CRT.c_str());
  _AWS_CERT_PRIVATE = (char *)malloc(sizeof(char) * (AWS_CERT_PRIVATE.length() + 1));
  strcpy(_AWS_CERT_PRIVATE, AWS_CERT_PRIVATE.c_str());

  Serial.println("===============================================");
  Serial.println("Certificates:");
  Serial.println();
  Serial.println("Root CA:");
  Serial.write(_AWS_CERT_CA);
  Serial.println("===============================================");
  Serial.println();
  Serial.println("Cert:");
  Serial.write(_AWS_CERT_CRT);
  Serial.println("===============================================");
  Serial.println();
  Serial.println("privateKey:");
  Serial.write(_AWS_CERT_PRIVATE);
  Serial.println("===============================================");
}

void connectAWS()
{
  WiFi.mode(WIFI_STA);                      //Tipo de conexión WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);     //Credenciales WiFi
  Serial.println("Conectando al Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED)     //Imprime puntos mientras se conecta
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" ");

  //---------Credenciales AWS
  net.setCACert(_AWS_CERT_CA);
  net.setCertificate(_AWS_CERT_CRT);
  net.setPrivateKey(_AWS_CERT_PRIVATE);

  //---------Conexión vía MQTT
  client.setServer(AWS_IOT_ENDPOINT, 8883);

  //---------Manejador del cliente para las suscripciones
  client.setCallback(messageHandler);

  Serial.println("\nConectando a AWS IOT...");
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" ");

  if (!client.connected())
  {
    Serial.println("¡No ha sido posible conectarse a AWS IoT!");
    return;
  }

  //---------Tópico de suscripción
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC, 1); //(Topic, QoS)
  Serial.println("¡Conectado establecida con AWS IoT!");
}

//Función de publicar mensaje vía MQTT
void publishMessage()
{
  StaticJsonDocument<200> doc;    //Declarar variable "doc" tipo Json
  doc["humedad"] = h;            //humedad tipo Json
  doc["temperatura"] = t;         //temperatura tipo Json
  char jsonBuffer[512];           //Arreglo de caracteres de 512 bytes
  serializeJson(doc, jsonBuffer); //Empaquetar variable
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer); //Publicar dato

  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%  Temperatura: ");
  Serial.print(t);
  Serial.println("°C ");
}

//Función de suscripción vía MQTT
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  StaticJsonDocument<200> doc;          //Declarar variable "doc" en tipo Json
  deserializeJson(doc, payload);        //Desempaquetar el mensaje
  const char* message = doc["message"]; //Guardar la carga en la variable mensaje
  Serial.println(message);

  //Si el mensaje es "1" se enciende el LED, si es "0" se apaga
  if (*message == '1') {
    digitalWrite(PinLED, HIGH);
    Serial.println("Led encendido");
  }
  else if (*message == '0') {
    digitalWrite(PinLED, LOW);
    Serial.println("Led apagado");
  }
  else {
    Serial.println("Dato no válido");
  }
}

void setup() {
  Serial.begin(115200);
//  Serial.setDebugOutput(true);
  dht.begin();
  pinMode(PinLED, OUTPUT);
  FilesSPIFFS();
  connectAWS();
}

void loop() {
  client.loop();

  //Cada 5 segundos se publica la temperatura y humedad
  if (millis() - ti >= 5000)
  {
    h = dht.readHumidity();
    t = dht.readTemperature();
    if (isnan(h) || isnan(t) )  // Revisa el estado del sensor DHT
    {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    publishMessage(); //Publico el mensaje
    ti = millis();
  }
}
