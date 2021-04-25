// From left N5110 display #1 to #5
// #1 RST      - Pin 9
// #2 CS/CE    - Pin 10
// #3 DC       - Pin 8
// #4 MOSI/DIN - Pin 11
// #5 SCK/CLK  - Pin 13
// #6 VCC 3.3V
// #7 LIGHT (200ohm to GND) Pin 6
// #8 GND
// 
// Pin2 - IR receiver (not now)
// Pin5 - button

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 8, 10, 9); // SW SPI
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 10, 9); // HW SPI

#include <idDHT11.h>
#include <Wire.h>
#include <DS1307.h>
#include "LowPower.h"
#include <BMP180.h>
#include <BH1750.h>

BH1750 lightMeter;

BMP180 barometer;
// Store the current sea level pressure at your location in Pascals.
float seaLevelPressure = 101325;

DS1307 clock;
RTCDateTime dt;

#define buttonPin  5
#define lightPin   6
#define idDHT11pin 2       //Digital pin for comunications
int idDHT11intNumber = 0; //interrupt number (must be the one that use the previus defined pin (see table above)
//declaration
void dht11_wrapper(); // must be declared before the lib initialization
idDHT11 DHT11(idDHT11pin, idDHT11intNumber, dht11_wrapper);
void dht11_wrapper() {
  DHT11.isrCallback();
}

char buf[30];
//#include "proppl5x7_font.h"
//#include "term9x14_font.h"
//#include "term11x16_font.h"
//#include "amstrad_font.h"
//#include "c64enh_font.h"

//#include "chicago_font.h"
//#include "digi19x15_font.h"
#include "digi21x16_font.h"
//#include "broadway_font.h"

//#include "small4x5_font.h"
#include "small4x6_font.h"
//#include "small4x7_font.h"
//#include "small5x7_font.h"
#include "small5x7bold_font.h"
#include "tiny3x7_font.h"

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}
void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(lightPin, OUTPUT);
  lightMeter.begin();
  display.begin(0x30, 2); // contrast, bias
  display.clearDisplay();
  Serial << "-- Start --" << "\n";
  // Initialize DS1307
  //Serial.println("Initialize DS1307");;
  clock.begin();
  // If date not set
  if (!clock.isReady()) {
    // Set sketch compiling time
    clock.setDateTime(__DATE__, __TIME__);
  }
  barometer = BMP180();
  // We check to see if we can connect to the sensor.
  if (barometer.EnsureConnected()) {
    //Serial.println("Connected to BMP180."); // Output we are connected to the computer.
    // When we have connected, we reset the device to ensure a clean start.
    barometer.SoftReset();
    // Now we initialize the sensor and pull the calibration data.
    barometer.Initialize();
  } else {
    //Serial.println("Could not connect to BMP180.");
  }
  //irrecv.enableIRIn();
}

void readDHT11()
{
  DHT11.acquire();
  while (DHT11.acquiring())
    ;
  int result = DHT11.getStatus();
  switch (result)
  {
    case IDDHTLIB_OK:
      //Serial.println("OK");
      break;
    case IDDHTLIB_ERROR_CHECKSUM:
      Serial.println("Error\n\r\tChecksum error");
      break;
    case IDDHTLIB_ERROR_ISR_TIMEOUT:
      Serial.println("Error\n\r\tISR Time out error");
      break;
    case IDDHTLIB_ERROR_RESPONSE_TIMEOUT:
      Serial.println("Error\n\r\tResponse time out error");
      break;
    case IDDHTLIB_ERROR_DATA_TIMEOUT:
      Serial.println("Error\n\r\tData time out error");
      break;
    case IDDHTLIB_ERROR_ACQUIRING:
      Serial.println("Error\n\r\tAcquiring");
      break;
    case IDDHTLIB_ERROR_DELTA:
      Serial.println("Error\n\r\tDelta time to small");
      break;
    case IDDHTLIB_ERROR_NOTSTARTED:
      Serial.println("Error\n\r\tNot started");
      break;
    default:
      Serial.println("Unknown error");
      break;
  }
  //Serial.println(DHT11.getHumidity());
  //Serial.println(DHT11.getCelsius(), 2);
  //Serial.println(DHT11.getDewPoint());
}

long readIntTemp() {
  long result;
  // Read temperature sensor against 1.1V reference
  ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = (result - 125) * 1075;
  return result;
}


long bmpPressure = 0;
long bmpTemp = 0;

void readBMP()
{ if (barometer.IsConnected)
  {
    // Retrive the current pressure in Pascals.
    bmpPressure = barometer.GetPressure() / 100;
    // Retrive the current temperature in degrees celcius.
    bmpTemp = barometer.GetTemperature();
  }
}

unsigned long cnt = 0;
int lastMode, mode = 1;
uint16_t lux;
long tsDebounce = 0, ts = 0;
void loop()
{
  if (checkButton())
    mode = (mode + 1) % 3;

  if (millis() - ts > 1000 || lastMode != mode) {
    if (millis() - ts > 400)
      readDHT11();
    lastMode = mode;
    ts = millis();
    readBMP();
    lux = lightMeter.readLightLevel();
    dt = clock.getDateTime();
    setLight();
    Serial << "Time:   " << dt.hour<<":"<<dt.minute<<":"<<dt.second<<"\r\n";
    Serial << "DHT11:  " << (int)DHT11.getCelsius()<<"'C  "<<(int)DHT11.getHumidity()<<"%\r\n";
    Serial << "BMP180: " << bmpTemp<<"'C  "<<bmpPressure<<" hPa\r\n";
    Serial << "BH1750: " << lux<<" lux\r\n";
    Serial << "----------------------------------------------\r\n";
    if (Serial.available() > 0) {
      if (Serial.read() == '\n')
        mode = (mode + 1) % 3;
    }
      
    display.clearDisplay();
    switch (mode) {
      case 0:
        mode0(); break;
      case 1:
        mode1(); break;
      case 2:
        mode2(); break;
      default:
        mode0(); break;
    }
    display.display();
    cnt++;
  }
}

void mode0()
{
  if (cnt % 15 < 6) {
    showBigClockDate(0);
  } else {
    showAllSensors(0);
  }
}

void mode1()
{
  showBigClockDate(1);
}

void mode2()
{
  showAllSensors(1);
}

void setLight()
{
  //  analogWrite(lightPin, map(constrain(lux,30,50), 30, 50, 0, 255));
  digitalWrite(lightPin, lux < 50 ? LOW : HIGH);
}

int oldState = LOW;
int checkButton()
{
  if (millis() - tsDebounce < 50)
    return 0;
  tsDebounce = millis();
  int state = digitalRead(buttonPin);
  if (state == oldState)
    return 0;
  oldState = state;
  return state == LOW ? 1 : 0;
}

char *monthsPl[] = {"Sty", "Lut", "Mar", "Kwi", "Maj", "Cze", "Lip", "Sie", "Wrz", "Paź", "Lis", "Gru" };
char *daysPl[] = {"Pon", "Wt", "Śr", "Czw", "Pt", "Sob", "Nie"};
void showBigClockDate(int secs)
{
  //if (secs) display.drawLine(0, 0, (dt.second) * 84 / 60, 0, BLACK);
  display.setFont(Digi21x16);
  display.setSpacing(3);
  display.setTextSize(1, 2);
  snprintf(buf, 20, "%d:%02d", dt.hour, dt.minute);
  display.setCursor(CENTER, 2);
  display.printTxt(buf);

  display.setSpacing(1);
  display.setTextSize(1, 1);
  display.setFont(Small5x7PLBold);
  snprintf(buf, 20, "%d %s %02d %s", dt.day, monthsPl[dt.month - 1], dt.year, daysPl[dt.dayOfWeek - 1]);
  display.setCursor(CENTER, 39);
  display.printTxt(buf);

  if(!secs)
    return;
  int xs = display.stringXSize(buf);
  //display.drawRect((display.width() - xs) / 2 - 2, 37, xs + 3, 7 + 4, BLACK);
  int start = (display.width() - xs) / 2 - 2;
  display.drawLine(start, 37, start + (dt.second) * (xs+3) / 60, 37, BLACK);
  display.drawLine(start, 47, start + (dt.second) * (xs+3) / 60, 47, BLACK);
}

void showAllSensors(int date)
{
  if (!date) {
    display.setFont(Small5x7PLBold);
    display.setTextSize(2, 1);
    //snprintf(buf, 20, "%d:%02d", dt.hour, dt.minute);
    snprintf(buf, 20, "%d:%02d:%02d", dt.hour, dt.minute, dt.second);
    display.setCursor(CENTER, 0);
    display.printTxt(buf);
  } else {
    display.setTextSize(1, 1);
    display.setFont(Tiny3x7PL);
    snprintf(buf, 20, "%d:%02d:%02d", dt.hour, dt.minute, dt.second);
    display.setCursor(LEFT, 0);
    display.printTxt(buf);
    
    snprintf(buf, 20, "%d.%02d.%02d", dt.day, dt.month, dt.year - 2000);
    display.setCursor(RIGHT, 0);
    display.printTxt(buf);

    snprintf(buf, 20, "%s", daysPl[dt.dayOfWeek - 1]);
    display.setCursor(CENTER, 0);
    display.printTxt(buf);
  }

  display.setFont(Small4x6PL);
  display.setTextSize(1);

  display.setCursor(0, 9);
  display.printTxt("DHT/BMP");
  snprintf(buf, 30, "%2d'C/%2d'C", (int)DHT11.getCelsius(), bmpTemp);
  display.setCursor(RIGHT, 9);
  display.printTxt(buf);

  display.setCursor(0, 17);
  display.printTxt("Wilgotność");
  snprintf(buf, 20, "%2d%%", (int)DHT11.getHumidity());
  display.setCursor(RIGHT, 17);
  display.printTxt(buf);

  display.setCursor(0, 25);
  display.printTxt("Ciśnienie");
  snprintf(buf, 20, "%d hPa", bmpPressure);
  display.setCursor(RIGHT, 25);
  display.printTxt(buf);

  display.setCursor(0, 33);
  display.printTxt("Światło");
  snprintf(buf, 20, "%d lux", lux);
  display.setCursor(-2, 33);
  display.printTxt(buf);

  display.setCursor(0, 41);
  display.printTxt("Temp. Arduino");
  snprintf(buf, 30, "%2d'C", (readIntTemp() / 10000) - 2);
  display.setCursor(RIGHT, 41);
  display.printTxt(buf);
}
