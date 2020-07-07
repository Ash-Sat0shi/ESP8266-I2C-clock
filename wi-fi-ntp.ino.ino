#include <RTClib.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <time.h>

#define WIFI_SSID   "Buffalo-G-1698"
#define WIFI_PASSWORD   "pwykhfvgjcnnk"
#define JST     3600*9

char s[8];
char t[32];
RTC_DS3231 RTC;
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //STM32F103C8T6(BlackPill) and DSDtech I2C

void setup() {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  u8g2.begin();
  /*RTC.adjust(DateTime(F(__DATE__),F(__TIME__)));
    rtc.adjust(DateTime(2020, 5, 14, 9, 27, 0));
    to set time on boot
  */
  #define timestr " DATE  TIME"

   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.printf("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  configTzTime("JST-9", "ntp.nict.jp", "time.google.com");
}

void loop() {
//this part for display nowtime on serialmonitor
//  DateTime now = RTC.now();
//  sprintf(t, " %02d/%02d %02d:%02d:%02d",  now.month(), now.day(), now.hour(), now.minute(), now.second());
   
//  Serial.print(F("Date/Time: "));
//  Serial.println(t);

time_t t;
  struct tm *tm;
  static const char *wd[7] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};

  t = time(NULL);
  tm = localtime(&t);
  Serial.printf("ESP8266/Arduino ver%s :  %04d/%02d/%02d(%s) %02d:%02d:%02d\n",
        __STR(ARDUINO_ESP8266_GIT_DESC),
        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
        wd[tm->tm_wday],
        tm->tm_hour, tm->tm_min, tm->tm_sec);
  
//this part for display nowtime on LCD
  sprintf(s, " %02d:%02d",  tm->tm_hour, tm->tm_min); 
  u8g2.clearBuffer();                   // clear the internal memory
  u8g2.setFont(u8g2_font_fur30_tf);  // choose a suitable font  u8g2_font_8x13_tf
  u8g2.drawStr(1,32,s); // write time
  u8g2.sendBuffer();
  delay(500);
  u8g2.clearBuffer();
  sprintf(s, " %02d %02d",  tm->tm_hour, tm->tm_min);
  u8g2.drawStr(1,32,s); // write time
  u8g2.sendBuffer();
  delay(500);
}
