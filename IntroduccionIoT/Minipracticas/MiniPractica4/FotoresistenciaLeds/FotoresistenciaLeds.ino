//Se define el arreglo de leds
const int leds[5] = {14, 27, 26, 25, 33}; 
//Se define el pin del sensor de fotoresistencia
#define PinADC 34


void setup(){
  //Se inicializa los leds para salida
  for (int i = 0; i <=4; i++){
    pinMode(leds[i], OUTPUT);
    } 
  pinMode(PinADC, INPUT); // Declarar al pin como salida
  
}
//Apaga los leds
void turnOffLeds(){
  for(int i = 4;i>=0;i--){
    digitalWrite(leds[i],LOW);
  }
}

void loop(){
  //Lee la señal de la fotoresistencia
  int sign = analogRead(PinADC);
  turnOffLeds();
  //Estan acotados segun el humbral que se puede calcular
  //Si es diferente de 0 y menor que 600 entonces enciende un led
  if (sign!= 0 && sign < 600) {
     digitalWrite(leds[0],HIGH);
     }
    //Acotado en un rango de [600,1200)
    else if (sign >= 600 && sign < 1200){
       digitalWrite(leds[0],HIGH);
       digitalWrite(leds[1],HIGH);
    }
    //Acotado en un rango de [1200,1800)
    else if (sign >= 1200 && sign < 1800){
        for(int i = 0; i < 3; i++){
          digitalWrite(leds[i], HIGH);
          }
    }
    //Acotado en un rango de [1800,2400)
    else if (sign >= 1800 && sign < 2400){
        for(int i = 0; i < 4; i++){
          digitalWrite(leds[i], HIGH);
          }
    }
    //Acotado en un rango de [2400,4096)
    else if (sign >= 2400 && sign < 4096){
        for(int i = 0; i < 5; i++){
          digitalWrite(leds[i], HIGH);
          }
      }
    //Al quitar la señal apagamos los leds  
    else if (sign==0){
      //Llama la función si no hay un valor
      turnOffLeds();
        }
        delay(200);
      }
      
      
