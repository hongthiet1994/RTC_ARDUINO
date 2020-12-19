
#include <Arduino.h>
#include <DS1307RTC.h>
#include "module_realtime.h"
#include "module_display.h"

tmElements_t time_data;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void set_time()
{
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