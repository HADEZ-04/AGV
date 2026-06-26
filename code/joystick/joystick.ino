
 int x=35;
 int y=33;
 int s=15;
 void setup() {
pinMode(x,INPUT);
pinMode(y,INPUT);
pinMode(s,INPUT);

pinMode(s,INPUT_PULLUP);
Serial.begin(115200);
}

void loop() {
Serial.print(analogRead(x));
Serial.print("\t");
Serial.print(analogRead(y));
Serial.print("\t");
Serial.println(digitalRead(s));
}

