int l1=14;
int l2=27;
int r1=33;
int r2=32;

//PWM pins
int enr=21;
int enl=32;

void setup() {
pinMode(l1,OUTPUT);
pinMode(l2,OUTPUT);
pinMode(r1,OUTPUT);
pinMode(r2,OUTPUT);

pinMode(enr,OUTPUT);
pinMode(enl,OUTPUT);

analogWrite(enr,255);
// analogWrite(enl,255);
}

void loop() {
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);
digitalWrite(l1,HIGH);
digitalWrite(l2,LOW);





}
