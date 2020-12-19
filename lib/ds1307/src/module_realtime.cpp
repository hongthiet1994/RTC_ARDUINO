
#include "module_realtime.h"
#include "module_display.h"


tmElements_t time_data;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


void set_time()
{

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