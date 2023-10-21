//Bibliotecas necesarias y otra para ocultar la informacion
#include"Credentials.h"//Incluimos las credenciales con el puerto y servidor broker
#include "EspMQTTClient.h" //Biblioteca para MQTTClient
#include "DHT.h" //Biblioteca para el sensor de temparatura.

//Pines
#define DHTPIN 32 //PIN Para el sesnor de de temparatura y humedad
#define DHTTYPE DHT11 //DHT11 sensor 
#define pinPhoto 34 //Pin para la fotoresistencia
const int leds[5] = {14, 27, 26, 25, 33}; //Declarar los demás leds
//Boton para SW1
#define SW1 15
//Boton para SW2
#define SW2 4
//Se definio un contador para las pulsaciones de despues. 
long timeCounter1 = 0;
//Se definio un contador para las pulsaciones de despues. 
long timeCounter2 = 0;
//Se definio el umbral.
int timeThreshold = 250;

//Topicos
String ledsTopic = "ClaseIoT/Angeles/Led"; //Topico para leds
String dhtTopicH =  "ClaseIoT/Angeles/DHT/Hum"; //Topico para la humedad
String dhtTopicT = "ClaseIoT/Angeles/DHT/Tem"; //Topioco para la temperatura
String dhtVolt = "ClaseIoT/Angeles/Pot"; //Temperatura para el voltaje de la fotoresistencia


//Variables globales
long timePower = millis(); //Tiempo transcurrido

//Objeto Cliente

DHT dht(DHTPIN,DHTTYPE);
EspMQTTClient client(SSID,PASSWORD,BROKER,NAMECLIENT,PORT);


void setup() {
  Serial.begin(115200); //Se inicia la comunicacion serial
  dht.begin(); //Empieza el funcionamiento del dht
  for(int i = 0;i<5;i++){ //Declaracion de los leds de salida
    pinMode(leds[i],OUTPUT);
  }
  pinMode(pinPhoto, INPUT); // Configura el pin del sensor como entrada.
  pinMode(SW1, INPUT); //Boton 1  en booleano representa 0 o LOW
  pinMode(SW2, INPUT); //Boton 2 en booleano representa 1 o HIGH
  if(!client.isConnected()){ //Verificacion con la conexion del cliente.
    Serial.println("Conectado con el broker!");
  }else{
    Serial.println("No Conectado, revise su conexión");
  }
  delay(5000); //Una espera de 5 segundos
}

//Funciones para la practica
//Funcion para prender y apagar leds.
void ledsFunction(String payload){ //Funcion para enceder o apagar los leds
  //Lee los valores recibidos del payload
  String auxiliar = payload.substring(0); //Recibe el primer valor del payload, i.e. 1,2,3,4,5,0.
  int value = auxiliar.toInt(); //Lo convierte a un entero y lo almacena en la variable value
  Serial.println(value); //Verificamos en el serial si este recibiendo el entero
  if (value == 1){ //Si es 1 
    digitalWrite(leds[0], HIGH); //Prende el led 1
    Serial.println("Led 1 encendido");//Envia el mensaje al serial
  }else if (value == 2){ //Si es 2 
    digitalWrite(leds[1], HIGH);//Prende el led 2
    Serial.println("Led 2 encendido");//Envia el mensaje al serial
  }else if (value == 3){//Si es 3 
    digitalWrite(leds[2], HIGH);//Prende el led 3
    Serial.println("Led 3 encendido");//Envia el mensaje al serial
  }else if (value == 4){//Si es 4 
    digitalWrite(leds[3], HIGH);//Prende el led 4
    Serial.println("Led 4 encendido");//Envia el mensaje al serial
  }else if (value == 5){//Si es 5
    digitalWrite(leds[4], HIGH);//Prende el led 5
    Serial.println("Led 5 encendido");//Envia el mensaje al serial
  }else if (value == 0){//Si es 0
    for(int i = 4;i>=0;i--){
      digitalWrite(leds[i], LOW); //Apaga todos los leds
    }
    Serial.println("Todos los leds se han apagado");//Envia el mensaje al serial
  }else{
    Serial.println("Dato no válido");//En el caso que no sea posible convertirlo
  }
}
void onConnectionEstablished(){
  //Prender y apagar LEDS
  client.subscribe(ledsTopic,[](const String & payload){
    //Funcion para los leds.
    ledsFunction(String(payload)); //recibe el valor del payload para la funcion de Leds
  });
}

//Funcion de Humedad
float Humedad(){
  //En el dado caso que el usuario ande dando más pulsaciones de las que debe se le restringe el uso
  if (millis() > timeCounter1 + timeThreshold) {
      float humidity = dhtStatus(1); //En el primer caso es por si SW1 está apretado envia a la funcion dhtStatus con el valor de 1
      Serial.print("La humedad en este momento es de: "); //Imprimir el texto en el serial del monitor serial
      Serial.println(humidity); //Imprime el valor de la humedad en el monitor serial
      timeCounter1 = millis(); //Pusación (tiempo)
      float hum = dhtStatus(1); // Da un 1 para que nada más regrese la humedad.
      return hum; //Retorna la humedad
  }
}
// Funcion Temperatura
float Temperatura() {
  //En el dado caso que el usuario ande dando más pulsaciones de las que debe se le restringe el uso
  if (millis() > timeCounter2 + timeThreshold) {
       float temperature = dhtStatus(0); //En el primer caso es por si SW2 está apretado envia a la funcion dhtStatus con el valor de 0
       Serial.print("La temperatura en este momento es de: ");//Imprimir el texto en el serial del monitor serial
       Serial.println(temperature); //Imprime el valor de la temperatura en el monitor serial
       timeCounter2 = millis(); //Pusación (tiempo)
       float tem = dhtStatus(0);// Da un 0 para que nada más regrese la humedad.
       return tem;//Retorna la temperatura
  }
}
//Evalua constantemente el estado del DHT 11
float dhtStatus(int value){
  delay(2000); //Retrazo por 2 segundos
  float h = dht.readHumidity(); //Lee los valores de la humedad
  float t = dht.readTemperature(); // Lee los valores de la temperatura
  if (isnan(h) || isnan(t)) { //Verifica si estos valores no están vacios o son nulos
    Serial.println(F("Failed to read from DHT sensor!")); //En el caso que no los haya leido entonces envía este error
  }if (isnan(h)!=true && value == 1){ //Si es diferente el valor de la humedad de nulo y SW1 está activo
    return h; //Regresa la humedad
  }if (isnan(t)!=true && value == 0){ //Si es diferente el valor de la temmperatura de nulo y SW2 está activo.
    return t; //Regresa la temperatura
  }
}
void loop() {
  client.loop(); //Inicia la comunicacion del cliente del MQTT
  int sensor = analogRead(pinPhoto); //Va leyendo la lectura de la fotoresistencia
  if (millis() - timePower >= 5000) {//Si pasa 5seg entonces procede el if
    float voltaje = (sensor / 4095.0) * 3.3; //Calcaucla el valor del voltaje de la fotoresistencia
    String mensaje = "El valor de la fotoresistencia es de: "+String(voltaje); //Lo convierte en un string para el mensaje
    Serial.println(mensaje); // Imprime el valor del valor de la fotoresistencia
    client.publish(dhtVolt,mensaje); //Publica el mensaje del voltaje en el su respectivo topico
    timePower = millis(); //El conteo de milisegundos
  }
  if (digitalRead(SW1) == 1) { //Verifica si esta pulsado el botón
    float hum = Humedad(); //El valor que recibe es un float que es de la humedad
    String mensaje = "La humedad es de "+(String)hum+"%"; //Lo convierte a string para el mensaje
    client.publish(dhtTopicH,mensaje); //Publica el mensaje de la humedad;
  }
  if (digitalRead(SW2) == 0) {  //Verifica si esta pulsado el botón
    float tem = Temperatura(); ////El valor que recibe es un float que es de la temperatura
    String mensaje = "La temperatura es de "+(String)tem+"°C";//Lo convierte a string para el mensaje
    client.publish(dhtTopicT,mensaje); //Publica el mensaje de la temperatura;
   }
}
