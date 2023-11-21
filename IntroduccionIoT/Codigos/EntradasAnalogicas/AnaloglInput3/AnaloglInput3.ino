/*
 *Universidad Nacional Autónoma de México
 *Facultad de Ciencias
 *Licenciatura en Ciencias de la Computación
 *Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas
 *
 *Escrito por: M. en I. Valente Vázquez Velázquez
 *Última modificación: 1-enero-2023
 *https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

#define PinADC 34 //Defino pin

void setup() {
  Serial.begin(115200);     //Inicializo comunicación serial
  pinMode(PinADC, INPUT);   //Declaro al pin como entrada
}

void loop() {
  int sensor = analogRead(PinADC);  //Guardo en una variable la lectura del pin
  int prom = media(400, PinADC);     //Guardo en una variable el resultado de la función media
  Serial.print("Prom:");
  Serial.print(prom);               //Imprimo el valor de la variable "prom"
  Serial.print(",");
  Serial.print("Sensor:");
  Serial.println(sensor);           //Imprimo el valor de la variable "sensor"
}

//Función media(número de datos, pin de entrada)
int media(int data_number, int pin) {
  int value = 0;
  for (int i = 0; i < data_number; i++) {
    value = analogRead(pin) + value;
  }
  value /= data_number;
  return value;
}
