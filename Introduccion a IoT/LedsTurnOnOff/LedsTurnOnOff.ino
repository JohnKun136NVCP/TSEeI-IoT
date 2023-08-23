//Definir el arreglo de leds
const int leds[5] = {14, 27, 26, 25, 33}; 

void setup() {
  //Definir los pines como salida
  for (int i = 0;i<=4;i++){
    pinMode(leds[i],OUTPUT);
    
  }
}

void loop() {
  //Ciclo para enceder los leds uno por uno.
  for(int i = 0;i< 5;i++){
    digitalWrite(leds[i],HIGH);
    delay(20);
    digitalWrite(leds[i],LOW);
    delay(20);
  }
  //Un pequeño retardo.
  delay(20);
  //Ciclo para apagar los leds en modo descendente
   for(int i = 4;i>=0;i--){
    digitalWrite(leds[i],HIGH);
    delay(20);
    digitalWrite(leds[i],LOW);
    delay(20);
  }
  delay(20);
}
