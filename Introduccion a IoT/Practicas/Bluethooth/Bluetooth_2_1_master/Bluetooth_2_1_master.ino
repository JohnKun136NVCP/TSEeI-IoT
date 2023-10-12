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

//Variable con el nombre del cliente (dispositivo a conectarse - maestro)
String clientName = "Creeper_JohnyXianyaSLAVE"; //Clave del cliente para modo maestro
bool connected; //Variable para conectado

void setup() {
  Serial.begin(115200); //Inicializar la comunicación serial
  BT.begin("Creeper_JohnyXianyaMASTER", true); //Nombre de su dispositivo Bluetooth y en modo maestro
  Serial.println("El dispositivo Bluetooth está en modo maestro.\n Conectando con el anfitrión ..."); //Mensaje cuando este conectandose

  connected = BT.connect(clientName); //Inicializar la conexión vía bluetooth
  if (connected) { //minetras que este conectado
    Serial.println("¡Conectado exitosamente!"); //Si se conecte directamente 
  } else {
    while (!BT.connected(10000)) { //Secuencia en que se conecta
      Serial.println("No se pudo conectar. \n Asegúrese de que el dispositivo remoto esté disponible y dentro del alcance, \n luego reinicie la aplicación.");//En el caso que no se conecte arroja el mensaje
    }
  }
}
void loop() {
  if (digitalRead(SW1) == HIGH) { //Verifica si esta pulsado el botón
    Temperatura();//Entrega la temperatura y envia la temperatura del DHT
  }
  else if (digitalRead(SW2) == LOW) {  //Verifica si esta pulsado el botón
    Humedad(); //LLama a la función Humedad() y envia la humedad del DHT.
  }
}

// Funcion Temperatura
void Temperatura() {
  //En el dado caso que el usuario ande dando más pulsaciones de las que debe se le restringe el uso
  if (millis() > timeCounter2 + timeThreshold) {
       //BT.write(49); // Envía 1 en ASCII
       float temperature = dhtStatus(1);//En el primer caso es por si SW2 está apretado envia a la funcion dhtStatus con el valor de 0
       //BT.print("La temperatura en este momento es de: ");//Imprime el texto en el serial del telefono
       BT.print("Temp:");
       BT.print(temperature); //Imprime el valor de la temperatura en el monitor serial
       ///BT.println(temperatureString);//Imprime el valor de la temperatura
       Serial.print("La temperatura en este momento es de: ");//Imprimir el texto en el serial del monitor serial
       Serial.println(temperature); //Imprime el valor de la temperatura en el monitor serial
       timeCounter2 = millis(); //Pusación (tiempo)
  }
}
//Evalua constantemente el estado del DHT 11
float dhtStatus(int value){
    float h = dht.readHumidity(); //Lee los valores de la humedad
    float t = dht.readTemperature(); // Lee los valores de la temperatura
    if (isnan(h) || isnan(t)) { //Verifica si estos valores no están vacios o son nulos
      Serial.println(F("Failed to read from DHT sensor!")); //En el caso que no los haya leido entonces envía este error
    }if (isnan(h)!=true && value == 0){ //Si es diferente el valor de la humedad de nulo y SW1 está activo
      return h; //Regresa la humedad
    }if (isnan(t)!=true && value == 1){ //Si es diferente el valor de la temmperatura de nulo y SW2 está activo.
      return t; //Regresa la temperatura
    }
}



//Funcion de Humedad
void Humedad(){
  //En el dado caso que el usuario ande dando más pulsaciones de las que debe se le restringe el uso
  if (millis() > timeCounter1 + timeThreshold) {
      float humidity = dhtStatus(0); //En el primer caso es por si SW1 está apretado envia a la funcion dhtStatus con el valor de 1
      BT.print("Humedad:"); //Imprime el texto en el serial del telefono
      BT.println(humidity); //Imprime el valor de la humedad
      Serial.print("Humedad: "); //Imprimir el texto en el serial del monitor serial
      Serial.println(humidity); //Imprime el valor de la humedad en el monitor serial
      timeCounter1 = millis(); //Pusación (tiempo)
  }
}
