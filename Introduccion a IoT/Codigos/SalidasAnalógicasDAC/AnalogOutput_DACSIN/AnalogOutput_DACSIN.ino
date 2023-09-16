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
#define PinDAC 25
#define PinADC 12

void setup() {
  Serial.begin(115200); //Inicializar comunicación serial
  pinMode(PinDAC, OUTPUT); //Declaro pin como salida
  pinMode(PinADC, INPUT); //Declaro pin como entrada
}

void loop() {
  //Escribo un contínuo incremental de valore y los leo con el ADC
  for (int i = 0; i < 360; i++) {
    float seno = 126 * sin(i * M_PI / 180) + 128;
    dacWrite(PinDAC, seno);
    Serial.println(analogRead(PinADC));// * (3.3 / 4096.0));
    delay(10);
  }
}
