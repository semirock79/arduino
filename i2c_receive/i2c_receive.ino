#include <Wire.h>

#define SLAVE_1 0x01

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(SLAVE_1);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void receiveEvent(int numByte) {
  Serial.print("received byte:");
  Serial.println(numByte);

  while (1 < Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }

  byte x = Wire.read();
  Serial.println(x);
}

void requestEvent() {
  Wire.write("bye");
}
