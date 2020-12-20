
#include <Arduino.h>
#include <DS1307RTC.h>
#include "module_realtime.h"
#include "module_display.h"

extern uint32_t ui32_current_screen;
tmElements_t time_data;


char daysOfTheWeek[8][12] = {"   ","Mon", "Tue", "Wed", "Thu", "Fri", "Sat","Sun"};

uint32_t validate_months(int32_t i32_value)
{
    if (i32_value > MAX_OF_MONTH)
    {
        i32_value = 0;
    }
    else if (i32_value < 0)
    {
        i32_value = MAX_OF_MONTH;
    }
}

uint32_t validate_days(int32_t i32_value)
{
    if (i32_value > MAX_OF_DAY)
    {
        i32_value = 0;
    }
    else if (i32_value < 0)
    {
        i32_value = MAX_OF_DAY;
    }
}


uint32_t validate_hours(int32_t i32_value)
{
    if (i32_value > MAX_OF_HOUR)
    {
        i32_value = 0;
    }
    else if (i32_value < 0)
    {
        i32_value = MAX_OF_HOUR;
    }
}

uint32_t validate_minutes_seconds(int32_t i32_value)
{
    if (i32_value > MAX_OF_MINUTE)
    {
        i32_value = 0;
    }
    else if (i32_value < 0)
    {
        i32_value = MAX_OF_MINUTE;
    }   
}

uint32_t validate_wday(int ui32_wday)
{
    if (ui32_wday>MAX_OF_WDAY)
    {
        return ui32_wday = 1;
    }
    else if (ui32_wday<1)
    {
        return ui32_wday = MAX_OF_WDAY;
    }
    else
    {
        return ui32_wday;
    }   
}

void set_time()
{
    time_data.Hour = 00;
    time_data.Minute = 12;
    time_data.Second = 30;
    time_data.Day= 20;
    time_data.Month = 12;
    time_data.Year = 50;
    time_data.Wday = 7;
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
        print_time();    
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


