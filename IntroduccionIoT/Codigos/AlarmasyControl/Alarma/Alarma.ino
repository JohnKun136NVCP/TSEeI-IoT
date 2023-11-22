/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por: M. en I. Valente Vázquez Velázquez
  Última modificación: 20-abril-2023
  https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

// Definición de pines
#define PinLDR 34
#define PinButton 15

// Arreglo para los pines de los LEDs
int leds[5] = {14, 27, 26, 25, 33};

// Umbral para la lectura del sensor LDR
const int umbral = 3000;

void setup() {
  // Inicializa la comunicación serial a 115200 baudios
  Serial.begin(115200);
  
  // Configura los pines como entradas o salidas
  pinMode(PinLDR, INPUT);
  pinMode(PinButton, INPUT);
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }  
  // Inicia con todos los LEDs apagados
  apagado();
}

void loop() {
  // Lee el valor del sensor LDR (valor analógico)
  int sensor = analogRead(PinLDR);
  // Lee el estado del botón (1 si se presiona, 0 si no)
  int button = digitalRead(PinButton);
  
  // Muestra los valores leídos en la consola serial
  Serial.print(sensor);
  Serial.print(", ");
  Serial.println(button);
  
  // Si el valor del sensor supera el umbral o el botón está presionado,
  // activa la sirena, de lo contrario, mantiene todo apagado
  if((sensor > umbral) || (button == 1)){
    sirena();
  }
  else{
    apagado();
  }
}

// Función para activar la sirena (encender los LEDs)
void sirena(){
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], HIGH);
  }

  delay(500);
  // Apaga los LEDs
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], LOW);
  }
  
  delay(500);
}

// Función para apagar todos los LEDs
void apagado(){
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], LOW);
  }
}
