#define PIN_LDR 34
#define PIN_LM35 35

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Serial.println(analogRead(PIN_LDR));
  Serial.println(analogRead(PIN_LM35)*0.1221); //Lectura LM35 
}
