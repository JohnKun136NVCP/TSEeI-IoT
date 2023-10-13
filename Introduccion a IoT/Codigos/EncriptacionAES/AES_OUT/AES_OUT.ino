//Biblioteca
#include "mbedtls/aes.h" //Seeed_Arduino_mbedtls - Gestor de Librerías Arduino

void setup() {
  Serial.begin(115200);

  char *key = "Clase IoT 2024-1"; //Clave de 128 bits (16 bytes)
  unsigned char chipherText[16] = {87,32,210,226,161,101,98,106,6,40,86,245,242,242,149,254}; //Declaro variable de texto cifrado
  unsigned char outputBuffer[16]; //Búfer de salida (16 bytes)

  //Estructura para cifrar
  mbedtls_aes_context aes; //Variable de tipo estructura
  mbedtls_aes_init(&aes); //Incicializamos el método
  
  //Establecemos la clave de decifrado (tipo, clave, tamaño)
  mbedtls_aes_setkey_dec(&aes, (const unsigned char*) key, 128); 
  
  //Establecemos tipo de decifrado (tipo, operación, entrada, salida)
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer); 
  
  mbedtls_aes_free(&aes); //Terminamos el método

  Serial.println("\nTexto descifrado:"); //Imprime el texto decifrado
  for (int i = 0; i < 16; i++) {
    Serial.print((char)outputBuffer[i]);
  }
}

void loop() {}
