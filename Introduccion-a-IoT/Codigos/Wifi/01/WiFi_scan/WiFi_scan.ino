/*
 *Universidad Nacional Autónoma de México
 *Facultad de Ciencias
 *Licenciatura en Ciencias de la Computación
 *Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas
 *
 *Escrito por: M. en I. Valente Vázquez Velázquez
 *Última modificación: 1-enero-2023
 *https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

//Biblioteca WiFi
#include "WiFi.h"

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA); //Modo estación
  WiFi.disconnect(); //Desconectar del modo AP (por si estaba conectado)
  delay(100);
  Serial.println("WiFi en modo estación establecido");
}

void loop() {
  Serial.println("Comenzando escaneo de redes WiFi...");
  int n = WiFi.scanNetworks(); //Regresa el número de redes WiFi encontradas
  Serial.print("Escaneo terminado, ");

  if (n == 0) {
    Serial.println("no se encontraron redes WiFi.");
  }
  else {
    Serial.print(n);
    Serial.println(" redes WiFi encontradas:");
    for (int i = 0; i < n; ++i) {
      //Imprimir las redes encontradas
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i)); //Nombre de la red
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i)); //Potencia de la red
      Serial.print(")");
      // Escribir open si la red no tiene credenciales
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "--open--" : " ");
      delay(10);
    }
  }
  Serial.println("");
  delay(10000);
}
