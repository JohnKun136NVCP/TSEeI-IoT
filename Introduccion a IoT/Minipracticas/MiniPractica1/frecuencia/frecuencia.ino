//Se inicializa el led del pin.
void setup() {
  pinMode(14, OUTPUT);
}

//Se genera el loop. 
void loop() {
  /*
   * La frecuencia en el que ya no se percibe el led epara mayor a f>60Hz -> T<11ms
   */
  digitalWrite(14, HIGH);
  delay(12);
  digitalWrite(14, LOW);   
  delay(12);           
}
