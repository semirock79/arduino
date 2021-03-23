#include<SPI.h>

#define MAX_CLOCK_SPEED 8UL * 1000UL * 1000UL

SPISettings settings(MAX_CLOCK_SPEED, MSBFIRST, SPI_MODE0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  byte data;
  SPI.beginTransaction(settings);
  data = SPI.transfer(0x00);
  SPI.endTransaction();
  Serial.println(data);
  delay(1000);
}
