/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por: M. en I. Valente Vázquez Velázquez
  Última modificación: 14-abril-2023
  https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

//Bibliotecas----------------------------------
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
/*
   Decargar las bibliotecas de:
   https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip}
   https://github.com/me-no-dev/AsyncTCP/archive/master.zip
*/

//Credenciales Red-----------------------------
const char* ssid = "Clase_IoT";
const char* password = "0123456789";

//Objeto AsyncWebServer, puerto 80-------------
AsyncWebServer server(80);

//Código HTML----------------------------------
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Clase IoT</title>
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }
      h2 { font-size: 4.0rem;
           color: #059e8a;
           }
      p { font-size: 2.5rem; }
    </style>  
    </head>
  <body>
    <h2>ESP32 IoT</h2>
    <p>Este es un ejemplo de texto en HTML con un poco de formato</p>
    <p>Tiene buena pinta</p>
    <p><a href="/pageA">Web A</a></p>
  </body>
</html>)rawliteral";

const char pageA[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Clase IoT</title>
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }
      h2 { font-size: 6.0rem;
           color: #030e8a;
           }
      p { font-size: 3rem; }
    </style> 
  </head>
  <body>
    <h2>Web A</h2>
    <p>Vamos bien?</p>
    <p>Alguna pregunta?</p>
    <p><a href="/">Index</a></p>
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

void setup() {
  Serial.begin(115200);
  setup_wifi();

  //Comenzar el servidor-----------------------
  server.begin();

  //GET HTML-----------------------------------
  /*
     Elementos de la función server.on:
      server.on(Ruta, Método, [](AsyncWebServerRequest *request){
        request->send(Status Code, tipo, mensaje);
      });
  */
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", index_html);
  });

  server.on("/pageA", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", pageA);
  });

  //Función para error 404
  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404, "text/plain", "Error 404");
  });
}

void loop() {

}
