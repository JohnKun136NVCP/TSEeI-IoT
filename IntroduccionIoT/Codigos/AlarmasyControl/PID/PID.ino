/*
 *Universidad Nacional Autónoma de México
 *Facultad de Ciencias
 *Licenciatura en Ciencias de la Computación
 *Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas
 *
 *Escrito por: M. en I. Valente Vázquez Velázquez
 *Última modificación: 1-mayo-2023
 *https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
 *
 *Conectar el PinDAC con el PinADC
*/

#define PinDAC 25 //Pin de escritura
#define PinADC 13 //Pin de lectura
#define PinPOT 35 //Pin de setpoint

//PID constantes
const double Kp = 100, Ki = 0.25, Kd = 5;
//const double Kp = 0.01, Ki = 0.05, Kd = 0.001;
//const double Kp = 1, Ki = 1, Kd = 1;

//PID variables
unsigned long currentTime, previousTime;
double elapsedTime;
double lastError, P_Error, I_Error, D_Error;
double inPut, outPut;
double setPoint;

void setup() {
  Serial.begin(115200);
  pinMode(PinDAC, OUTPUT);
  pinMode(PinADC, INPUT);
  pinMode(PinPOT, INPUT);
}

void loop() {
  inPut = analogRead(PinADC) * (3.3 / 4096.0); //Se lee el voltaje del output
  setPoint = analogRead(PinPOT) * (3.3 / 4096.0); //Se lee el voltaje del pot para el setpoint

  currentTime = millis();//Se guarda el tempo actual
  elapsedTime = currentTime - previousTime;//Se calcula el tiempo transcurrido

  P_Error = setPoint - inPut;//Se obtiene el error proporcional
  I_Error += P_Error * elapsedTime;//Se obtiene el error integral
  D_Error = (P_Error - lastError) / elapsedTime;//Se obtiene el error derivativo
  outPut = (Kp * P_Error) + (Ki * I_Error) + (Kd * D_Error);//Se calcula la salida del controlador

  lastError = P_Error;//El error actual se convierte en el error pasado
  previousTime = currentTime;//El tiempo actual se convierte en el tiempo pasado

  dacWrite(PinDAC, outPut); //Salida DAC del ESP32

  Serial.print("Input:");
  Serial.print(inPut);
  Serial.print(",");
  Serial.print("Setpoint:");
  Serial.println(setPoint);
  delay(50);
}
