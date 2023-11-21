/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por: M. en I. Valente Vázquez Velázquez
  Última modificación: 20-abril-2023
  https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
*/

//Biblioteca
#include "mbedtls/aes.h" //Seeed_Arduino_mbedtls - Gestor de Librerías Arduino

void setup() {
  Serial.begin(115200);

  //1 char = 1 byte
  char *key = "Clase IoT 2024-1"; //Clave de 128 bits (16 bytes)  
  char *input = "Hola, grupo IoT!"; //Texto a cifrar (16 bytes)
  unsigned char chipherText[16]; //Búfer de salida (16 bytes)

  //Estructura para cifrar
  mbedtls_aes_context aes; //Variable de tipo estructura
  mbedtls_aes_init(&aes); //Incicializamos el método
  
  //Establecemos la clave de cifrado (tipo, clave, tamaño)
  mbedtls_aes_setkey_enc(&aes, (const unsigned char*)key, 128);
  
  //Establecemos tipo de cifrado (tipo, operación, entrada, salida)
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)input, chipherText);
  
  mbedtls_aes_free(&aes); //Terminamos el método

  Serial.println("\nTexto cifrado:"); //Imprime el texto cifrado
  for (int i = 0; i < 16; i++) {
    Serial.print(chipherText[i]);
    Serial.print(","); //Se imprimen con comas por facilidad de identificación
  }
}

void loop() {}
