#include <IRremote.h>

const int recv_pin = 6;
const int ledPin = 7; 
volatile int x = 0;
IRrecv irrecv(recv_pin);

decode_results results;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

 pinMode(ledPin,OUTPUT);
 irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:

  
  if (irrecv.decode(&results)){

    // print code in hex

    Serial.println(results.value,HEX);
    irrecv.resume();
    }
  
    if(results.value == 0xFFC23D){
      digitalWrite(ledPin,HIGH);
    }else if(results.value == 0xFFE21D){
      digitalWrite(ledPin,LOW);
    }
    
    
  
}
