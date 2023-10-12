//Incluir librería de bluetooth
#include "BluetoothSerial.h"

//Condición para habilitar el bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Definir un pin para el LED
#define LED 2

BluetoothSerial BT; //Objeto Bluetooth

void setup() {
  Serial.begin(115200); //Inicializar la comunicación serial
  BT.begin("Creeper_JohnyXianyaSLAVE"); //Nombre de su dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejarse");
  pinMode (LED, OUTPUT); //Pin de LED como salida
}

void loop() {
  if (BT.available()) // Mientras haya datos por recibir vía bluetooth
  {
    String data = BT.readStringUntil('\n');//Lega hasta el un salto de linea que cada vez que llegue la informacion
    if(data.startsWith("Temp:")){ //Si el primer string es de temperatura -> Temp:
      float temperature = data.substring(5).toFloat(); //Convierte la temperatura de String a float 
      Serial.println("La temperatura(°C) de ahoria es de: "+String(temperature)); //Imprime la temperatura en modo String.
      digitalWrite(LED,HIGH); //Enciede el LED.
    }else if (data.startsWith("Humedad:")){// Si empieza con humedad entonces entra a este if
      float humidity = data.substring(8).toFloat(); //Convierte de string a float.
      Serial.println("Humedad (%) recibida: " + String(humidity)); //Imprime todo en un string.
      digitalWrite(LED,LOW);//Apaga el led.
      }
   }
}
