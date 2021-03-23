#include <Wire.h>

#define SLAVE_1 0x01

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(SLAVE_1);
  Wire.write("good");
  Wire.write(0x02);
  Wire.endTransmission();

  delay(1000);

  Wire.requestFrom(SLAVE_1, 3);
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println("");
}
