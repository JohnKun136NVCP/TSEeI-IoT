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

//Condición para habilitar el bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


BluetoothSerial BT; // Objeto Bluetooth

//Variable con el nombre del cliente (dispositivo a conectarse - esclavo)
String clientName = "Creeper_JohnyXianyaSLAVE"; 
bool connected;

void setup() {
  Serial.begin(115200); //Inicializar la comunicación serial
  BT.begin("Creeper_JohnyXianyaMASTER", true); //Nombre de su dispositivo Bluetooth y en modo maestro
  Serial.println("El dispositivo Bluetooth está en modo maestro.\n Conectando con el anfitrión ...");

  connected = BT.connect(clientName); //Inicializar la conexión vía bluetooth
  if (connected) {
    Serial.println("¡Conectado exitosamente!");
  } else {
    while (!BT.connected(10000)) {
      Serial.println("No se pudo conectar. \n Asegúrese de que el dispositivo remoto esté disponible y dentro del alcance, \n luego reinicie la aplicación.");
    }
  }
}
void loop() {
  if (digitalRead(SW1) == 1) { //Verifica si esta pulsado el botón
    Temperatura(); //Llama a la función Temperatura
  }
  if (digitalRead(SW2) == 0) {  //Verifica si esta pulsado el botón
    Humedad(); //LLama a la función Humedad();
  }
}

// Funcion Temperatura
void Temperatura() {
  //En el dado caso que el usuario ande dando más pulsaciones de las que debe se le restringe el uso
  if (millis() > timeCounter2 + timeThreshold) {
       BT.write(49); // Envía 1 en ASCII
       float temperature = dhtStatus(0); //En el primer caso es por si SW2 está apretado envia a la funcion dhtStatus con el valor de 0
       BT.print("La temperatura en este momento es de: ");//Imprime el texto en el serial del telefono
       BT.println(temperature);//Imprime el valor de la temperatura
       Serial.print("La temperatura en este momento es de: ");//Imprimir el texto en el serial del monitor serial
       Serial.println(temperature); //Imprime el valor de la temperatura en el monitor serial
       timeCounter2 = millis(); //Pusación (tiempo)
  }
}
//Funcion de Humedad
void Humedad(){
  //En el dado caso que el usuario ande dando más pulsaciones de las que debe se le restringe el uso
  if (millis() > timeCounter1 + timeThreshold) {
      BT.write(48); // Envía 0 en ASCII
      float humidity = dhtStatus(1); //En el primer caso es por si SW1 está apretado envia a la funcion dhtStatus con el valor de 1
      BT.print("La humedad en este momento es de: "); //Imprime el texto en el serial del telefono
      BT.println(humidity); //Imprime el valor de la humedad
      Serial.print("La humedad en este momento es de: "); //Imprimir el texto en el serial del monitor serial
      Serial.println(humidity); //Imprime el valor de la humedad en el monitor serial
      timeCounter1 = millis(); //Pusación (tiempo)
  }
}
