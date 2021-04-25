/*
  NTP-TZ-DST
  NetWork Time Protocol - Time Zone - Daylight Saving Time

  This example shows how to read and set time,
  and how to use NTP (set NTP0_OR_LOCAL1 to 0 below)
  or an external RTC (set NTP0_OR_LOCAL1 to 1 below)

  TZ and DST below have to be manually set
  according to your local settings.

  This example code is in the public domain.
*/

#include <ESP8266WiFi.h>
#include <time.h>                       // time() ctime()
#include <sys/time.h>                   // struct timeval
#include <coredecls.h>                  // settimeofday_cb()

////////////////////////////////////////////////////////

#define SSID            "alan2"
#define SSIDPWD         "barker22"
#define TZ              0       // (utc+) TZ in hours
#define DST_MN          60      // use 60mn for summer time in some countries

#define NTP0_OR_LOCAL1  0       // 0:use NTP  1:fake external RTC
#define RTC_TEST     1510592825 // 1510592825 = Monday 13 November 2017 17:07:05 UTC

////////////////////////////////////////////////////////

#define TZ_MN           ((TZ)*60)
#define TZ_SEC          ((TZ)*3600)
#define DST_SEC         ((DST_MN)*60)

timeval cbtime;			// time set in callback
bool cbtime_set = false;

void time_is_set(void) {
  gettimeofday(&cbtime, NULL);
  cbtime_set = true;
  Serial.println("------------------ settimeofday() was called ------------------");
}

void setup() {
  Serial.begin(115200);
  settimeofday_cb(time_is_set);

  #if NTP0_OR_LOCAL1
  // local

  ESP.eraseConfig();
  time_t rtc = RTC_TEST;
  timeval tv = { rtc, 0 };
  timezone tz = { TZ_MN + DST_MN, 0 };
  settimeofday(&tv, &tz);

  #else // ntp

  configTime(TZ_SEC, DST_SEC, "pool.ntp.org");
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, SSIDPWD);
  // don't wait, observe time changing when ntp timestamp is received

  #endif // ntp
}

// for testing purpose:
extern "C" int clock_gettime(clockid_t unused, struct timespec *tp);

#define PTM(w) \
  //Serial.print(":" #w "="); \
  //Serial.print(tm->tm_##w);

void printTm(const char* what, const tm* tm) {
  Serial.print(what);
  PTM(isdst); PTM(yday); PTM(wday);
  PTM(year);  PTM(mon);  PTM(mday);
  PTM(hour);  PTM(min);  PTM(sec);
}

timeval tv;
timespec tp;
time_t now;
uint32_t now_ms, now_us;

void safe_delay(int time_in_ms) {
  const int SAFE_DELAY_TIME = 10;
  
  for (int i=0 ; i < time_in_ms ; i += SAFE_DELAY_TIME ) {
    yield();
    delay(SAFE_DELAY_TIME);
  }
}

void loop() {

  gettimeofday(&tv, nullptr);
  clock_gettime(0, &tp);
  now = time(nullptr);
  now_ms = millis();
  now_us = micros();

  // localtime / gmtime every second change
  static time_t lastv = 0;
  if (lastv != tv.tv_sec) {
    lastv = tv.tv_sec;
    //Serial.println();
    //printTm("localtime", localtime(&now));
    //Serial.println();
    //printTm("gmtime   ", gmtime(&now));
    //Serial.println();
    //Serial.println();
  }


  // human readable
  //Serial.print(" ctime:(UTC+");
  //Serial.print((uint32_t)(TZ * 60 + DST_MN));
  //Serial.print("mn)");
  Serial.print(ctime(&now));

  // simple drifting loop
  //Serial.println("--------------------------------------------------------------------");
  safe_delay(60000);
  
}
