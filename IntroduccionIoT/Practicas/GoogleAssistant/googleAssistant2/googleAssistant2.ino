/*
* Documentación : https://help.sinric.pro/pages/tutorials/dimmable-switch/YYAC-3S
*/

//Requisitos.
/*
 * 1. Los tres dispositivos tendrán que ser switch - Dimmer sino no va a funcionar
 * 2. Los pins tiene que user PWM para ello se implementó una función abajo.
 * 3. Las credenciales de los Switches son diferentes a las de switch-dimmer.
 * 4. El Crendentials.h debe incluir las 3.
 * 
*/

#ifdef ENABLE_DEBUG
  #define DEBUG_ESP_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif 

#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32) || defined(ARDUINO_ARCH_RP2040)
  #include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProDimSwitch.h"
#include "Credentials.h"

#define BAUD_RATE         115200                // Change baudrate to your need
#define PINLED1            14
#define PINLED2            27
#define PINLED3            26

// we use a struct to store all states and values for our dimmable switch
struct {
  bool powerState = false;
  int powerLevel = 0;
} device_state;

// setting PWM properties
const int freq = 1000; // 1KHz
const int ledChannel = 0;
const int resolution = 8;

void setPWM(int powerLevel) {
   int dutyCycle = map(powerLevel, 0, 100, 0, 255); // Map power level from 0 to 100, to a value between 115 to 255
   ledcWrite(ledChannel, dutyCycle);
   //delay(30);
}
bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Device %s power turned %s \r\n", deviceId.c_str(), state?"on":"off");
  device_state.powerState = state;  
  setPWM(state ? 100: 0);
  return true; // request handled properly
}
bool onPowerLevel(const String &deviceId, int &powerLevel) {
  device_state.powerLevel = powerLevel; 
  setPWM(powerLevel);
  Serial.printf("Device %s power level changed to %d\r\n", deviceId.c_str(), device_state.powerLevel);
  return true;
}
bool onAdjustPowerLevel(const String &deviceId, int &levelDelta) {
  device_state.powerLevel += levelDelta;
  Serial.printf("Device %s power level changed about %i to %d\r\n", deviceId.c_str(), levelDelta, device_state.powerLevel);
  levelDelta = device_state.powerLevel;
  setPWM(levelDelta);
  return true;
}

void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");

  #if defined(ESP8266)
    WiFi.setSleepMode(WIFI_NONE_SLEEP); 
    WiFi.setAutoReconnect(true);
  #elif defined(ESP32)
    WiFi.setSleep(false); 
    WiFi.setAutoReconnect(true);
  #endif

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  IPAddress localIP = WiFi.localIP();
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %d.%d.%d.%d\r\n", localIP[0], localIP[1], localIP[2], localIP[3]);
}
void setupSinricPro() {
  SinricProDimSwitch &myDimSwitch1 = SinricPro[DIMSWITCH1_ID];
  SinricProDimSwitch &myDimSwitch2 = SinricPro[DIMSWITCH2_ID];
  SinricProDimSwitch &myDimSwitch3 = SinricPro[DIMSWITCH3_ID];

  // set callback function to device
  myDimSwitch1.onPowerState(onPowerState);
  myDimSwitch1.onPowerLevel(onPowerLevel);
  myDimSwitch1.onAdjustPowerLevel(onAdjustPowerLevel);
  
  myDimSwitch2.onPowerState(onPowerState);
  myDimSwitch2.onPowerLevel(onPowerLevel);
  myDimSwitch2.onAdjustPowerLevel(onAdjustPowerLevel);
  
  myDimSwitch3.onPowerState(onPowerState);
  myDimSwitch3.onPowerLevel(onPowerLevel);
  myDimSwitch3.onAdjustPowerLevel(onAdjustPowerLevel);
  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}
void setupYYAC3S(){
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(PINLED1, ledChannel);
  ledcAttachPin(PINLED2, ledChannel);
  ledcAttachPin(PINLED3, ledChannel);
}

void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupYYAC3S();
  setupWiFi();
  setupSinricPro();
}
void loop() {
  SinricPro.handle();
}
