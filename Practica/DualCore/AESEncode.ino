#include "mbedtls/aes.h"
 
void setup() {
 
  Serial.begin(115200);
 
  mbedtls_aes_context aes;
 
  char * key = "abcdefghijklmnop";
 
  char *input = "My Teen Romantic Comedy SNAFU";
  unsigned char output[30];
 
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)input, output);
  mbedtls_aes_free( &aes );
  Serial.println("Texto cifrado: ");
  
  for (int i = 0; i < 16; i++) {
 
    char str[3];
 
    sprintf(str, "%02x", (int)output[i]);
    Serial.print(str);
  }
  Serial.println("\n");
  Serial.println("Texto descifrado");
  Serial.println(input);
}
 
void loop() {}
