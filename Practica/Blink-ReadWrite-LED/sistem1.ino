const  int LED_PIN = 32;
void setup() {
  pinMode(LED_PIN,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_PIN,HIGH);
  delay(500);
  digitalWrite(LED_PIN,LOW);
  delay(500);

}
