/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


#include <Fonts/FreeMonoBold12pt7b.h>
//#include <Fonts/FreeMono9pt7b.h>
//#include <Fonts/digi21x16_font.h>
//#include <Fonts/amstrad_font.h>
//#include <Fonts/TomThumb.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
//Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 5, 4, 3);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!


void setup()   {
  Serial.begin(9600);
  Serial.println("Serial on...");

  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(127);
  display.setFont(&FreeMonoBold12pt7b);

  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer

  // draw a single pixel
  display.drawPixel(10, 10, BLACK);
  display.display();
  delay(20);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  
}


 void loop()  {
  //Serial.println("in the loop");

 
  
  display.setCursor(0,30);
  display.println("14:01");
  display.display();
  delay(500);
  display.clearDisplay();

  display.setCursor(0,30);
  display.println("14 01");
  display.display();
  delay(500);
  display.clearDisplay();



  

 }

