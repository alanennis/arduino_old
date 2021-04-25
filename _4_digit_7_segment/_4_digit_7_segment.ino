/*
This Arduino code for "4-digit-7-segment-led-display" (KYX-5461AS).
* This code can display one Number in all 4 digit!
* This code can display 4 Numbers each on in specific digit
* This code can also make a Number Countdown (Timers).
author : Oussama Amri (@amriunix)
website : ithepro.com
*/

//display pins
int segA = 5;  // >>  11
int segB = 13; // >>  7
int segC = 10; // >>  4
int segD = 8;  // >>  2
int segE = 7;  // >>  1
int segF = 4;  // >>  10
int segG = 11; // >>  5
int segPt = 9; // >>  3
//------------//

//display digit
int d1 = 6;   // >> 12
int d2 = 3;   // >> 9
int d3 = 2;   // >> 8
int d4 = 12;  // >> 6
//------------//

int delayTime = 5000; //delayTime <Don't change it, if you don't know where is it!>

int i=0;

//=============================================//
//init all pin used
void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}



//=============================================//
void loop() {
//down(0,0,2,4);
all(5);
//writeN(1,9,9,4);
}



//=============================================//
//Write a Number - writeN(1,9,9,0) -> 1990
void writeN(int a,int b,int c,int d){
    selectDwriteL(1,a);
    selectDwriteL(2,b);
    selectDwriteL(3,c);
    selectDwriteL(4,d);
}

//=============================================//
//Make a Number Number Countdown (Timers).
void down(int a,int b,int c,int d){
  while (a != -1) {
    while(b != -1){
      while(c != -1){
        while (d != -1) {
          while (i<10) { // i here is like a timer ! because we can't use delay function
            selectDwriteL(1,a);
            selectDwriteL(2,b);
            selectDwriteL(3,c);
            selectDwriteL(4,d);
            i++;
          }
          i=0;
          d--;
        }
        d=9;
        c--;
      }
      c=9;
      b--;
    }
    b=9;
    a--;
    }
}

//=============================================//
//Select Wich Digit (selectD) is going to Display (writeL)
void selectDwriteL(int d,int l){
  switch (d) { // choose a digit
    case 0: digitalWrite(d1, LOW); //case 0 - All ON
            digitalWrite(d2, LOW);
            digitalWrite(d3, LOW);
            digitalWrite(d4, LOW);
            break;
    case 1: digitalWrite(d1, LOW);//case 1 - Digit Number 1
            digitalWrite(d2, HIGH);
            digitalWrite(d3, HIGH);
            digitalWrite(d4, HIGH);
            break;
    case 2: digitalWrite(d1, HIGH);//case 1 - Digit Number 2
            digitalWrite(d2, LOW);
            digitalWrite(d3, HIGH);
            digitalWrite(d4, HIGH);
            break;
    case 3: digitalWrite(d1, HIGH);//case 1 - Digit Number 3
            digitalWrite(d2, HIGH);
            digitalWrite(d3, LOW);
            digitalWrite(d4, HIGH);
            break;
    case 4: digitalWrite(d1, HIGH);//case 1 - Digit Number 4
            digitalWrite(d2, HIGH);
            digitalWrite(d3, HIGH);
            digitalWrite(d4, LOW);
            break;
  }

  switch (l) { // choose a Number
    case 0: zero();
            break;
    case 1: one();
            break;
    case 2: two();
            break;
    case 3: three();
            break;
    case 4: four();
            break;
    case 5: five();
            break;
    case 6: six();
            break;
    case 7: seven();
            break;
    case 8: eight();
            break;
    case 9: nine();
            break;
    case 10: point(); // print a Point
            break;
    case 11: none(); // make all them off !
            break;
  }

delayMicroseconds(delayTime); // delayTime for nice display of the Number !

}

//=============================================//
//shown one Number in the 4 Digit
void all(int n){
  selectDwriteL(0,n);
}

//=============================================//
void zero(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, LOW);
}
//=============================================//
void one(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, LOW);
}
//=============================================//
void two(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}
//=============================================//
void three(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}
//=============================================//
void four(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}
//=============================================//
void five(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}
//=============================================//
void six(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}
//=============================================//
void seven(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, LOW);
}
//=============================================//
void eight(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}
//=============================================//
void nine(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}
//=============================================//
void point(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void none(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, LOW);
}
