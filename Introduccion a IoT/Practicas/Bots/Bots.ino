#include "CTBot.h" // Incluye la biblioteca CTBot para interactuar con la API de Telegram.
#include "Credentials.h"

#define pinPhoto 34


const int leds[5] = {14, 27, 26, 25, 33};


CTBot myBot;
TBMessage msg;


void setup() {
  Serial.begin(115200); // Inicia la comunicación serial.
  Serial.print("Comenzando TelegramBot...  ");
  pinMode(pinPhoto, INPUT); // Configura el pin del sensor como entrada.
  //Inicializar los leds para salida
  for (int i = 0; i <=4; i++){
    pinMode(leds[i], OUTPUT);
  } 
  
  myBot.wifiConnect(SSID, PASSWORD); // Conecta a la red Wi-Fi especificada.
  myBot.setTelegramToken(TOKEN); // Establece el token de autenticación para el bot de Telegram.
  delay(2000); // Espera un momento para que la conexión se establezca.
  // Verifica si la conexión con el bot de Telegram se ha establecido correctamente.
  if (myBot.testConnection()){
    Serial.println("Conectado con Bot");
  }else{
    Serial.println("Error en la conexión");
  }
}

void loop() {

  // Verifica si hay un nuevo mensaje para el bot de Telegram.
  if (myBot.getNewMessage(msg)) {
    if(msg.messageType == CTBotMessageText){
      if (msg.text.equalsIgnoreCase("/start")) {
        myBot.sendMessage(msg.sender.id, "Este bot puede intecturar usando leds prendiendo y apagando, monitorear el voltaje y ejecutar una alarma dado un umbral que me proporciones. Para ver las opciones, por favor, usa el comando /options");
      }else if (msg.text.equalsIgnoreCase("/options")){
        myBot.sendMessage(msg.sender.id, "Este bot puede intecturar usando leds prendiendo y apagando, monitorear el voltaje y ejecutar una alarma dado un umbral que me proporciones. Para ver las opciones, por favor, usa el comando /options");
      }else if (msg.text.equalsIgnoreCase("/helpleds")){
        myBot.sendMessage(msg.sender.id,"Comandos de ayuda para sistema Led");
        myBot.sendMessage(msg.sender.id,"/led1 -> Apagar o Encender el Led 1");
        myBot.sendMessage(msg.sender.id,"/led2 -> Apagar o Encender el Led 2");
        myBot.sendMessage(msg.sender.id,"/led3 -> Apagar o Encender el Led 3");
        myBot.sendMessage(msg.sender.id,"/led4 -> Apagar o Encender el Led 4");
        myBot.sendMessage(msg.sender.id,"/led5 -> Apagar o Encender el Led 5");
        myBot.sendMessage(msg.sender.id,"/ledall -> Apagar o Encender todos los leds");
      }else if(msg.text.equalsIgnoreCase("/led1")){
        int val = digitalRead(leds[0]);
         if(val != HIGH){
          digitalWrite(leds[0],HIGH);
          myBot.sendMessage(msg.sender.id, "Led 1 encendido");
         }else if (val != LOW){
          digitalWrite(leds[0],LOW);
          myBot.sendMessage(msg.sender.id, "Led 1 apagado");
         }
      }else if(msg.text.equalsIgnoreCase("/led2")){
        int val = digitalRead(leds[1]);
         if(val != HIGH){
          digitalWrite(leds[1],HIGH);
          myBot.sendMessage(msg.sender.id, "Led 2 encendido");
         }else if (val != LOW){
          digitalWrite(leds[1],LOW);
          myBot.sendMessage(msg.sender.id, "Led 2 apagado");
         }
      }else if(msg.text.equalsIgnoreCase("/led3")){
        int val = digitalRead(leds[2]);
         if(val != HIGH){
          digitalWrite(leds[2],HIGH);
          myBot.sendMessage(msg.sender.id, "Led 3 encendido");
         }else if (val != LOW){
          digitalWrite(leds[2],LOW);
          myBot.sendMessage(msg.sender.id, "Led 3 apagado");
         }
      }else if(msg.text.equalsIgnoreCase("/led4")){
        int val = digitalRead(leds[3]);
         if(val != HIGH){
          digitalWrite(leds[3],HIGH);
          myBot.sendMessage(msg.sender.id, "Led 4 encendido");
         }else if (val != LOW){
          digitalWrite(leds[3],LOW);
          myBot.sendMessage(msg.sender.id, "Led 4 apagado");
         }
      }else if(msg.text.equalsIgnoreCase("/led5")){
        int val = digitalRead(leds[4]);
         if(val != HIGH){
          digitalWrite(leds[4],HIGH);
          myBot.sendMessage(msg.sender.id, "Led 4 encendido");
         }else if (val != LOW){
          digitalWrite(leds[4],LOW);
          myBot.sendMessage(msg.sender.id, "Led 4 apagado");
         }
      }else if(msg.text.equalsIgnoreCase("/ledall")){
        for(int i = 0;i<5;i++){
          int val = digitalRead(leds[i]);
          if(val==LOW){
            int lednum = i+1;
            String warning = (String)"Encendiendo led:  " + (String)lednum;
            myBot.sendMessage(msg.sender.id, warning);
            delay(1000);
            digitalWrite(leds[i],HIGH); 
          }else{
            int lednum = i+1;
            String warning = (String)"Apagando led: " + (String)lednum;
            myBot.sendMessage(msg.sender.id, warning);
            delay(1000);
            digitalWrite(leds[i],LOW); 
          }
        }
        myBot.sendMessage(msg.sender.id, "Todos los leds se han apagado/prediddo");
      }else {
          // Si el mensaje recibido no coincide con ninguno de los comandos anteriores, envía un mensaje de error.
        myBot.sendMessage(msg.sender.id, "Mensaje no válido, intenta de nuevo con: /options");
      }

    }
    
  }  
  delay(50); 
}
