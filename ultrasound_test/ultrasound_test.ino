#define TRIGPIN 8
#define ECHOPIN 9
#define SOUNDPIN 10
#define CTM 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(SOUNDPIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int dur;
  float dis;
  
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(CTM);
  digitalWrite(TRIGPIN, LOW);
  dur = pulseIn(ECHOPIN, HIGH);
  dis = dur * 17.0 / 1000.0;
  Serial.print(dis);
  Serial.println("cm");

  if (dis > 0.0 && dis < 20.0) {
    analogWrite(SOUNDPIN, 127);
  } else if (dis >= 20.0) {
    analogWrite(SOUNDPIN, 0);
  }
  delay(100);
}
