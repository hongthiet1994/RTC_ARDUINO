#include <Arduino.h>
#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>
#include "module_display.h"


LiquidCrystal_I2C lcd(0x27,16,2);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
//extern char daysOfTheWeek[7][12];

void init_lcd()
{
    lcd.init(); 
    lcd.backlight();
    delay(200);
}
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
    else 
    {
        lcd.print(tm.Minute); 
    }
    lcd.print(':');
    if(tm.Second<=9)
    {
        lcd.print("0");
        lcd.print(tm.Second);
    }
    else 
    {
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
    else 
    {
        lcd.print(tm.Day); 
    }
    lcd.print('/');
    if(tm.Month<=9)
    {
        lcd.print("0");
        lcd.print(tm.Month);
    }
    else 
    {
        lcd.print(tm.Month); 
    }
    lcd.print('/');
    lcd.print(tmYearToCalendar(tm.Year));
}

void display_test()
{
    lcd.setCursor(0, 0);
    lcd.print("Nguyen hong ");
    lcd.setCursor(0, 1);
    lcd.print("thiet hong ");
}
