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
  Serial.begin(115200); //Inicializo comunicación serial
  pinMode(PinADC, INPUT); //Declaro al pin como entrada
}

void loop() {
  int sensor = analogRead(PinADC); //Guardo en una variable la lectura del pin
  Serial.println(sensor); //Imprimo el valor de la variable "sensor"
  }
