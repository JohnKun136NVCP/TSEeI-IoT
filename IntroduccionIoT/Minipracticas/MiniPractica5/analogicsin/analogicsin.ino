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
}

void loop() {
  int val = state ? 255 : 0;
  for(int i = 0;i<256;i++){
    float pwmSinValue = 126 + 92* sin(2*M_PI* i / 256);
    float DACsinValue = 126 * sin(2* i * M_PI / 256) + 127;
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
