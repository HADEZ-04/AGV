int l1=14;
int l2=27;
int r1=15;
int r2=4;

//PWM pins
int enr=33;
int enl=32;

int ir1=22;
int ir2=17;
int ir3=3;
int ir4=21;
int a,b,c,d;
void setup() {
pinMode(l1,OUTPUT);
pinMode(l2,OUTPUT);
pinMode(r1,OUTPUT);
pinMode(r2,OUTPUT);

pinMode(enr,OUTPUT);
pinMode(enl,OUTPUT);

analogWrite(enr,249);
analogWrite(enl,255);

pinMode(ir1,INPUT);
pinMode(ir2,INPUT);
pinMode(ir3,INPUT);
pinMode(ir4,INPUT);
Serial.begin(9600);

Serial.begin(9600);
}
void loop() {
a=digitalRead(ir4);
b=digitalRead(ir3);
c=digitalRead(ir2);
d=digitalRead(ir1);

Serial.print(a);
Serial.print("   _  ");
Serial.print(b);
Serial.print("   _  ");
Serial.print(c);
Serial.print("   _  ");
Serial.println(d);
}
