# Arduino
Finite State Machine Code for Intel Robot

### Registers_Lesson.ino

This file contains bitwise operation codes for setting external interrupts on Atmega328 register.

By using this code you can ON/OFF a LED with a push button. 


### remote_infra.ino

This code can be implemented to control an LED with a Infrared Remote 


### Sensor.ino

This code can be implemented to recieve real time distance feedback from a Ultrasonic Sensor

### V5_interrupt_motor_control.ino

This is the main code for InterlServerRobot that combines motor control and sensor feature. This code implements a Finate State Machine algorithm which controls two stepper motors. 


#### <TimerOne.h> 
This library provides funcitons required to invoke interrupt feature of Atmega 328 microcontroller. 

#### nema34()

This function controls the drive motors (NEMA 34).

#### nema23

This function controls the lift motor (nema 23).

#### sonicSensor()

This function activates ultrasonic sensor.
