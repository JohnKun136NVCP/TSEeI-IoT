/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por: M. en I. Valente Vázquez Velázquez
  Última modificación: 1-enero-2023
  https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

#define PinBotton_PullUp 4

int count = 0;
long timeCounter = 0;
const int timeThreshold = 150;

void setup() {
  Serial.begin(115200);
  pinMode(PinBotton_PullUp, INPUT);
}

void loop() {
  int in_up = digitalRead(PinBotton_PullUp);
  if (in_up == LOW) {
    if (millis() > timeCounter + timeThreshold) {
      count++;
      Serial.println(count);
      timeCounter = millis();
    }
  }
}
