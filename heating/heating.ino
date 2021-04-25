1#include <SimpleTimer.h>

unsigned long start_time;
unsigned long current_time;
unsigned long time_diff;
byte status_timer;
byte remainder_timer;
int time_delta;
int minutes_remaining;
int seconds_remaining;
int duration = 600000;


SimpleTimer timer;
SimpleTimer clock_check;

void doNothing() { // check and see how long is left
	Serial.println("doing nothing3");
}

void time_remaining() {// check how much is left
	Serial.println(millis());
	Serial.println("checking time");
	Serial.println(start_time);
	current_time = millis();
	Serial.println(current_time);

	time_delta = current_time - start_time;
	Serial.println("time_delta");
	Serial.println(time_delta);

	time_diff = duration - time_delta;

	seconds_remaining = time_diff/1000 * -1;
	Serial.println("seconds remaining");
	Serial.println(seconds_remaining);
	Serial.println("");

	minutes_remaining = seconds_remaining / 60;

	Serial.println("Minutes remaining = ");
	Serial.println(minutes_remaining);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  status_timer = timer.setInterval(duration, doNothing);
  delay(1000);
  start_time = millis();
  remainder_timer = clock_check.setInterval(5000, time_remaining);
}

void loop() {
  // put your main code here, to run repeatedly:

	timer.run();
	clock_check.run();

}
