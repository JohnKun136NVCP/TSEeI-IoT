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

#define PinPWM1 26
#define PinPWM2 25
#define PinADC1 13
#define PinADC2 12

//Variables para definir el PWM
const int freq1 = 1000; //Frecuencia en Hz
const int ChanelPWM1 = 0; //Canal 0
const int resolution1 = 8; //Bits de resolución, hasta 8

const int freq2 = 500; //Frecuencia en Hz
const int ChanelPWM2 = 1; //Canal 1
const int resolution2 = 8; //Bits de resolución, hasta 8

void setup() {
  Serial.begin(115200);
  pinMode(PinPWM1, OUTPUT);
  pinMode(PinPWM2, OUTPUT);
  pinMode(PinADC1, INPUT);
  pinMode(PinADC2, INPUT);

  ledcSetup(ChanelPWM1, freq1, resolution1);
  ledcSetup(ChanelPWM2, freq2, resolution2);
  ledcAttachPin(PinPWM1, ChanelPWM1);
  ledcAttachPin(PinPWM2, ChanelPWM2);
}

void loop() {
  for(int i = 0; i < 256; i++){
    ledcWrite(ChanelPWM1, i);
    ledcWrite(ChanelPWM2, i);
    float v1 = analogRead(PinADC1)*(3.3/4096.0);
    float v2 = analogRead(PinADC2)*(3.3/4096.0);   
    delayMicroseconds(10000);
    
    Serial.print("S1:");
    Serial.print(v1);
    Serial.print(",");
    Serial.print("S2:");
    Serial.println(v2);    
  }
}
