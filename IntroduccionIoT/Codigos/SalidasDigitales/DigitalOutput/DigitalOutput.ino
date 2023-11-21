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

//Defino pines
#define LED1 14
#define LED2 27

void setup() {
  //Declaro los pines como salida
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  //Enciendo dos leds durante 200 ms
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(200);

  //Apago dos leds durante 200 ms
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(200);
}
