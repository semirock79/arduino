#include <SPI.h>

#define CS_PIN 10

void setup() {
  // put your setup code here, to run once:
  pinMode(CS_PIN, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  digitalWrite(CS_PIN, HIGH);
  Serial.begin(38400);
  SPI.begin();
//  SPI.setClockDivider(SPI_CLOCK_DIV128);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(CS_PIN, LOW);
  byte val1 = SPI.transfer(0xC0);
  byte val2 = SPI.transfer(0x00);
//  Serial.print("val1:0x");
//  Serial.println(val1, HEX);
//  Serial.print("val2:0x");
//  Serial.println(val2, HEX);
  digitalWrite(CS_PIN, HIGH);
  delay(1);

//  digitalWrite(CS_PIN, LOW);
//  SPI.transfer(0xFF);
  Serial.println(analogRead(5));
  static bool flag = false;
  if (!flag) {
    analogWrite(6, 254);
    flag = true;
  }
  
  Serial.print("pulse width:");
  Serial.println(pulseIn(5, HIGH));
  Serial.print("read:");
  Serial.println(analogRead(5));
//  digitalWrite(CS_PIN, HIGH);
  delay(1);

  delay(1000);
}
