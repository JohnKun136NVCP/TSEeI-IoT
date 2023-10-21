#define RELE 14
#define PIN_BUTTON 33

int led_status = 0;

int menu = 2;

//debouncing (evitar el rebote del boton)
unsigned long lastDebounceTime = 0;
unsigned debounceDelay = 200;



void IRAM_ATTR isr_button(){
  if (millis()- lastDebounceTime > debounceDelay){
    led_status++;
    if (led_status >= menu){
      led_status = 0;
    
    }
    if(led_status >= menu) led_status = 0;
//    led_status = (led_status >= 7) ?0 : led_status+1;
   lastDebounceTime = millis();
   
   
   }

}


void setup() {
  pinMode(PIN_BUTTON,INPUT);
  attachInterrupt(PIN_BUTTON,isr_button,RISING);
  pinMode(RELE,OUTPUT);

  Serial.begin(115200);

}

void loop() {
  switch(led_status){
    case 1:
      digitalWrite(RELE,HIGH);
      Serial.println("encendido");
    break;
    
    case 2:
      digitalWrite(RELE,LOW);
      Serial.println("apagado");
    break;

    
    default:
      digitalWrite(RELE,LOW);
      Serial.println("apagado");
    break;

  
  }

  
}
