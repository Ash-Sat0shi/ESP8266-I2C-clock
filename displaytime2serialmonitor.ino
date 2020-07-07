#include <RTClib.h>
#include <Wire.h>
char t[32];
RTC_DS3231 RTC;
void setup() 
{
  Serial.begin(9600);
  Wire.begin();

  RTC.begin();
  RTC.adjust(DateTime(F(__DATE__),F(__TIME__)));
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  

}

void loop()
{
  DateTime now = RTC.now();

  sprintf(t, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());  
  
  Serial.print(F("Date/Time: "));
  Serial.println(t);

  delay(1000);
}
