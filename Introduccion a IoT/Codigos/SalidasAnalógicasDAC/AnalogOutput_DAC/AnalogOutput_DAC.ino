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

#define PinDAC 26

void setup() {
  pinMode(PinDAC, OUTPUT);
}

void loop() {
  for(int i = 0; i < 256; i++){
    dacWrite(PinDAC, i);
    delay(10);
  }
  for(int i = 255; i > -1; i--){
    dacWrite(PinDAC, i);
    delay(10);
  }
}
