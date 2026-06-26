/**
   ESPNOW - Basic communication - Slave
   Date: 26th September 2017
   Author: Arvind Ravulavaru <https://github.com/arvindr21>
   Purpose: ESPNow Communication between a Master ESP32 and a Slave ESP32
   Description: This sketch consists of the code for the Slave module.
   Resources: (A bit outdated)
   a. https://espressif.com/sites/default/files/documentation/esp-now_user_guide_en.pdf
   b. http://www.esploradores.com/practica-6-conexion-esp-now/

   << This Device Slave >>

   Flow: Master
   Step 1 : ESPNow Init on Master and set it in STA mode
   Step 2 : Start scanning for Slave ESP32 (we have added a prefix of `slave` to the SSID of slave for an easy setup)
   Step 3 : Once found, add Slave as peer
   Step 4 : Register for send callback
   Step 5 : Start Transmitting data from Master to Slave

   Flow: Slave
   Step 1 : ESPNow Init on Slave
   Step 2 : Update the SSID of Slave with a prefix of `slave`
   Step 3 : Set Slave in AP mode
   Step 4 : Register for receive callback and wait for data
   Step 5 : Once data arrives, print it in the serial monitor

   Note: Master and Slave have been defined to easily understand the setup.
         Based on the ESPNOW API, there is no concept of Master and Slave.
         Any devices can act as master or salve.
*/

#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1

//MOTOR pins
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

//STATIONS
void ST1(){            //STATION 1
do{
lf();
}while(b==1||c==1);
}
void ST2(){            //STATION 2
do{
lf();
}while(a==0);
}
void ST3(){            //STATION 3
do{
lf();
}while(d==0);
}


//Line follower 
void lf(){                           
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
}}


void rel(){
digitalWrite(r1,LOW);
digitalWrite(r2,LOW);     
digitalWrite(l1,LOW);
digitalWrite(l2,LOW);
delay(1000);
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

void turn1(){
do{
a=digitalRead(ir4);
b=digitalRead(ir3);
c=digitalRead(ir2);
d=digitalRead(ir1);
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);     //turn the bot at station 1
digitalWrite(l1,LOW);
digitalWrite(l2,HIGH);
}while(b==0 || c==0);
}

void turn2(){
do{
a=digitalRead(ir4);
b=digitalRead(ir3);
c=digitalRead(ir2);
d=digitalRead(ir1);
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);     //turn the bot at station 2
digitalWrite(l1,LOW);
digitalWrite(l2,HIGH);
}while(b==0 || c==0 || a==1);
}

void turn2x(){
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

void turn3(){
do{
a=digitalRead(ir4);
b=digitalRead(ir3);
c=digitalRead(ir2);
d=digitalRead(ir1);
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);     //turn the bot at station 3
digitalWrite(l1,LOW);
digitalWrite(l2,HIGH);
}while(b==0 || c==0 || d==1);
}

//IR CHECK
int check(){               //checks the current position of the bot 
a=digitalRead(ir4);   
b=digitalRead(ir3);
c=digitalRead(ir2);
d=digitalRead(ir1); 

if(a==1 && d==1){ return 0; }        //bot is at inventory

else if(a==0 && d==0){ return 1; }   //bot is at station 1

else if(a==1 && d==0){ return 2;}    //bot is at station 2

else if(a==0 && d==1){ return 3;}    //bot is in station 3
}


// Init ESP Now with fallback
void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    // Retry InitESPNow, add a counte and then restart?
    // InitESPNow();
    // or Simply Restart
    ESP.restart();
  }
}

// config AP SSID
void configDeviceAP() {
  const char *SSID = "Slave_1";
  bool result = WiFi.softAP(SSID, "Slave_1_Password", CHANNEL, 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
    Serial.print("AP CHANNEL "); Serial.println(WiFi.channel());
  }
}

void setup() {
pinMode(l1,OUTPUT);
pinMode(l2,OUTPUT);
pinMode(r1,OUTPUT);
pinMode(r2,OUTPUT);

pinMode(enr,OUTPUT);
pinMode(enl,OUTPUT);

analogWrite(enr,230);
analogWrite(enl,235);

pinMode(ir1,INPUT);
pinMode(ir2,INPUT);
pinMode(ir3,INPUT);
pinMode(ir4,INPUT);
  Serial.begin(115200);
  Serial.println("ESPNow/Basic/Slave Example");
  //Set device in AP mode to begin with
  WiFi.mode(WIFI_AP);
  // configure device AP mode
  configDeviceAP();
  // This is the mac address of the Slave in AP Mode
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
  // Init ESPNow with a fallback logic
  InitESPNow();
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info.
  esp_now_register_recv_cb(OnDataRecv);
}

// callback when data is recv from Master
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Recv from: "); Serial.println(macStr);
  Serial.print("Last Packet Recv Data: "); Serial.println(*data);
  Serial.println("");
//DOWN
if(*data==0){
  if(check()==0){                         // if bot is at inventory
     rel();
  }else if(check()==1){                   // if bot is at station 1
    ST1();
    rel();
    turn0();
    rel();
  }else if(check()==2){                   // if bot is at station 2
    ST1();
    rel();
    turn0();
    rel();
  }else if(check()==3){                   // if bot is at station 3
    ST1();
    rel();
    turn0();
    rel();    
  }
}

  //BUTTON
if(*data==1){
    if(check()==0){               // if bot is at inventory
    ST1();
    rel();
    turn1();
    rel();
    }

    else if(check()==1){          // if bot is at station 1
     rel();
    }

    else if(check()==2){         // if bot is at station 2
      delay(1000);
      turn2();
      rel();
      ST1();
      rel();
      turn1();
      rel();
    }
    else if(check()==3){         // if bot is at station 3
      delay(1000);
      turn3();
      rel();
      ST1();
      rel();
      turn1();
      rel();
    }  }

   //LEFT
   else if(*data==2){ 
    if(check()==0){            // if bot is at inventory
      rel();
    }

    else if(check()==1){       // if bot is at station 1
      ST2();
      rel();}

   else if(check()==2){        // if bot is at station 2
    rel();}

    else if(check()==3){       // if bot is at station 3
      delay(1000);
      turn3();
      rel();
      ST3();
      lf();
      delay(750);
      rel();
      turn2x();
      rel();
    }

  }
  
  // RIGHT
  else if(*data==3){        
    if(check()==0){              // if bot is at inventory
      rel();
    }          
      if(check()==1){            // if bot is at station 1
      ST3();
      rel();}

      else if(check()==2){       // if bot is at station 3
      ST3();  
      rel();
    }
    else if(check()==3){        // if bot is at station 3
    rel();
    }
    }

else{
      rel();}
      }
  

void loop() {
  // Chill
}
