#include <TimerOne.h>    // interrupt library

//************************************* Global Variables


// Variables for sensor

const int trigPin=13;                //Sensor Trig pin connected to Arduino pin 13
const int echoPin=11;                //Sensor Echo pin connected to Arduino pin 11
volatile float pingTime;                //time for ping to travel from sensor to target and return
volatile float targetDistance;          //Distance to Target in inches
const float speedOfSound=776.5;      //Speed of sound in miles per hour when temp is 77 degrees.
volatile int dir34 = 1;                 //changes direction for nema34
volatile int dir23 = 1;                 //changes direction for nema23
volatile int state =0 ;                 // swtich variable

// Flags

int motorStatus34=1 ;          // flag for nema 34 motor and sensor feedback
int motorStatus23=1 ;          // flag for nema 23 motor and sensor feedback

int motorrot = 0;             // flag for motor. dictates stop or rotate

 
// Define variables for stepper motor connections:

#define dirPin34 2      //Pin that controls direction for NEMA 34
#define stepPin34 3     //Pin that provides pwm to NEMA 34
#define dirPin23 4      //pin thatcontrols direction for NMEA 23
#define stepPin23 5     //pin that provides pwm to NEMA 23
#define RedLED 9        //pin for led

//*********************************************************************SETUP FUNCTION***********
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);          // baud rate
  pinMode(trigPin, OUTPUT);    // sensor trig pin
  pinMode(echoPin, INPUT);     // sensor echo pin

    
  pinMode(stepPin34, OUTPUT);    // motor step pin nema34 
  pinMode(dirPin34, OUTPUT);     // motor direction pin nema34
  pinMode(stepPin23, OUTPUT);    // motor step pin nema23
  pinMode(dirPin23, OUTPUT);     // motor direction pin nema23
  
//  digitalWrite(dirPin34, dir34);    // Set the spinning direction for nema34 CW/CCW:
//  digitalWrite(dirPin23, dir23);    // Set the spinning direction for nema23 CW/CCW:


  Timer1.initialize(750000); // interrupt initialization for 0.25 seconds

  Timer1.attachInterrupt(sonicSensor); // call sonic sensor function

}

void loop() {
  // put your main code here, to run repeatedly:



  switch(state){


    case  0:        // initialize parameters
    
            motorStatus34=1 ;          // flag for nema 34 motor and sensor feedback
            motorStatus23=1 ;          // flag for nema 23 motor and sensor feedback
            dir34 = 1;                 //changes direction for nema34
            dir23 = 1;                 //changes direction for nema23

            state=1;                   // state transition
            break;

     case 1:       // move from A to B. only NEMA 34 rotates CW

            delay(2000);
            for(int i=0; i<=3300*2;i++){  // 3300 for one full rotation of shaft with 500 microsec delay

            nema34();  // calling nema 34 // statement(s);

            }

            state=2;  // state transition
            break;

     
     case 2:      // stop at B. stop the NEMA 34s  

           delay(2000);     // delay a little bit
           motorStatus34=0;  // changes pin 3 to LOW
           state=3;        // state transition
           break;

           
     case 3:      // lift up while standing at B. NEMA 23 rotates CW

            for(int i=0; i<=3300*5;i++){  // 3300 for one full rotation of shaft with 500 microsec delay

               nema23();  // calling nema 23 // statement(s);

            }

            state=4;   // state transition
            break;
     
     case 4:     // Stop at lifting postion while stationed at B. stop NEMA 23
            
            delay(2000);      // delay a little bit
            motorStatus23=0;  // changes pin 5 to LOW
            state=5;          // state transtion
            break;

                 
     case 5:     // go down while stationed at B. NEMA 23 rotates CCW
           delay(2000);
           dir23 =0; // rotate CCW
           motorStatus23=1;  // changes pin 5 to HIGH
            
           for(int i=0; i<=3300*5;i++){  // 3300 for one full rotation of shaft with 500 microsec delay

              nema23();  // calling nema 23 // statement(s);

            }

           state=6;     // state transtion
           break;
     
     case 6:     // stop at down postion. stop NEMA 23 
           delay(2000);
           motorStatus23=0;  // changes pin 5 to LOW
           state=7;          // state transtion
           break;
           
     case 7:     // Move from B to A. NEMA 34s rotates CCW

           delay(2000);
           dir34 =0; // rotate CCW
           motorStatus34=1;  // changes pin 3 to HIGH

           for(int i=0; i<=3300*2;i++){  // 3300 for one full rotation of shaft with 500 microsec delay

              nema34();  // calling nema 34 // statement(s);

            }

           state=8;     // state transtion      
           break;
     
     case 8:      // stop the system

           motorStatus34=0;  // changes pin 3 to LOW

           state=0;         // state transtion
           break;

    
  }


}



void nema34(){


if (targetDistance<6) {         // compares data from sensor 
     
     motorStatus34 = 0;          // motor flag = stop motor. 
     analogWrite(RedLED,255);  // flash red light
   }
 
  else{

   motorStatus34 = 1;        // keep motor rotate
   analogWrite(RedLED,0);  // turn off red light
  }
  //*****************************************************************************NEMA 34 MOTOR CODE***********************************
   // These four lines result in 1 step:
  //analogWrite(stepPin, x);      // provides pwm wave 0-255 value
  digitalWrite(dirPin34, dir34);
  digitalWrite(stepPin34, motorStatus34); 
  delayMicroseconds(250);
  digitalWrite(stepPin34,0);      // 0 = LOW and 1 = HIGH
  delayMicroseconds(250);

 
}

void nema23(){

    //*****************************************************************************NEMA 23 MOTOR CODE***********************************
   // These four lines result in 1 step:
  //analogWrite(stepPin, x);      // provides pwm wave 0-255 value
  digitalWrite(dirPin23, dir23);
  digitalWrite(stepPin23, motorStatus23); 
  delayMicroseconds(600);
  digitalWrite(stepPin23,0);      // 0 = LOW and 1 = HIGH
  delayMicroseconds(600);
}

void sonicSensor(){

    //********************************************************************************SENSOR CODE*****************************
  digitalWrite(trigPin, LOW);        //Set trigger pin low
  delayMicroseconds(2000);           //Let signal settle
  digitalWrite(trigPin, HIGH);       //Set trigPin high
  delayMicroseconds(300);             //Delay in high state
  digitalWrite(trigPin, LOW);        //ping has now been sent
  delayMicroseconds(300);             //Delay in low state
  
  pingTime = pulseIn(echoPin, HIGH);          //pingTime is presented in microceconds
  pingTime=pingTime/1000000;                  //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime=pingTime/3600;                     //convert pingtime to hourse by dividing by 3600 (seconds in an hour)
  targetDistance= speedOfSound * pingTime;    //This will be in miles, since speed of sound was miles per hour
  targetDistance=targetDistance/2;            //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  targetDistance= targetDistance*63360;       //Convert miles to inches by multipling by 63360 (inches per mile)
  
  Serial.println(targetDistance);
  
  delay(100); //delay tenth of a  second to slow things down a little.



}
