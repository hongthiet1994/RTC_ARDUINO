#include <TimeLib.h>
#include "module_display.h"

extern char daysOfTheWeek[7][12];

void display_time_lcd(tmElements_t tm)
{
  lcd.setCursor(4, 1);
    if(tm.Hour<=9)
    {
      lcd.print("0");
      lcd.print(tm.Hour);
    }
    else 
    {
     lcd.print(tm.Hour); 
    }
    lcd.print(':');
    if(tm.Minute<=9)
    {
      lcd.print("0");
      lcd.print(tm.Minute);
    }
    else {
     lcd.print(tm.Minute); 
    }
    lcd.print(':');
    if(tm.Second<=9)
    {
      lcd.print("0");
      lcd.print(tm.Second);
    }
    else {
     lcd.print(tm.Second); 
    }
    lcd.print("   ");

    lcd.setCursor(1, 0);
    lcd.print(daysOfTheWeek[tm.Wday]);
    lcd.print(",");
    if(tm.Day<=9)
    {
      lcd.print("0");
      lcd.print(tm.Day);
    }
    else {
     lcd.print(tm.Day); 
    }
    lcd.print('/');
    if(tm.Month<=9)
    {
      lcd.print("0");
      lcd.print(tm.Month);
    }
    else {
     lcd.print(tm.Month); 
    }
    lcd.print('/');
    lcd.print(tmYearToCalendar(tm.Year));
}