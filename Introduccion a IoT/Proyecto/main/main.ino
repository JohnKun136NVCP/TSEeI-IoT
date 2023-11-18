
//LEDS AND BUZZER
#define LED_1 14 
#define LED_2 26 
#define LED_3 27
#define Bzzer 4
//LIBRARIES
//Library for WiFi
#include <WiFi.h>
#include "ESPAsyncWebServer.h" //Server for ESP32
//Library for credentials and passwords
#include "Credentials.h"
//Library for emailclient
#include <ESP_Mail_Client.h>
//Library for making ping to website
#include <ESP32Ping.h>
//Library for TelegramBot
#include <CTBot.h>
#define SMTP_HOST  "smtp.gmail.com"
#define SMTP_PORT esp_mail_smtp_port_465 //Port to SMTP

//GLOBAL VARIABLES
int pingNumber = 4;
//Message 
int ok = 0;
int warning = 0;
int danger = 0;
int emailSender = 0;
const int resolution = 8; 
//Telegram bot message
bool warningMessage = false;
bool dangerMessage = false;

//Objects
CTBot myBot; //Telegram bot object
TBMessage msg; // Object to get messages from Telegram Bot
SMTPSession smtp; //Object used SMTPSession for SMTP transport
WiFiServer server(80); // Puerto 80 es común para HTTP, pero puedes usar otro


void setup() {
  Serial.begin(115200);
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);
  pinMode(LED_3,OUTPUT);
  pinMode(Bzzer,OUTPUT);
  WiFi.begin(ssid_STA, password_STA);
  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
  }
  Serial.println(WiFi.localIP());
  myBot.setTelegramToken(BOT_TOKEN);
  server.begin();
}
void loop() {
  idsLedUP();//Leds, alerts and PWM
  telegramBotService();//Telegram bot
}
