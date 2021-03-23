void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);
  float temp = val / 1023.0 * 5.0 * 100.0;
  Serial.print("temperature:");
  Serial.println(temp);
  delay(1000);
}
