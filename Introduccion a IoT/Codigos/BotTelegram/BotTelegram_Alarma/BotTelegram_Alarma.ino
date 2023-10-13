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

CTBot myBot; // Crea un objeto para interactuar con el bot de Telegram.

// Detalles de la red Wi-Fi y el token de autenticación del bot de Telegram.
String ssid = "#####";  // Reemplazar con tu SSID de Wi-Fi.
String pass = "######"; // Reemplazar con tu contraseña de Wi-Fi.
String token = "########"; // Reemplazar con el token de tu bot de Telegram. 

boolean state = false; // Variable para rastrear si la alarma está activada o desactivada.
int umbral = 3000; // Define el umbral sobre el cual se activará la alarma.
int id = 0; // Variable para almacenar el ID del chat de Telegram desde el que se activó la alarma.

void setup() {
  Serial.begin(115200); // Inicia la comunicación serial.
  Serial.println("Comenzando TelegramBot..."); 
  pinMode(pinPhoto, INPUT); // Configura el pin del sensor como entrada.
  
  myBot.wifiConnect(ssid, pass); // Conecta a la red Wi-Fi especificada.
  myBot.setTelegramToken(token); // Establece el token de autenticación para el bot de Telegram.
  delay(2000); // Espera un momento para que la conexión se establezca.

  // Verifica si la conexión con el bot de Telegram se ha establecido correctamente.
  if (myBot.testConnection())
    Serial.println("Conectado con Bot");
  else
    Serial.println("Error en la conexión");
}

void loop(){
  TBMessage msg; // Crea un objeto para almacenar los mensajes entrantes de Telegram.
  int sensor = analogRead(pinPhoto); // Lee el valor actual del sensor.
  Serial.println(sensor); // Imprime el valor del sensor en el monitor serial.
  
  // Verifica si hay un nuevo mensaje para el bot de Telegram.
  if (myBot.getNewMessage(msg)) {   
    if (msg.text.equalsIgnoreCase("/start")){
      // Si el comando es "/start", responde con un mensaje de bienvenida e instrucciones.
      Serial.print("Nueva interacción de: ");
      Serial.println(msg.sender.username);
      myBot.sendMessage(msg.sender.id, "Hola, por favor envía /Dato para monitorear la variable, /Alarma si deseas activar una alarma o /Alto si deseas desactivar esta última");
    }
    else if (msg.text.equalsIgnoreCase("/Dato")){
      // Si el comando es "/Dato", envía el valor actual del sensor al usuario.
      Serial.print("Monitoreo: ");
      Serial.println(sensor);
      String mensaje = (String)"El valor actual es: " + (String)sensor;
      myBot.sendMessage(msg.sender.id, mensaje);
      Serial.println("Dato enviado");
    }
    else if (msg.text.equalsIgnoreCase("/Alarma")){
      // Si el comando es "/Alarma", activa la alarma y guarda el ID del chat.
      state = true;
      id = msg.sender.id;
      String mensaje = "Alarma activada";
      myBot.sendMessage(msg.sender.id, mensaje);
      Serial.println(mensaje);
    }
    else if (msg.text.equalsIgnoreCase("/Alto")){
      // Si el comando es "/Alto", desactiva la alarma.
      state = false;
      id = msg.sender.id;
      String mensaje = "Alarma desactivada";
      myBot.sendMessage(msg.sender.id, mensaje);
      Serial.println(mensaje);
      id = 0; // Restablece el ID del chat ya que la alarma está desactivada.
    }
    else{
      // Si el mensaje recibido no coincide con ninguno de los comandos anteriores, envía un mensaje de error.
      String mensaje1 = "Mensaje no válido, intenta de nuevo con: /start";
      myBot.sendMessage(msg.sender.id, mensaje1);
      Serial.println(mensaje1);
    }
  }
  
  // Si la alarma está activada y el valor del sensor supera el umbral, envía una alerta al usuario.
  if ((state == true) && (sensor > umbral)){
    Serial.println(sensor);
    //Serial.println(id);
    String mensaje = "¡¡ALERTA!! El nivel aumentó a: "+(String)sensor;
    myBot.sendMessage(id, mensaje);
  }
  
  delay(50);
}
