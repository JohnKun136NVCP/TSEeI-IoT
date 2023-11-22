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

void setup() {
  Serial.begin(115200);
  pinMode(PinBotton_PullUp, INPUT);
  pinMode(PinBotton_PullDown, INPUT);
}

void loop() {
  int in_up = digitalRead(PinBotton_PullUp);
  int in_down = digitalRead(PinBotton_PullDown);
  Serial.print(in_up);
  Serial.print(", ");
  Serial.println(in_down);
}
