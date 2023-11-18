void idsLedUP(){ //Function to connect a server to send information as WI
  WiFiClient client = server.available(); //Check if a client's connected
  if (!client) {
    delay(10); 
    return;
  }
  while (client.connected()) {
    if (client.available()) {
      String request = client.readStringUntil('\n'); //Get 1,0 or -1 
      String message = client.readStringUntil('\r'); //Get length of packet
      Serial.print(request);
      Serial.print(",");
      Serial.println(message);
      if(request=="0"){//IDS traffic it's OK
        ok++; //Add counter to ok traffic
        digitalWrite(LED_1,HIGH);
        delay(1000);
        digitalWrite(LED_1,LOW);
      }
      else if (request=="1"){//IDS traffic, it's warning
        digitalWrite(LED_2,HIGH);
        delay(1000);
        digitalWrite(LED_2,LOW);
        warning++;//Add counter to warning traffic
        warningMessage = true;dangerMessage=false;
        senderMessageLog(warningMessage,dangerMessage); //Send logs to Telegram
      }else if(request=="-1"){ //IDS traffic, it's danger
        digitalWrite(LED_3,HIGH);
        delay(1000);
        digitalWrite(LED_3,LOW);
        danger++;//Add counter to danger traffic
        emailSender++; //Number of times that it's sent a message
        digitalWrite(Bzzer, HIGH);   // turn on the buzzer 
        delay(1000);                 // wait
        digitalWrite(Bzzer , LOW);  // turn off the buzzer
        warningMessage = false;dangerMessage=true;
        senderMessageLog(warningMessage,dangerMessage); //Sends DANGER alert
        sendingEmail(message);//Send a email
      }
      client.stop();
    }
    pingTargets();//Generate traffic
  }
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

//SMTP -> Sends emails. Check documentation on https://github.com/mobizt/ESP-Mail-Client
void sendingEmail(String messageIP){
   smtp.debug(1);
   smtp.callback(smtpCallback);
   ESP_Mail_Session session;
   session.server.host_name = SMTP_HOST;
   session.server.port = SMTP_PORT;
   session.login.email = AUTHOR_EMAIL;
   session.login.password = AUTHOR_PASS;
   SMTP_Message message;
   message.sender.name = F("ESP IDS WARNING SECURITY LOGS");
   message.sender.email = AUTHOR_EMAIL;
   message.subject = F("SECURITY ALERT!!");
   message.addRecipient(F("John"), RECIPIENT_EMAIL);
   String textMsg = "ALERT.\nExcess traffic has been detected from IP "+(String)messageIP+"\nPlease review your intranet monitoring." ;
   message.text.content = textMsg.c_str();
   message.text.charSet = "us-ascii";  
   message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
   message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_high;
  /* Connect to the server */
  if (!smtp.connect(&session)){
    //ESP_MAIL_PRINTF("Connection error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
    return;
  }
  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message)){
    //ESP_MAIL_PRINTF("Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
    return;
  }
}
void smtpCallback(SMTP_Status status)
{
  if (status.success())
  {
    struct tm dt;
    for (size_t i = 0; i < smtp.sendingResult.size(); i++)
    {
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);
    }
    smtp.sendingResult.clear();
  }
}

//Telegram Bots
//Options functions for Telegram bot
void logsMessages(String option){
  if(option == "/start"){ //Function Start
    String startMessage = "Hi, @"+(String)msg.sender.username+"\nThis bot alerts you about your traffic in your ESP32\nPlease, use command /options .";
    myBot.sendMessage(msg.sender.id,startMessage);
  }else if(option = "/options"){ //Function Options
    String opString  = "/options\t\t To show options\n/logs\t\t Show you  all number of logs\n/email\t\t Show you if any email has been sent.";
    myBot.sendMessage(msg.sender.id,opString);
  }
}
//Get number of logs
void logsCounter(){
  String logMessage = "You have number of logs by category:\nOk: "+(String)ok+"\nWarning: "+(String)warning+"\nDanger: "+(String)danger;
  myBot.sendMessage(msg.sender.id, logMessage);
  return;
}
//Get if an email has sent
void numberSendEmail(){
  String logEmail = "An email has sent "+(String)emailSender+" number of times";
  myBot.sendMessage(msg.sender.id, logEmail);
  return;
}
//Sends notifications to elegram
void senderMessageLog(bool warningMessage, bool dangerMessage){
  if((warningMessage==true) && (dangerMessage == false) &&(lostMessage == false)){
    String messageStatus = "WARNING! A suspicious packet was detected on your network";
    myBot.sendMessage(msg.sender.id, messageStatus);
  }else if ((warningMessage==false) && (dangerMessage == true) && (lostMessage == false)){
    String messageStatus = "DANGER! A issue packet was detected on your network";
    myBot.sendMessage(msg.sender.id, messageStatus);
  }else if  ((warningMessage==false) && (dangerMessage == false) && (lostMessage == true)){
    String messageStatus = "A package was lost while the IDS was working";
    myBot.sendMessage(msg.sender.id, messageStatus);
  }
}

//Telegram bot main

void telegramBotService(){
  if(myBot.getNewMessage(msg)){
    if(msg.messageType == CTBotMessageText){
      if(msg.text.equalsIgnoreCase("/start")){ //Start case
        logsMessages(msg.text);
      }else if (msg.text.equalsIgnoreCase("/options")){ //Options case
        logsMessages(msg.text);
      }else if (msg.text.equalsIgnoreCase("/logs")){ //Logs case
        logsCounter();
      }else if (msg.text.equalsIgnoreCase("/email")){//Email case
        numberSendEmail();
      }else{
        myBot.sendMessage(msg.sender.id, msg.text);//Error message
        myBot.sendMessage(msg.sender.id, "UPS! Try with: /options");
      }
    }
  }
}
