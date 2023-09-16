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

//Definir pines
#define PinPWM 26

//Variables para definir el PWM
const int freq = 1000; //Frecuencia en Hz
const int ChanelPWM = 0; //Canal 0 - 15
const int resolution = 8; //Bits de resolución, hasta 8

void setup() {
  pinMode(PinPWM, OUTPUT); //Declarar pin como salida
  ledcSetup(ChanelPWM, freq, resolution); //Configuración del PWM
  ledcAttachPin(PinPWM, ChanelPWM); //Enlazar pin a canal
}

void loop() {
  //Escribo un contínuo incremental
  for(int i = 0; i < 256; i++){
    ledcWrite(ChanelPWM, i);
    delayMicroseconds(10000);
  }
  //Escribo un contínuo decremental
  for(int i = 256; i > -1; i--){
    ledcWrite(ChanelPWM, i);
    delayMicroseconds(10000);
  }
}
