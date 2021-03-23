void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      digitalWrite(13, HIGH);
      delay(i);
      digitalWrite(13, LOW);
      delay(10 - i);
    }
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      digitalWrite(13, LOW);
      delay(i);
      digitalWrite(13, HIGH);
      delay(10 - i);
    }
  }
}
