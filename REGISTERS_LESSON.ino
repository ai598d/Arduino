//pins
const uint8_t btn_pin = 2;
const uint8_t led_pin = 5;

//Global
uint8_t led_state = LOW;
uint8_t btn_prev = HIGH;



void setup() {
  // put your setup code here, to run once:

 pinMode(btn_pin, INPUT_PULLUP);
 pinMode(led_pin, OUTPUT);

 
 //  DDRD = B00100000; // means 32
//  PORTD = B00000100;
attachInterrupt(digitalPinToInterrupt(btn_pin),toggle,FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:

  uint8_t btn_state = digitalRead(btn_pin);


//  if ((btn_state ==LOW) && (btn_prev ==HIGH)){
//
//      
//    led_state =!led_state;
//    digitalWrite(led_pin, led_state);
//  } 
//  
//  btn_prev= btn_state;
  delay(500);

}


void toggle(){


  led_state = !led_state;
  digitalWrite(led_pin,led_state);
}
