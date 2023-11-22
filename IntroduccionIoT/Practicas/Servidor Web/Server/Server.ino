/*
 * Implementación de CSS y HMTL por JohnKun136NVCP
 * Implementación de servidor y JS por Gansito21
*/

//Bibliotecas necesarias
#include "WiFi.h" //Wifi para conexión entre Wifi
#include "ESPAsyncWebServer.h" //Servidor para el esp32
#include "SPIFFS.h" //Subir archivos a la memoria del esp32
#include "Credentials.h" //Guardar contraseñas tipo archivo



//Sensores
#define poten 35 //Potenciometro
#define ldr 34 //Fotoresistencia

//LED PARA PWM
#define ledPin 14
String sliderValue = "0";
const int freq = 1000;
const int ledChannel = 0;
const int resolution = 8;
const char* PARAM_INPUT = "value";

//LEDS 1 - 4
#define ledBlue 26 // led 4
#define ledRed 25 //led 3
#define ledGreen 33 //led 5
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";
const char* PARAM_INPUT_3 = "state";


//Objeto para servidor
AsyncWebServer server(80);

//Conexion Wifi por STA
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

// Funcion para convertir de float to String al voltaje
String Potenciometro(){
  float voltaje = (analogRead(poten) / 4095.0) * 3.3;
  Serial.println(voltaje);
  return String(voltaje);
}
// Convertimos a cadena la lectura del ldr (voltaje)
String LDR(){
  float volt_ldr = (analogRead(ldr)/4095.0)*3.3;
  Serial.println(volt_ldr);
  return String(volt_ldr);
}

//Asignamos la cadena a la variable processor para caa uno de los sensores
String processor(const String& var){
  //Caso potenciometro
  if (var == "VOLTAJE"){
    return Potenciometro();
    }
    //Caso fotodiodo
  else if (var == "FOTODIODO"){
    return LDR();
    }
    //caso PWM
  else if (var == "SLIDERVALUE"){
    return sliderValue;
    }
    //Caso botones leds 3,4 5
   else if (var == "BUTTONPLACEHOLDER"){
      String buttons = "";
      buttons += "<h4>LED 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"25\" " + outputState(ledBlue) + "><span class=\"slider1\"></span></label>";
      buttons += "<h4>LED 3</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"26\" " + outputState(ledRed) + "><span class=\"slider2\"></span></label>";
      buttons += "<h4>LED 5</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"33\" " + outputState(ledGreen) + "><span class=\"slider3\"></span></label>";
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
  pinMode(poten, INPUT);
  pinMode(ldr, INPUT);
  pinMode(ledPin, OUTPUT);

  //botones 3, 4 y 5
  pinMode(ledBlue, OUTPUT);
  digitalWrite(ledBlue, LOW);
  
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledRed, LOW);
  
  pinMode(ledGreen, OUTPUT);
  digitalWrite(ledGreen, LOW);

  //Activar PWM--------------------------------
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
  ledcWrite(ledChannel, sliderValue.toInt());  

  //Confirmar archivos subidos
  //a la memoria flash-------------------------
  if (!SPIFFS.begin(true)) {
    Serial.println("Error al leer SPIFFS");
    return;
  }

  // Start server
  server.begin();

  //GET HTML-----------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  //Archivo CSS--------------------------------
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  //Archivo JS--------------------------------
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/script.js", "text/js");
  });
  //Enviar dato potenciometro-------------------------
  server.on("/poten", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", Potenciometro().c_str());
  });
  server.on("/poten", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", Potenciometro().c_str());
  });
    //Enviar dato fotodiodo-------------------------
  server.on("/fotodiodo", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", LDR().c_str());
  });
  server.on("/fotodiodo", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", LDR().c_str());
  });
  //PWM
    //Enviar solicitud a <ESP_IP>/slider?value=<inputMessage>
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    //Obtener valor de <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      ledcWrite(ledChannel, sliderValue.toInt());
    }
    else {
      inputMessage = "Mensaje no enviado";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

   // Botones leds 3,4 y 5
     //Enviar solicitud a <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputM1;
    String inputM2;
    String inputM3;
    //Obtener valor de <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2) && request->hasParam(PARAM_INPUT_3)) {
      inputM1 = request->getParam(PARAM_INPUT_1)->value();
      inputM2 = request->getParam(PARAM_INPUT_2)->value();
      inputM3 = request->getParam(PARAM_INPUT_3)->value();
      digitalWrite(inputM1.toInt(),inputM2.toInt());
      digitalWrite(inputM2.toInt(),inputM3.toInt());
     

    }
    else {
      inputM1 = "Mensaje no enviado";
      inputM2 = "Mensaje no enviado";
      inputM3 = "Mensaje no enviado";
    }
    Serial.print("GPIO: ");
    Serial.print(inputM1);
    Serial.print(" - estado: ");
    Serial.println(inputM2);
    Serial.print(" - estado: ");
    Serial.println(inputM3);
    request->send(200, "text/plain", "OK");
  });

  
  //Función para error 404
  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404, "text/plain", "Error 404");
  });
  
}

void loop() {

}
