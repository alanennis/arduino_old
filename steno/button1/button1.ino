

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;

byte val0 = 0;
byte val1 = 0;
byte val2 = 0;
byte val3 = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(pushButton, INPUT_PULLUP);

  pinMode(13, OUTPUT); //use led to show button press
  digitalWrite(13, LOW);  // Turn off LED
}

void give(){
  Serial.println("this is a test");
}

void cr() {
  Serial.print("\n");
}







// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  if (buttonState == 0) {
    give();

  }

    
  // print out the state of the button:
  //Serial.println(buttonState);
  delay(10);        // delay in between reads for stability
}
