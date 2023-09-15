//Incluir librería de bluetooth
#include "BluetoothSerial.h"

//Definir el arreglo de leds
const int leds[5] = {14, 27, 26, 25, 33}; 

//Condición para habilitar el bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Definir un pin para el LED
BluetoothSerial BT; //Objeto Bluetooth

void setup() {
  BT.begin("Creeper_JohnyXianya"); //Nombre de su dispositivo Bluetooth y en modo esclavo
  for(int i = 0;i<5;i++){
    pinMode(leds[i],OUTPUT);//Pines de LED como salida
  }
}

void loop() {
  if (BT.available()) // Mientras haya datos por recibir vía bluetooth
  {    
    int val = BT.read(); // Lee un byte de los datos recibidos
    switch (val){
      case 49: //1 en ASCII
        digitalWrite(leds[0], HIGH);
        break;
      case 50:// 2 en ASCII
        digitalWrite(leds[1], HIGH);
        break;
      case 51:// 3 en ASCII
        digitalWrite(leds[2], HIGH);
        break;
      case 52:// 4 en ASCII
        digitalWrite(leds[3], HIGH);
        break;
      case 53:// 5 en ASCII
        digitalWrite(leds[4], HIGH);
        break;
      case 48:// 0 en ASCII
        for(int i = 5;i>=0;i--){
          digitalWrite(leds[i], LOW);
        }
        break;
    }
  }
}
