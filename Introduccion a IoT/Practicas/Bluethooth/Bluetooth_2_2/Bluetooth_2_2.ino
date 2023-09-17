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
    int val = BT.read(); // Lee un byte de los datos recibidos
    Serial.print("Recibido: ");
    Serial.println(val);
    if (val == 49) { // 1 en ASCII
      digitalWrite(LED, HIGH);
    }
    if (val == 48) { // 0 en ASCII
      digitalWrite(LED, LOW);
    }
  }
}
