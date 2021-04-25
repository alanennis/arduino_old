#include <SimpleTimer.h>

int duration = 98500;
unsigned long start_time;
unsigned long current_time;
unsigned long time_diff;  
unsigned long time_elapsed;
unsigned long time_remain;

SimpleTimer timer1;
SimpleTimer timer2;

void printIt(){
  Serial.println("hello");
}

void time_check(){
  current_time = millis();
  time_elapsed = current_time - start_time;
  time_remain = duration - time_elapsed;
  Serial.println("Time remaining");
  Serial.println(time_remain);
  


  
}



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  timer1.setInterval(duration, printIt);
  start_time - millis();
  timer2.setInterval(1000, time_check);
}

void loop() {
  // put your main code here, to run repeatedly:

  timer1.run();
  timer2.run();

}
