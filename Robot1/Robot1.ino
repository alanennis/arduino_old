/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);
  float slowFactor = 1.1;

const int trigPin = 2;
const int echoPin = 4;

void setup() {
  Serial.begin(115200);         
  Serial.println("Robot 1 online");

  AFMS.begin(1000);  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(240); // motors are not well balanced so slight different speed required for straing line
  myMotor2->setSpeed(255);

}

boolean checkDistance() {
  //Serial.println("made it here");

  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration;
  float cm;
  float safeDistance = 30.0;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  Serial.println(duration);
  cm = duration / 29.00 / 2.0;
  //return cm;
  Serial.println(cm);
  if (cm < safeDistance){ return false;}
  else {return true;}
  
}


void drive(String whereTo, int turnAmount)
{

  
 if (whereTo == "forward")
  {
    Serial.println("going forward");
    myMotor->run(RELEASE);
    myMotor2->run(RELEASE);
    
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
    
    //delay(turnAmount);
    
    //myMotor->run(RELEASE);
    //myMotor2->run(RELEASE);

    //Keep going until we are stopped
    
  }

  else if (whereTo == "back"){

    Serial.println("reverse");
    myMotor->run(RELEASE);
    myMotor2->run(RELEASE);
    
    myMotor->run(BACKWARD);
    myMotor2->run(BACKWARD);
    delay(turnAmount);
    
    myMotor->run(RELEASE);
    myMotor2->run(RELEASE);
    
  }
  
  else if (whereTo == "left"){
    Serial.println ("turning left");
    
    myMotor->run(RELEASE);
    myMotor2->run(RELEASE);
        
    myMotor->run(FORWARD);
    myMotor2->run(BACKWARD);
    if (turnAmount == 10) {delay (26); }
    else if (turnAmount == 20) { Serial.println ("turning 20"); delay (52); }
    else if (turnAmount == 30) {delay (78); }
    else if (turnAmount == 45) {delay (120); }
    else {Serial.println ("Can't do the turn");} 
      
    myMotor->run(RELEASE);
    myMotor2->run(RELEASE);
  }
      
   else if (whereTo == "right"){
    
    myMotor->run(RELEASE);
    myMotor2->run(RELEASE);
        
    myMotor->run(BACKWARD);
    myMotor2->run(FORWARD);
    if (turnAmount == 10) {delay (26); }
    else if (turnAmount == 20) { Serial.println ("turning 20"); delay (52); }
    else if (turnAmount == 30) {delay (78); }
    else if (turnAmount == 45) {delay (120); }
    else {Serial.println ("Can't do the turn");} 
   
    myMotor->run(RELEASE);
    myMotor2->run(RELEASE);
   
   }  

   else if (whereTo == "stop"){
    
    myMotor->run(RELEASE);
    myMotor2->run(RELEASE); 
    
   }
   
    
    
} 
  

void loop() {
 
// delay (50); // just to give me a chance to get out of the way
 
//drive("forward",0);
 

while (checkDistance()){ 
  
  
  Serial.println ("good to go");
    drive("forward",0);
    delay (500);
 
  
  
  }
  
  Serial.println("DANGER");
  drive("stop",0);
  drive("back", 200);
  drive("left", 30);
 

//delay(200);

}








