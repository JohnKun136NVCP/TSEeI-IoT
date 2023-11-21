#include "CTBot.h" // Incluye la biblioteca CTBot para interactuar con la API de Telegram.
#include "Credentials.h" //En un archivo por aparte escribe las credenciales (SSID,PASWORD,BOTTOKEN)

#define pinPhoto 34 //Pin para la fotoresistencia
#define pinPOT 35 //PIn para la potencia 
#define LED 2 //Se define el led 2 como salida
const int leds[5] = {14, 27, 26, 25, 33}; // Se define los leds para salida
bool stateVoltage = false; //Estado del voltaje por default
bool callback = false;//Estado del callback por default antes de ser llamada
bool state = false;//Estado de la alarma por default
int umbral = 200;//Estado del umbral por defecto
int defaultVal = 200; //Variable auxiliar para saber si hubo cambios en el umbral original
double setPoint; //Punto para establecer el voltaje
int id = 0;// Variable para almacenar el ID del chat de Telegram desde el que se activó la alarma.
int valint; //Variable auxiliar para str en ingreso de valores

CTBot myBot; //Objeto tipo bot
TBMessage msg; //Objeto donde recibira los mensajes del Telegram del Bot


void setup() {
  Serial.begin(115200); // Inicia la comunicación serial.
  Serial.print("Comenzando TelegramBot...  "); // Se lanza mensaje para la comunicacion con el bot
  //Inicializar los leds para salida 
  for (int i = 0; i <=4; i++){
    pinMode(leds[i], OUTPUT);
  }
  pinMode(LED,OUTPUT);
  pinMode(pinPhoto, INPUT); // Configura el pin del sensor como entrada.
  pinMode(pinPOT, INPUT);
  myBot.wifiConnect(SSID, PASSWORD); // Conecta a la red Wi-Fi especificada.
  myBot.setTelegramToken(TOKEN); // Establece el token de autenticación para el bot de Telegram.+
  delay(2000); // Espera un momento para que la conexión se establezca.
  // Verifica si la conexión con el bot de Telegram se ha establecido correctamente.
  if (myBot.testConnection()){ //Se hace el test de conexicion para de WIFI
    Serial.println("Conectado con Bot"); //Si pasa el este envia el log que se establecion la conexicion
  }else{
    Serial.println("Error en la conexión"); //En el caso contrario se envia el mensaje que hubo un error
  }
}

//DOCUMENTACION O AYUDA PARA USUARIO
void logsMensajes(String option){ //Mensajes segun la opcion aparente.
     if(option == "/start"){ //Si empieza con el comando start 
        //Breve explicacion de que hace el bot  definiendo la variable del mensaje
        String startString = "Hola,@"+(String)msg.sender.username+"!\nEste bot puede intecturar usando leds prendiendo y apagando, monitorear el voltaje y ejecutar una alarma dado un umbral que me proporciones.\nPara ver las opciones, por favor, usa el comando /opciones";
        //Envia el mensaje al usuario
        myBot.sendMessage(msg.sender.id,startString);
     }else if (option == "/opciones"){ //Si empieza con el comando opciones 
        //Breve explicacion de las opciones del bot  definiendo la variable del mensaje
        String optString = "Los comandos disponibles para este bot son los siguientes:\n/opciones\tMostrar el menu de opciones\n/helpleds\tAyuda en el comando de los leds\n/fotores\t Opciones disponibles para la alarma y fotoresistencia\n/poltstatus\t Opciones de monitoreo de voltaje ";
        //Envia el mensaje al usuario
        myBot.sendMessage(msg.sender.id,optString);
     }else if (option == "/helpleds"){//Si empieza con el comando helpleds 
        //Envia al mensaje al usuario de lo que hace cada comando mediante un mensaje escalonado
        for(int i = 0;i<5;i++){
            int lednum = i+1;
            String helpString = "/led"+(String)lednum+"\t Apagar o Encender el Led "+(String)lednum;
            myBot.sendMessage(msg.sender.id,helpString);
        }
        //Envia el mensaje al usuario del comando /ledall
        myBot.sendMessage(msg.sender.id,"/ledall\t Apagar o Encender todos los leds");
        //Envia el mensaje al usuario del comando de ayuda para los leds
        myBot.sendMessage(msg.sender.id,"/helpleds\t Muestra nuevamente el menú");
     }else if (option == "/fotores"){//Si empieza con el comando fotores 
        //Breve explicacion de las opciones de la alarma  definiendo la variable del mensaje
        String fotoString = "Comandos disponibles en fotoresistencia son:\n /changeinterval numero(int)\t Cambia el umbral (por defecto 200) por un numero entero que le asignemos\n/alarmUp\t Activa la alarma\n/alarmDown\t Desactiva la alarma\n/alarmStatus\t Da los parametros generales de la alarma\n/fotores\t Muestra los comandos disponibles";
        //Envia el mensaje al usuario
        myBot.sendMessage(msg.sender.id,fotoString);
     }else if (option == "/poltstatus"){//Si empieza con el comando poltstatus 
        //Breve explicacion del voltaje enviando el mensaje en una variable
        String voltString = " /upvlt\t Inicial el monitoreo del voltaje\n/poltstatus\t Muestra nuevamente este menú";
        myBot.sendMessage(msg.sender.id,voltString);//Envia el mensaje al usuario
     }
}

//FUNCIONALIDADES GENERALES DEL BOT
//Encender o apagar leds segun la opcion, si es todos 
void ledsinput(int estado, int nled){
    if(nled<5){ //Si el arreglo del led es menor que 5
        if(estado!= HIGH){ //Si esta apagado
            int lednum = nled+1; //Contador para string
            String advertencia = (String)"Encendiendo led:  " + (String)lednum; //Almacena el mensaje del led que va encender
            delay(1000); //Espera de un segundo
            digitalWrite(leds[nled],HIGH); //Enciende el led
            myBot.sendMessage(msg.sender.id, advertencia); //Envia el mensaje al usuario  
        }else if(estado!=LOW){//Si esta encendido
            int lednum = nled+1;//Contador para string
            String advertencia = (String)"Apagando led: " + (String)lednum;//Almacena el mensaje del led que va encender
            delay(1000);//Espera de un segundo
            digitalWrite(leds[nled],LOW);//Apaga el led
            myBot.sendMessage(msg.sender.id, advertencia); //Envia el mensaje al usuario  
        }
    }else if(nled == 5){ //Si van a encender o apagar todos los leds (dependiendo su estado en que se encuentren)
        for(int i = 0;i<5;i++){
            int val = digitalRead(leds[i]);
            if(val == LOW){//Si esta apagado
                int lednum = i + 1;//Contador para string
                String advertencia = (String)"Encendiendo led:  " + (String)lednum;//Almacena el mensaje del led que va encender
                myBot.sendMessage(msg.sender.id, advertencia);//Envia el mensaje al usuario 
                delay(1000);//Espera de un segundo
                digitalWrite(leds[i],HIGH); //Enciende el led que esta apagado (uno por uno)     
              }else{
                int lednum = i+1;
                String warning = (String)"Apagando led: " + (String)lednum;
                myBot.sendMessage(msg.sender.id, warning);
                delay(1000);
                digitalWrite(leds[i],LOW); 
              }        
         }
        myBot.sendMessage(msg.sender.id, "Todos los leds se han apagado/encendido");//Envia el mensaje al usuario              
    }
}

//Administracion de voltaje
void voltTimeStatus(bool statusV){ //Recibe un valor de status de voltaje 
    if(statusV){ //Si es verdaddero
            setPoint = analogRead(pinPOT) * (3.3 / 4096.0); //Se lee el voltaje del pot para el setpoint
            String voltstat = (String)"El voltaje actual es de: "+(String)setPoint; //Va imprimiendo el voltaje cada ciclo y lo almacena 
            digitalWrite(LED,HIGH); //Prende un led
            delay(1500); //Espera segundo y medio
            myBot.sendMessage(msg.sender.id,voltstat); //Envia mensaje al usuario del monitoreo del voltaje
            delay(1500); // Espera segundo y medio
            digitalWrite(LED,LOW);// Apaga el led
    }else{
        myBot.sendMessage(msg.sender.id,"El monitoreo está inactivo o se desactivo"); //Si es falso el estado entonces apaga envia un mensaje al usuario
    }
}

//Administracion del umbral
//Si se llamo a la funcion para cambiar el umbral y regresar un valor a callback 
bool isThreshold(bool call){
    if(call){
        return true;
    }else{
        return false;
    }
}

//Alarma encendida
void alarmisUp(){
    state = true; //Vuelve a un estado verdadero
    int sensor = analogRead(pinPhoto); // Lee el valor actual del sensor.
    id = msg.sender.id; //Se obtiene su id del usuario
    String mensaje = "Alarma activada"; //Mensaje de la alarma activada
    myBot.sendMessage(msg.sender.id, mensaje); //Envia mensaje al usuario
    Serial.println(mensaje); //Imprime el mensaje en el serial.
}


//Ver si la alarma esta encendida
void alarmisDown(){
    state = false; //Pone a un estado falso y cambia los valores
    id = msg.sender.id; // Obtiene el id del usuario
    String mensaje = "Alarma desactivada"; //Genera el mensaje.
    myBot.sendMessage(msg.sender.id, mensaje); //Envia el mensaje al usuario
    Serial.println(mensaje);//Imprime el mensaje en consola
    id = 0; // Restablece el ID del chat ya que la alarma está desactivado
}


void alarmStatus(){
    //Default values
    if((state==true) && (umbral==defaultVal)){
        String mensaje = "Estatus de la alarma:\nPrendida: "+(String)state+"\n Valor de umbral(Default): "+(String)umbral; //Verifica con un valor true y con el default de los valores iniciales
        myBot.sendMessage(msg.sender.id,mensaje);//Envia mensaje al usuario
    }else if((state==true) && (umbral!=defaultVal)){
        String mensaje = "Estatus de la alarma:\nPrendida: "+(String)state+"\n Valor de umbral(Modificado): "+(String)umbral;//Verifica con un valor true y con el default de los valores distinto al umbral
        myBot.sendMessage(msg.sender.id,mensaje);//Envia mensaje al usuario        
    }else if((state==false) && (umbral==defaultVal)){
        String mensaje = "Estatus de la alarma:\nPrendida: "+(String)state+"\n Valor de umbral(Default): "+(String)umbral;//Verifica con un valor false y con el default de los valores inicial
        myBot.sendMessage(msg.sender.id,mensaje);//Envia mensaje al usuario        
    }else if((state==false) && (umbral!=defaultVal)){
        String mensaje = "Estatus de la alarma:\nPrendida: "+(String)state+"\n Valor de umbral(Modificado): "+(String)umbral;//Verifica con un valor false y con el default de los valores distinto al umbral
        myBot.sendMessage(msg.sender.id,mensaje);//Envia mensaje al usuario        
    }
}



void loop() {
  int sensor = analogRead(pinPhoto);
  Serial.println(sensor);
  // Verifica si hay un nuevo mensaje para el bot de Telegram.
  if (myBot.getNewMessage(msg)) {
    if(msg.messageType == CTBotMessageText){ //Si el mensaje es texto
      if (msg.text.equalsIgnoreCase("/start")) { //Inicia el comando start
        logsMensajes(msg.text); //Envia mensaje de la funcion logs
      }else if (msg.text.equalsIgnoreCase("/opciones")){ //Inicia el comando opciones
        logsMensajes(msg.text);//Envia mensaje de la funcion logs
      }else if (msg.text.equalsIgnoreCase("/fotores")){//Inicia el comando fotores
        logsMensajes(msg.text);//Envia mensaje de la funcion logs
      }else if (msg.text.equalsIgnoreCase("/poltstatus")){//Inicia el comando poltstatus
        logsMensajes(msg.text);//Envia mensaje de la funcion logs
      }else if (msg.text.equalsIgnoreCase("/helpleds")){//Inicia el comando helpleds
        logsMensajes(msg.text);//Envia mensaje de la funcion logs    
      }else if(msg.text.equalsIgnoreCase("/led1")){//Inicia el comando led1
        int val = digitalRead(leds[0]);//Recibe el primer led
        ledsinput(val, 0); //Aplica funcion para los leds definda arriba
      }else if(msg.text.equalsIgnoreCase("/led2")){//Inicia el comando led2
        int val = digitalRead(leds[1]);//Recibe el segundo led
        ledsinput(val, 1);//Aplica funcion para los leds definda arriba
      }else if(msg.text.equalsIgnoreCase("/led3")){//Inicia el comando led3
        int val = digitalRead(leds[2]);//Recibe el tercero led
        ledsinput(val, 2);//Aplica funcion para los leds definda arriba
      }else if(msg.text.equalsIgnoreCase("/led4")){//Inicia el comando led4
        int val = digitalRead(leds[3]);//Recibe el cuarto led
        ledsinput(val, 3);//Aplica funcion para los leds definda arriba
      }else if(msg.text.equalsIgnoreCase("/led5")){//Inicia el comando led5
        int val = digitalRead(leds[4]);//Recibe el quinto led
        ledsinput(val, 4);//Aplica funcion para los leds definda arriba
      }else if(msg.text.equalsIgnoreCase("/ledall")){//Inicia el comando ledall
          ledsinput(0, 5);//Aplica funcion para los leds definda arriba
      }else if (msg.text.equalsIgnoreCase("/upvlt")){//Inicia el comando upvlt
          myBot.sendMessage(msg.sender.id,"Monitoreo activado"); //Envia mensaje
          stateVoltage = true; //Cambia el estado del voltaje
          voltTimeStatus(stateVoltage); //Aplica funcion para los voltaje definda arriba
      }else if(msg.text.equalsIgnoreCase("/changeinterval "+(String)msg.text.substring(16))){//Inicia el comando changeinterval
        callback = true;//Cambia el estado de llamada
        if(isThreshold(callback)){ //Si es verdadero entonces
            umbral = msg.text.substring(16).toInt(); //Cambia el valor del umbral de str a int
        }
        myBot.sendMessage(msg.sender.id, "El valor del umbral ha cambiado exitosamente a "+(String)umbral);//Envia mensaje
      }else if(msg.text.equalsIgnoreCase("/alarmUp")){//Inicia el comando alarmUp
        alarmisUp();//Aplica funcion para la alarma definda arriba
      }else if(msg.text.equalsIgnoreCase("/alarmDown")){//Inicia el comando alarmDown
        alarmisDown();//Aplica funcion para la alarma definda arriba
      }else if(msg.text.equalsIgnoreCase("/alarmStatus")){//Inicia el comando alarmStatus
        alarmStatus();//Aplica funcion para la alarma definda arriba
      }else {
        // Si el mensaje recibido no coincide con ninguno de los comandos anteriores, envía un mensaje de error.
        myBot.sendMessage(msg.sender.id, msg.text);//Reenvia el mensaje que tecleo por accidente y despues salta el error
        myBot.sendMessage(msg.sender.id, "Mensaje no válido, intenta de nuevo con: /opciones");
      }
    }
  }
    if ((state == true) && (sensor > umbral)){
    Serial.println(sensor);
    String mensaje = "¡¡ALERTA!! El nivel aumentó a: "+(String)sensor;
    myBot.sendMessage(msg.sender.id, mensaje);
    }
  delay(50);//Un delay para cada instruccion 
}
