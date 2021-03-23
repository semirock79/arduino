void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println((1023 - analogRead(A0)) / 1023.0 * 10000);
  Serial.println(map(analogRead(A0), 1023.0, 0.0, 0.0, 10000));
  delay(1000);
}
