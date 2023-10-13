/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por: M. en I. Valente Vázquez Velázquez
  Última modificación: 20-abril-2023
  https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

#include "CTBot.h" // Incluye la biblioteca CTBot para interactuar con la API de Telegram.

#define pinPhoto 34 // Define el número de pin al que está conectada la fotorresistencia.
#define pinLED 14   // Define el número de pin al que está conectado el LED.

CTBot myBot; // Crea un objeto para interactuar con el bot de Telegram.

// Detalles de la red Wi-Fi y el token de autenticación del bot de Telegram.
String ssid = "#####";  // Reemplazar con tu SSID de Wi-Fi.
String pass = "######"; // Reemplazar con tu contraseña de Wi-Fi.
String token = "########"; // Reemplazar con el token de tu bot de Telegram. 

void setup() {
  Serial.begin(115200); // Inicia la comunicación serial.
  Serial.print("Comenzando TelegramBot...  ");
  pinMode(pinPhoto, INPUT); // Configura el pin del sensor como entrada.
  pinMode(pinLED, OUTPUT);  // Configura el pin del LED como salida.
  digitalWrite(pinLED, LOW); // Inicializa el LED en estado apagado.
  
  myBot.wifiConnect(ssid, pass); // Conecta a la red Wi-Fi especificada.
  myBot.setTelegramToken(token); // Establece el token de autenticación para el bot de Telegram.
  delay(2000); // Espera un momento para que la conexión se establezca.

  // Verifica si la conexión con el bot de Telegram se ha establecido correctamente.
  if (myBot.testConnection())
    Serial.println("Conectado con Bot");
  else
    Serial.println("Error en la conexión");
}

void loop() {
  TBMessage msg; // Crea un objeto para almacenar los mensajes entrantes de Telegram.

  // Verifica si hay un nuevo mensaje para el bot de Telegram.
  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("/start")) {
      // Si el comando es "/start", responde con un mensaje de bienvenida e instrucciones.
      Serial.print("Nueva interacción de: ");
      Serial.println(msg.sender.username);
      myBot.sendMessage(msg.sender.id, "Hola, por favor envía /Dato para monitorear la variable, 1 para encender un LED o 0 para apagarlo.");
    } 
    else if (msg.text.equalsIgnoreCase("/Dato")) {
      // Si el comando es "/Dato", envía el valor actual del sensor al usuario.
      Serial.print("Monitoreo: ");
      int sensor1 = analogRead(pinPhoto); // Lee el valor actual del sensor.
      Serial.println(sensor1); // Imprime el valor del sensor en el monitor serial.
      String mensaje1 = (String)"El valor actual es: " + (String)sensor1;
      myBot.sendMessage(msg.sender.id, mensaje1); // Envía el valor del sensor al chat de Telegram.
      Serial.println("Dato enviado");
    }
    else if (msg.text.equalsIgnoreCase("1")) {
      // Si el mensaje es "1", enciende el LED.
      digitalWrite(pinLED, HIGH); // Enciende el LED.
      Serial.println("Led ON");
      String mensaje1 = "Led encendido";
      myBot.sendMessage(msg.sender.id, mensaje1); // Notifica al usuario que el LED está encendido.
    }
    else if (msg.text.equalsIgnoreCase("0")) {
      // Si el mensaje es "0", apaga el LED.
      digitalWrite(pinLED, LOW); // Apaga el LED.
      Serial.println("Led OFF");
      String mensaje1 = "Led apagado";
      myBot.sendMessage(msg.sender.id, mensaje1); // Notifica al usuario que el LED está apagado.
    }
    else {
      // Si el mensaje recibido no coincide con ninguno de los comandos anteriores, envía un mensaje de error.
      myBot.sendMessage(msg.sender.id, "Mensaje no válido, intenta de nuevo con: /start");
    }
  }  
  delay(50); 
}
