//Bibliotecas
cont int PIN_LED = 32;

#include <SD.h>
#include <sd_diskio.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;
File readings;
char payload[120];

void setup() {
  Serial.begin(115200);
  bmp.begin(0x75);
  SD.begin();
  read_me = SD.open('/README.txt',FILE_WRITE);
  read_me.print("Archivo de lecturas del sensor BMP280,\n"
                "Tem","Press");
  read_me.close();


}
void loop() {

  sprintf(payload, "%0.2f,0.2f",bmp.readTemperature(),bmp.readPressure());
  Serial.println(payload);
  digitalWrite(PIN_LED,HIGH);
    readings = SD.open("/readings.csv",APPEND);
    readings.println(payload);
    readings.close();
  digitalWrite(PIN_LED,LOW);
  delay(500);
}
