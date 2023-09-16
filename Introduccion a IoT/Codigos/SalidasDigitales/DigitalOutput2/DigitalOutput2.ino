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

//Defino los leds de uso en un arreglo
const int leds[5] = {14, 27, 26, 25, 33};

void setup() {
  //Defino mis pines como salida
  for (int i = 4; i >= 0 ; i--) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  //Ciclo for para encender 5 leds y esperar 200 ms
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(200);

  //Ciclo for para apagar 5 leds y esperar 200 ms
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], LOW);
  }
  delay(200);
}
