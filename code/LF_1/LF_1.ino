//Motor pins
int l1=14;
int l2=27;
int r1=15;
int r2=4;

//PWM pins
int enr=33;
int enl=32;

//IR pins
int ir1=22;
int ir2=17;
int ir3=3;
int ir4=21;
int a,b,c,d;


void setup()
{
pinMode(l1,OUTPUT);
pinMode(l2,OUTPUT);
pinMode(r1,OUTPUT);
pinMode(r2,OUTPUT);

pinMode(enr,OUTPUT);
pinMode(enl,OUTPUT);
                      //Motor speed
analogWrite(enr,230);
analogWrite(enl,235);

pinMode(ir1,INPUT);
pinMode(ir2,INPUT);
pinMode(ir3,INPUT);
pinMode(ir4,INPUT);
Serial.begin(9600);
rel();
delay(3000);
ST1();

}

void loop() 
{
}



//_________________________________________________________________________________________________________
//        FUNCTIONS




void ST2(){            //STATION 1
do{
lf();
}while(a==0);
}

void ST3(){            //STATION 2
do{
lf();
}while(d==0);
}


void ST1(){            //STATION 3
do{
lf();
}while(b==1||c==1);
}





void lf(){                           //Line follower 
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

if(b==1 && c==1){
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);     //FORWARD
digitalWrite(l1,HIGH);
digitalWrite(l2,LOW);
}

else if(b==0 && c==1){ 
digitalWrite(l1,HIGH);
digitalWrite(l2,LOW);      //TURNS RIGHT
digitalWrite(r1,LOW);
digitalWrite(r2,LOW);
}
else if(b==1 && c==0){
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);     //TURNS LEFT
digitalWrite(l1,LOW);
digitalWrite(l2,LOW);
}
else if(b==0 && c==0){
digitalWrite(r1,LOW);
digitalWrite(r2,LOW);      //DERAIL
digitalWrite(l1,LOW);
digitalWrite(l2,LOW);
}
}




void rel(){
digitalWrite(r1,LOW);
digitalWrite(r2,LOW);     
digitalWrite(l1,LOW);
digitalWrite(l2,LOW);
}

void turn(){
do{
a=digitalRead(ir4);
b=digitalRead(ir3);
c=digitalRead(ir2);
d=digitalRead(ir1);
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);     //turn
digitalWrite(l1,LOW);
digitalWrite(l2,HIGH);
}while(b==0 || c==0);
}


void turn1(){
do{
a=digitalRead(ir4);
b=digitalRead(ir3);
c=digitalRead(ir2);
d=digitalRead(ir1);
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);     //turn
digitalWrite(l1,LOW);
digitalWrite(l2,HIGH);
}while(b==0 || c==0 || a==1);
}


void turn0(){
do{
a=digitalRead(ir4);
b=digitalRead(ir3);
c=digitalRead(ir2);
d=digitalRead(ir1);
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);     //turn the bot at inventory
digitalWrite(l1,LOW);
digitalWrite(l2,HIGH);
}while(a==0 || b==0 || c==0 || d==0);
}

void turnx(){
do{
a=digitalRead(ir4);
b=digitalRead(ir3);
c=digitalRead(ir2);
d=digitalRead(ir1);
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);     //turn
digitalWrite(l1,LOW);
digitalWrite(l2,HIGH);
}while(b==0 || c==0 || a==0);
}