/************************************************************************
*
* Test of the Pmod module
*
*************************************************************************
* Description: Pmod_CLS
* message sent from serial monitor will be show on LCD display.
*
* Material
* 1. Arduino Uno
* 2. Pmod CLS (Jumpers on positions MOD0 and MOD2)
* See instructions list on https://reference.digilentinc.com/pmod/pmod/cls/user_guide
*
************************************************************************/

//Declaration of a serial port
#include <SoftwareSerial.h>
SoftwareSerial lcd(2,3); // RX, TX

char machaine[40];
int i=0;

void setup()
{
 
Serial.begin(9600); // initialization of serial communication of the moniteur
lcd.begin(9600); // initialisation of serial communication of the display
lcd.write("\x1b[j"); // Erase display
lcd.write("\x1b[0h"); // configuration of the display (write on 2 lines)
lcd.write("\x1b[0;5H"); // cursor is on line 1 and columm 5
lcd.print("hey");
lcd.write("\x1b[1;1H"); // cursor is on line 2 and columm 1e
lcd.print("your message");
delay(2000);
lcd.write("\x1b[j"); // Erase display
lcd.write("\x1b[0;1H"); // cursor is on line 1 and columm 1
lcd.print("ShutTheFuckUp");
lcd.write("\x1b[1;5H"); // cursor is on line 2 and columm 5
lcd.print("B****");
}

void loop()
{
while (Serial.available()) // As long as caracters are on serial communication
   {
   machaine[i]=Serial.read(); // Store caracters in table machaine
   Serial.print(machaine[i]); // Write caractères in serial monitor
   delay(10);
   if (i==0) // If first caracter
      {
      lcd.write("\x1b[j"); // Erase display
      lcd.print(machaine[i]); // Send caracter on display
      }
   else
     {
     lcd.print(machaine[i]);
     }
   i++;
   }
i=0; // Initialisation for next message
}




  // Serial. print (" The dist to the target is : ");
  // Serial. print (targetDistance);
   //Serial. print (" Inches ");
   
  // Serial.println(targetDistance);
  // delay(1000);


//   servoAngle= (106/7)*targetDistance + 37 ;
  // myPointer.write (servoAngle);
//  delay (100);

   

//}
