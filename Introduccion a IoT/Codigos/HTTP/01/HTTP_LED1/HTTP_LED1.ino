/*
 *Universidad Nacional Autónoma de México
 *Facultad de Ciencias
 *Licenciatura en Ciencias de la Computación
 *Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas
 *
 *Escrito por: M. en I. Valente Vázquez Velázquez
 *Última modificación: 14-abril-2023
 *https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

//Bibliotecas----------------------------------
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

//Credenciales Red-----------------------------
const char* ssid = "Clase_IoT";
const char* password = "0123456789";

//LED GPIO-------------------------------------
const int ledPin = 25;
String ledState;

//Objeto AsyncWebServer, puerto 80-------------
AsyncWebServer server(80);

//Código HTML----------------------------------
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Clase IoT</title> 
    </head>
  <body>
    <h1>Clase IoT</h1>
  <h2>Control de un LED</h2>
  <p>Estado LED: <strong> %STATE%</strong></p>
  <p><a href="/on"><button>ON</button></a></p>
  <p><a href="/off"><button>OFF</button></a></p>
  </body>
</html>)rawliteral";

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
String processor(const String& var){
  if(var == "STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print("Estado LED: ");
    Serial.println(ledState);
    return ledState;
  }
  return String();
}
 
void setup(){
  Serial.begin(115200);
  setup_wifi();
  pinMode(ledPin, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(14, LOW);

  //Comenzar el servidor-----------------------
  server.begin();

  //GET HTML-----------------------------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", index_html);
  }); 

  //STATUS LED------------------------------------
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);
    request->send_P(200, "text/html", index_html, processor);
  });

  //Función para error 404
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Error 404");
  });
}
 
void loop(){
  
}
