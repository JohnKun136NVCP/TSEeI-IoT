#define PinPWM 26
#define PinDAC 25
#define PinADCPWM 13
#define PinADCDAC 12

// Variables para definir el PWM
const int freq = 1000;      // Frecuencia en Hz
const int ChanelPWM = 0;    // Canal 0 - 15
const int resolution = 8;   // Bits de resolución, hasta 8
const int timedelay = 5000; // Delay en microsegundos
bool state = true;          // Variable de estado

void setup() {
  Serial.begin(115200);
  pinMode(PinPWM, OUTPUT);
  pinMode(PinDAC, OUTPUT);
  pinMode(PinADCPWM, INPUT);
  pinMode(PinADCDAC, INPUT);

  ledcSetup(ChanelPWM, freq, resolution);
  ledcAttachPin(PinPWM, ChanelPWM);
  ledcAttachPin(PinDAC, ChanelPWM);
}

void loop() {
  int val = state ? 255 : 0;
  for(int i = 0;i<256;i++){
    float DACsinValue = 135 + 85 * sin( M_PI *i/256);
    float pwmSinValue = 128 + 128 * sin(PI *i/ 180);
    dacWrite(PinDAC, DACsinValue);
    ledcWrite(ChanelPWM, pwmSinValue);  
    Serial.print("PWM:");
    Serial.print(analogRead(PinADCPWM));
    Serial.print(",");
    Serial.print("DAC:");
    Serial.println(analogRead(PinADCDAC));
    delayMicroseconds(timedelay);

  }
  state = !state;
}
