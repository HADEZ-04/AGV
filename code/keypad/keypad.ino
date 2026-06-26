#include <Key.h>
#include <Keypad.h>

const byte norow=4;
const byte nocol=4;

byte rowpins[norow]={2,3,4,5};
byte colpins[nocol]={6,8,9,10};

char keyarray[norow][nocol]= {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};

Keypad k=Keypad(makeKeymap(keyarray),rowpins,colpins,norow,nocol); 
void setup() {
Serial.begin(9600);
}

void loop() {
char keypressed=k.getKey();
if(keypressed){
  Serial.println(keypressed);
}
}
