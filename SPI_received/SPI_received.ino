#include <SPI.h>

#define INT_PIN 3
#define SS_PIN 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
  
  SPI.begin();
  
  SPCR |= _BV(SPIE);
  SPCR != _BV(SPE);
  SPCR &= ~_BV(MSTR);

  SPI.setClockDivider(SPI_CLOCK_DIV4);
}

ISR (SPI_STC_vect) {
  byte data = SPDR;
  Serial.print("data:");
  Serial.println(char(data));
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}
