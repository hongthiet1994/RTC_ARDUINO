
#include <Arduino.h>
#include <DS1307RTC.h>
#include "module_realtime.h"
#include "module_display.h"

tmElements_t time_data;



void set_time()
{
    time_data.Hour = 23;
    time_data.Minute = 20;
    time_data.Day= 19;
    time_data.Month = 12;
    time_data.Year = 50;
    time_data.Wday = 6;
    RTC.write(time_data);
}
void print2digits(int number)
{
  if (number >= 0 && number < 10)
  {
    Serial.write('0');
  }
  Serial.print(number);
}
void print_time()
{
  print2digits(time_data.Hour);
  Serial.write(':');
  print2digits(time_data.Minute);
  Serial.write(':');
  print2digits(time_data.Second);
  Serial.write(' ');
  print2digits(time_data.Wday);
  Serial.print(", Date (D/M/Y) = ");
  Serial.print(time_data.Day);
  Serial.write('/');
  Serial.print(time_data.Month);
  Serial.write('/');
  Serial.print(tmYearToCalendar(time_data.Year));
  Serial.println(); 
}
void get_time()
{
    if (RTC.read(time_data))
    {
        //print_time();    
        display_time_lcd(time_data);
    }
    else
    {
        if (RTC.chipPresent())
        {
            Serial.println("The DS1307 is stopped.  Please run the SetTime");
            Serial.println("example to initialize the time and begin running.");
        }
        else
        {
            Serial.println("DS1307 read error!  Please check the circuitry.");
            Serial.println();
        }
        delay(1000);
    }
}