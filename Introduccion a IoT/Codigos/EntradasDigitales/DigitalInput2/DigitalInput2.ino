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

#define PinBotton_PullUp 4
#define PinBotton_PullDown 15

#define PinLed_1 14
#define PinLed_2 27

void setup() {
  pinMode(PinLed_1, OUTPUT);
  pinMode(PinLed_2, OUTPUT);
  pinMode(PinBotton_PullUp, INPUT);
  pinMode(PinBotton_PullDown, INPUT);
}

void loop() {
  int x = digitalRead(PinBotton_PullUp);
  int y = digitalRead(PinBotton_PullDown);
  digitalWrite(PinLed_1, x);
  digitalWrite(PinLed_2, y);
}
