void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(9, 255 / 2);
  delay(1000);
  analogWrite(9, 0);
  delay(1000);
}
