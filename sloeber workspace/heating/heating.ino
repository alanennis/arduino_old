
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer
//http://robotsbigdata.com/docs-arduino-timer.html


int Countdown;   // Global variable used in Slider widget and runEveryMinute()
int TimeChoice;
byte control_pin = 22;
bool heat_state = false;
int state;
int heating_run_timer;


char auth[] = "a8483d62fa0c4e3f96b906e722d4d3ca";
WidgetLCD lcd(V2);



RBD::Timer heating_timer;
RBD::Timer status_timer;

void LCDUpdate(String lcd_message) { // update the lcd and add new messages
  lcd.print(0,0, lcd_message);
}


BLYNK_WRITE(V0){   // add a slider to your project on V0 range 0 to 30 (minutes)
  Countdown = param.asInt();  // set variable as Slider value
  Serial.println(Countdown);
}

BLYNK_WRITE(V1){   // Get index of timer choice
  switch (param.asInt())
    {
      case 1: { // Item 1
        Serial.println("30 minutes heating selected");
       
        heat_action(30000, 1);
        break;
      }

      case 2: { // Item 2
        Serial.println("45 minutes heating selected");

        heat_action(45000, 1);
       
        break;
      }

       case 3: { // Item 2
        Serial.println("60 minutes heating selected");

        heat_action(60000, 1);
        
        break;
      }

       case 4: { // Item 2
        Serial.println("90 minutes heating selected");

        heat_action(90000, 1);
        
        break;
      }

       case 5: { // Item 2
	    Serial.println("120 minutes heating selected");

	    heat_action(120000, 1);

	   break;
      }
  
   
  }
}
  
  
  
void heat_action(unsigned long duration, int action) { //duration in ms; action 0 = off, 1 = on

switch (action)
  {
    
  case 0: { // heating off
    digitalWrite (control_pin, LOW); //physically turn the pin off
    Serial.println("Heating off");

    heating_timer.stop();
    Serial.println("Timer off");

    heat_state = false;

    break;
  }
  
  case 1: { // heating on for duration


	  Serial.println("heat action on");
	  heating_timer.setTimeout(duration);
	  heating_timer.restart();
	  digitalWrite(control_pin, HIGH);
	  heat_state = true;


	  break;

  } 
  }
}
  
int get_time_left(){

	unsigned long seconds_remaining;
	unsigned int minutes_remaining;

	seconds_remaining = heating_timer.getInverseValue() / 1000;
	//minutes_remaining = seconds_remaining / 60;

	return seconds_remaining;

}

void show_heat_state () { //display state in LCD

	unsigned long seconds_remaining;
	unsigned int minutes_remaining;

	state = digitalRead(control_pin);
	lcd.clear();
	if (state == 0){
	  lcd.print(0,0, "Heating off");
	  heating_timer.stop();
	}
	if (state == 1) {
		if (heating_timer.isActive()) {
			minutes_remaining = get_time_left();
		}

		else {
			minutes_remaining = 0;
		}



	  lcd.print(0,0, "Heating on");
	  lcd.print(0,1, minutes_remaining);
	  lcd.print(3,1, "Minutes left");
	}


	}

void heat_off() {

	  heat_action(0,0);
}
  


void setup()
{
  pinMode(control_pin, OUTPUT);
  Serial.begin(9600); 
  Blynk.begin(auth);
  
  lcd.clear();

  status_timer.setTimeout(5000);

  
  
  
}

void loop()
{
  Blynk.run();

  if(heating_timer.onRestart()) { heat_off(); }
  if(status_timer.onRestart()) { show_heat_state(); }

  
 
}
