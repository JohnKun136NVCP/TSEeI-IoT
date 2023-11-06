//Library for WiFi
#include <WiFi.h>
//Library for making ping to website
#include <ESP32Ping.h>
//Library for TelegramBot
#include <CTBot.h>
//Library for emailclient
#include <ESP_Mail_Client.h>
//Library for credentials and passwords
#include "Credentials.h"

//Leds and pins
#define led 2
#define redLed 33
#define yellowLed 26
#define greenLed 27

#define SMTP_HOST  "smtp.gmail.com"
#define SMTP_PORT esp_mail_smtp_port_465 //Port to SMTP
//Global variables
bool shape = false;
WiFiServer server(80); // Puerto 80 es común para HTTP, pero puedes usar otro
int redAlert = 0;
int warningAlert = 0;
int greenWarning = 0;
int pingNumber = 4;
String localping;


//Objects
CTBot myBot; //Telegram bot object
TBMessage msg; // Object to get messages from Telegram Bot
SMTPSession smtp; //Object used SMTPSession for SMTP transport

void setup() {
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  pinMode(redLed,OUTPUT);
  pinMode(yellowLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  //Conexión modo STA
  WiFi.begin(SSID_STA, PASS_STA);
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP()); //Se obtiene la dirección IP del ESP32
  delay(1000);
  //myBot.wifiConnect(SSID_STA, PASS_STA);
  myBot.setTelegramToken(BOT_TOKEN);
  
}

//Ping tags
void pingTargets(){
  bool google = Ping.ping("www.google.com",pingNumber);
  bool telegram = Ping.ping("web.telegram.org",pingNumber);
  bool tbs = Ping.ping("www.tbs.co.jp",pingNumber);
  bool github = Ping.ping("github.com",pingNumber);
  bool mywebsite = Ping.ping("yoshiokeimakun.me",pingNumber);
  
  if(!google || !telegram ||!tbs || !github || !mywebsite){
    return;
  }
}

//Leds by number

String message(){
  
}
/*
void ledsAlert(){
  if
}
*/


//SMTP Logs

void sendingEmail(String messageIP){
  //Set the network reconnection option
  /** Enable the debug via Serial port
   * 0 for no debugging
   * 1 for basic level debugging
   *
   * Debug port can be changed via ESP_MAIL_DEFAULT_DEBUG_PORT in ESP_Mail_FS.h
   */
   smtp.debug(1);
   //Set the callback function to get the sending results
   smtp.callback(smtpCallback);
   //Declare the Session_Config for user defined session credentials
   ESP_Mail_Session session;
   //Set the session config
   session.server.host_name = SMTP_HOST;
   session.server.port = SMTP_PORT;
   session.login.email = AUTHOR_EMAIL;
   session.login.password = AUTHOR_PASS;
   /*
   * Set the NTP config time
   * For times east of the Prime Meridian use 0-12
   * For times west of the Prime Meridian add 12 to the offset.
   * Ex. American/Denver GMT would be -6. 6 + 12 = 18
   * See https://en.wikipedia.org/wiki/Time_zone for a list of the GMT/UTC timezone offsets
   */ 
   SMTP_Message message;
   message.sender.name = F("ESP IDS WARNING SECURITY LOGS");
   message.sender.email = AUTHOR_EMAIL;
   message.subject = F("SECURITY ALERT!!");
   message.addRecipient(F("John"), RECIPIENT_EMAIL);
   String textMsg = "ALERT.\nExcess traffic has been detected from IP"+(String)+"\nPlease review your intranet monitoring." ;
   message.text.content = textMsg.c_str();
   /** Set de caracteres para el texto:
   * us-ascii
   * utf-8
   * utf-7
   * The default value is utf-8
  */
   message.text.charSet = "us-ascii";  
   message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
     /** Priority of messaje
   * esp_mail_smtp_priority_high or 1
   * esp_mail_smtp_priority_normal or 3
   * esp_mail_smtp_priority_low or 5
   * The default value is esp_mail_smtp_priority_low
  */
   message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_high;
   

  /* Connect to the server */
  if (!smtp.connect(&session)){
    ESP_MAIL_PRINTF("Connection error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
    return;
  }
  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message)){
    ESP_MAIL_PRINTF("Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
  }
}
void smtpCallback(SMTP_Status status)
{
  /* Imprime los resultados del envio */
  if (status.success())
  {
    //Serial.println("----------------");
    ESP_MAIL_PRINTF("Mensajes enviados con éxito: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Mensajes no enviados por falla: %d\n", status.failedCount());
    //Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++)
    {
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Mensaje No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Estado: %s\n", result.completed ? "enviado" : "no enviado");
      ESP_MAIL_PRINTF("Fecha/Hora: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Destinatario: %s\n", result.recipients);
      ESP_MAIL_PRINTF("Asunto: %s\n", result.subject);
    }
    //Serial.println("----------------\n");

    //You need to clear sending result as the memory usage will grow up as it keeps the status, timstamp and
    //pointer to const char of recipients and subject that user assigned to the SMTP_Message object.

    //Because of pointer to const char that stores instead of dynamic string, the subject and recipients value can be
    //a garbage string (pointer points to undefind location) as SMTP_Message was declared as local variable or the value changed.

    //smtp.sendingResult.clear();
  }
}



//Telegram Bot
//logs messages
void logsMessages(String option){
  if(option == "/start"){
    String startMessage = "Hi, @"+(String)msg.sender.username+"\nThis bot alerts you about your traffic in your ESP32\nPlease, use command /options .";
    myBot.sendMessage(msg.sender.id,startMessage);
  }else if(option = "/options"){
    String opString  = "/options\t\t To show options\n/logs\t\t Show you  all number of logs\n/email\t\t Show you if any email has been sent.";
    myBot.sendMessage(msg.sender.id,opString);
  }
}


void telegramBotService(){
  if(myBot.getNewMessage(msg)){
    if(msg.messageType == CTBotMessageText){
      if(msg.text.equalsIgnoreCase("/start")){
        logsMessages(msg.text);
      }else if (msg.text.equalsIgnoreCase("/options")){
        logsMessages(msg.text);
      }
    }
  }
}




void loop() {
   // Espera a que un cliente se conecte
   telegramBotService();
   //message();
   pingTargets();
}
