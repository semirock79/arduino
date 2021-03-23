void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int light = analogRead(A0);
  int led = (int)(256 * light / 1024);
  if (light < 800) {
    analogWrite(3, 255);
  } else {
    analogWrite(3, 0);
  }
  delay(100);
}
