

#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer

unsigned long duration = 600000;
unsigned long seconds_remaining;
unsigned long minutes_remaining;


RBD::Timer timer1;
RBD::Timer timer2;

void printIt(){
  Serial.println("hello");
}

void time_check(){
//  current_time = millis();
//  time_elapsed = current_time - start_time;
//  time_remain = duration - time_elapsed;
//  Serial.println("Time remaining");
//  Serial.println(time_remain);

  seconds_remaining = timer1.getInverseValue() / 1000;
  minutes_remaining = seconds_remaining /60;
  Serial.println (minutes_remaining);

  
}



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  timer1.setTimeout(duration);
  timer2.setTimeout(1000);
  timer1.restart();
  timer2.restart();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(timer1.onRestart()){printIt();}
  if(timer2.onRestart()){time_check();}



}
