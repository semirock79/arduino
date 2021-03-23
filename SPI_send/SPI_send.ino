#include <SPI.h>

#define INT_PIN 3
#define SS_PIN 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setDataMode(SPI_MODE0);
}

void loop() {
  // put your main code here, to run repeatedly:
  static char _buf[5] = "hello";
  
  digitalWrite(SS_PIN, LOW);
  for (int i = 0; i < sizeof(_buf); i++) {
    SPI.transfer(_buf[i]);
    delay(5);
  }
  digitalWrite(SS_PIN, HIGH);
  delay(2000);
}
