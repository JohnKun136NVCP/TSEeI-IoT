/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por: M. en I. Valente Vázquez Velázquez
  Última modificación: 20-abril-2023
  https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

//Bibliotecas----------------------------------
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

//Credenciales Red-----------------------------
const char* ssid = "Clase_IoT";
const char* password = "0123456789";

//LEDs GPIO-------------------------------------
#define ledPinBlue 25
#define ledPinRed 26
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

//Objeto AsyncWebServer, puerto 80-------------
AsyncWebServer server(80);

//Conexión WiFi--------------------------------
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  delay(2000);
}

//Acciones a realizar--------------------------
String processor(const String& var) {
  //Serial.println(var);
  if (var == "BUTTONPLACEHOLDER") {
    String buttons = "";
    buttons += "<h4>LED 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"25\" " + outputState(ledPinBlue) + "><span class=\"slider1\"></span></label>";
    buttons += "<h4>LED 3</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"26\" " + outputState(ledPinRed) + "><span class=\"slider2\"></span></label>";
    return buttons;
  }
  return String();
}

//Estado del led-------------------------------
String outputState(int output) {
  if (digitalRead(output)) {
    return "checked";
  }
  else {
    return "";
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  //Leds---------------------------------------
  pinMode(ledPinBlue, OUTPUT);
  digitalWrite(ledPinBlue, LOW);
  pinMode(ledPinRed, OUTPUT);
  digitalWrite(ledPinRed, LOW);

  //Comenzar el servidor-----------------------
  server.begin();

  //Revisar archivos subidos a la memoria flash---
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  //Ruta raíz del archivo HTML-----------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Archivo CSS--------------------------------
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  //Enviar solicitud a <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage1;
    String inputMessage2;
    //Obtener valor de <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "Mensaje no enviado";
      inputMessage2 = "Mensaje no enviado";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - estado: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });

  //Función para error 404
  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404, "text/plain", "Error 404");
  });
}

void loop() {

}
