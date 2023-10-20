//Bibliotecas necesarias y otra para ocultar la informacion
#include"Credentials.h"
#include "EspMQTTClient.h"
#include "DHT.h"

//Pines
#define DHTPIN 32
#define DHTTYPE DHT11
#define pinPhoto 34 //Pin para la fotoresistencia
const int leds[5] = {14, 27, 26, 25, 33};


//Topicos
String ledsTopic = "ClaseIoT/Angeles/Led";
String dhtTopic =  "ClaseIoT/Angeles/DHT/Humtem";
String dhtVolt = "ClaseIoT/Angeles/Pot";


//Variables globales
long timeDHT = millis();

//Objeto Cliente

DHT dht(DHTPIN,DHTTYPE);
EspMQTTCLient client(SSID,PASSWORD,BROKER,NAMECLIENT,PORT);


void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(pinLED,OUTPUT);
  for(int i = 0;i<5;i++){
    pinMode(leds[i],OUTPUT);
  }
  pinMode(pinPhoto, INPUT); // Configura el pin del sensor como entrada.
  pinMode(PinPOT, INPUT);
  if(!client.isConnected()){
    Serial.println("Conectado con el broker!");
  }else{
    Serial.println("No Conectado, revise su conexión");
  }
  delay(5000);
}

//Funciones para la practica
//Funcion para prender y apagar leds.
void ledsFunction(String payload){
  //Lee los valores recibidos del payload
  if (payload == "1"){ //Si es 1 en ASCII
    digitalWrite(leds[0], HIGH); //Prende el led 1
    Serial.println("Led 1 encendido");//Envia el mensaje al serial
  }else if (payload == "2"){ //Si es 2 en ASCII
    digitalWrite(leds[1], HIGH);//Prende el led 2
    Serial.println("Led 2 encendido");//Envia el mensaje al serial
  }else if (payload == "3"){//Si es 3 en ASCII
    digitalWrite(leds[2], HIGH);//Prende el led 3
    Serial.println("Led 3 encendido");//Envia el mensaje al serial
  }else if (payload == "4"){//Si es 4 en ASCII
    digitalWrite(leds[3], HIGH);//Prende el led 4
    Serial.println("Led 4 encendido");//Envia el mensaje al serial
  }else if (payload == "5"){//Si es 5 en ASCII
    digitalWrite(leds[4], HIGH);//Prende el led 5
    Serial.println("Led 5 encendido");//Envia el mensaje al serial
  }else if (payload == "0"){//Si es 0 en ASCII
    for(int i = 4;i>=0;i--){
      digitalWrite(leds[i], LOW); //Apaga todos los leds
      Serial.println("Todos los leds se han apagado");//Envia el mensaje al serial
    }
  }else{
    Serial.println("Dato no válido");
  }
}






void onConnectionEstablished(){
  //Prender y apagar LEDS
  client.subscribe(ledsTopic,[](const String & payload){
    //Funcion para los leds.
    ledsFunction(String(payload));
  }
}







void loop() {
  // put your main code here, to run repeatedly:

}
