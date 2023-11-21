//Incluir librería de bluetooth
#include "BluetoothSerial.h"
//Incluir librería de Temperatura y Humedad
#include "DHT.h"
//Boton para SW1
#define SW1 15
//Boton para SW2
#define SW2 4
#define DHTPIN 32     // Digital pin contectado al sensor DHT
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
//Se definio un contador para las pulsaciones de despues. 
long timeCounter1 = 0;
//Se definio un contador para las pulsaciones de despues. 
long timeCounter2 = 0;
//Se definio el umbral.
int timeThreshold = 250;


//Definir el arreglo de leds
const int leds[5] = {14, 27, 26, 25, 33}; 

//Condición para habilitar el bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Definir un pin para el LED
BluetoothSerial BT; //Objeto Bluetooth
void setup() {
  Serial.begin(115200); //Inicializar la comunicación serial
  BT.begin("Creeper_JohnyXianya"); //Nombre de su dispositivo Bluetooth y en modo esclavo
  for(int i = 0;i<5;i++){
    pinMode(leds[i],OUTPUT);//Pines de LED como salida
  }
  dht.begin();
  pinMode(SW1, INPUT); //Boton 1  en booleano representa 0 o LOW
  pinMode(SW2, INPUT); //Boton 2 en booleano representa 1 o HIGH
}

void loop() {
  if (digitalRead(SW1) == 1) { //Verifica si esta pulsado el botón
    Humedad(); //LLama a la función Humedad();
  }
  if (digitalRead(SW2) == 0) {  //Verifica si esta pulsado el botón
    Temperatura(); //Llama a la función Temperatura
  }
  else{ //En el dado caso que ambos casos no pasaran entonces envía a llamar la función de abajo
    bluetoothValues(); //Funcion bluetoothValues();
  }
}

//Funciones
//Funcion de Humedad
void Humedad(){
  //En el dado caso que el usuario ande dando más pulsaciones de las que debe se le restringe el uso
  if (millis() > timeCounter1 + timeThreshold) {
      float humidity = dhtStatus(1); //En el primer caso es por si SW1 está apretado envia a la funcion dhtStatus con el valor de 1
      BT.print("La humedad en este momento es de: "); //Imprime el texto en el serial del telefono
      BT.println(humidity); //Imprime el valor de la humedad
      Serial.print("La humedad en este momento es de: "); //Imprimir el texto en el serial del monitor serial
      Serial.println(humidity); //Imprime el valor de la humedad en el monitor serial
    timeCounter1 = millis(); //Pusación (tiempo)
  }
}
// Funcion Temperatura
void Temperatura() {
  //En el dado caso que el usuario ande dando más pulsaciones de las que debe se le restringe el uso
  if (millis() > timeCounter2 + timeThreshold) {
       float temperature = dhtStatus(0); //En el primer caso es por si SW2 está apretado envia a la funcion dhtStatus con el valor de 0
       BT.print("La temperatura en este momento es de: ");//Imprime el texto en el serial del telefono
       BT.println(temperature);//Imprime el valor de la temperatura
       Serial.print("La temperatura en este momento es de: ");//Imprimir el texto en el serial del monitor serial
       Serial.println(temperature); //Imprime el valor de la temperatura en el monitor serial
       timeCounter2 = millis(); //Pusación (tiempo)
  }
}
//Evalua constantemente el estado del DHT 11
float dhtStatus(int value){
  while (1){ //Un ciclo infinito para verificar los datos de DHT
    delay(2000); //Retrazo por 2 segundos
    float h = dht.readHumidity(); //Lee los valores de la humedad
    float t = dht.readTemperature(); // Lee los valores de la temperatura
    if (isnan(h) || isnan(t)) { //Verifica si estos valores no están vacios o son nulos
      Serial.println(F("Failed to read from DHT sensor!")); //En el caso que no los haya leido entonces envía este error
    }if (isnan(h)!=true && value == HIGH){ //Si es diferente el valor de la humedad de nulo y SW1 está activo
      return h; //Regresa la humedad
    }if (isnan(t)!=true && value == LOW){ //Si es diferente el valor de la temmperatura de nulo y SW2 está activo.
      return t; //Regresa la temperatura
    }
  }
}
//Recibe los valores ingresados por el usuario.
void bluetoothValues(){
  //Lee los valores recibidos para el Bluetooth
  int val = BT.read();
  if (val == 49){ //Si es 1 en ASCII
    digitalWrite(leds[0], HIGH); //Prende el led 1
  }else if (val == 50){ //Si es 2 en ASCII
    digitalWrite(leds[1], HIGH);//Prende el led 2
  }else if (val == 51){//Si es 3 en ASCII
    digitalWrite(leds[2], HIGH);//Prende el led 3
  }else if (val == 52){//Si es 4 en ASCII
    digitalWrite(leds[3], HIGH);//Prende el led 4
  }else if (val == 53){//Si es 5 en ASCII
    digitalWrite(leds[4], HIGH);//Prende el led 5
  }else if (val == 48){//Si es 0 en ASCII
    for(int i = 4;i>=0;i--){
      digitalWrite(leds[i], LOW); //Apaga todos los leds
    }
  }
}
