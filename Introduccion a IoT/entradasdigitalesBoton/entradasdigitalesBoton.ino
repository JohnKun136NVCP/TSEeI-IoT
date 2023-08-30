//Se definio el PullDown  -> Boton SW1
#define PinBotton_PullDown 15
//Se definio el PullDown  -> Boton SW2
#define PinBotton_PullUp 4
//Se definio el arreglo de leds.
const int leds[5] = {14, 27, 26, 25, 33};
//Se definio un contador para las pulsaciones de despues. 
long timeCounter = 0;
//Se definio un contador que servirá para el no. pulsaciones
int count = 0;
//Se definio el umbral.
const int timeThreshold = 150;

//Se inicializa los pins para los leds y tambien para los 2 botones
void setup() {
  for(int i = 0;i<5;i++){
    pinMode(leds[i],OUTPUT);
  }
  pinMode(PinBotton_PullDown, INPUT); //Boton 1  en booleano representa 0 o LOW
  pinMode(PinBotton_PullUp, INPUT); //Boton 2 en booleano representa 1 o HIGH
}


//Se inicializa el loop
void loop() {
  //Guardara en la lectura si es un 1 o 2 -> para PullDown es 0 por defecto y para PullUp es 1.
  int in_down = digitalRead(PinBotton_PullDown);
  int in_up = digitalRead(PinBotton_PullUp);
  //Si en el caso el PullDown cambiará a 1
    if (in_down == HIGH) {
      //Prevenir que se cuenten demaciadas pulsaciones en el loop
      if (millis() > timeCounter + timeThreshold) {
        //Si es menor a 5 el count entonces:
        if(count<5){
          //Prende la luz del no. led 
          digitalWrite(leds[count],in_down);
          //Suma +1 el count para ir recorriendo el arreglo
          count++;
          timeCounter = millis();
      }else{
        //En el caso si fuera más de 5 pulsaciones
        for(int i = 5;i>=0;i--){
          //Apaga todos los leds
          digitalWrite(leds[i],LOW);
          //Disminuye el valor de count = 5 a count = 0 cuando termina el ciclo
          count--;
        }
      }
    }
  }else if (in_up == LOW){ //En el caso si el boton de PullUp esta en Low o cambie a 0
    if (millis() > timeCounter + timeThreshold) {
      //Apagará todos los leds
        for(int i = 5;i>=0;i--){
          digitalWrite(leds[i],LOW);
        }
        //Se reinicializa a count = 0 para que no guarde ningun valor y empiece desde el inicio
       count = 0;
       timeCounter = millis();
    }
  }
}