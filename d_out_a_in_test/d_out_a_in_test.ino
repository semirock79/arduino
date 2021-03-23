void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(2, HIGH);
  Serial.print("HIGH:");
  Serial.println(analogRead(A0));
  delay(1000);
//  digitalWrite(2, LOW);
//  Serial.print("LOW:");
//  Serial.println(analogRead(A0));
//  delay(1000);
}
