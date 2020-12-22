#include <Arduino.h>
#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>
#include "module_display.h"
#include "module_alarm.h"

uint32_t ui32_current_screen = MAIN_SCREEN;
LiquidCrystal_I2C lcd(0x27,16,2);

extern ALARM_DATA data_alarm[NUMBER_OF_ALARM];
extern uint32_t ui32_current_alarm;
extern char state_alarm[2][4];
extern char repeat_alarm[2][6];
extern char daysOfTheWeek[8][12];
extern tmElements_t time_data;
extern char daysOfTheWeek[8][12];

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

void display_0_before(uint32_t ui32_value)
{
    if (ui32_value<10)
    {
        lcd.print('0');
        lcd.print(ui32_value);
    }
    else
    {        
        lcd.print(ui32_value);
    }
    
    

}
void blink_value(uint32_t ui32_type_display)
{
    
    switch (ui32_current_screen)
    {
        case SET_WDAY_SCREEN:
            if (ui32_type_display == NULL)
            {
                lcd.setCursor(COLUMN_WDAY,ROW_WDAY);
                lcd.print("   ");
            }
            else
            {
                lcd.setCursor(COLUMN_WDAY,ROW_WDAY);
                lcd.print(daysOfTheWeek[time_data.Wday]);
            }
        break;

        case SET_HOURS_SCREEN:
            if (ui32_type_display == NULL)
            {
                lcd.setCursor(COLUMN_HOUR,ROW_HOUR);
                lcd.print("  ");
            }
            else
            {
                lcd.setCursor(COLUMN_HOUR,ROW_HOUR);
                display_0_before(time_data.Hour);               
            }
        break;

        case SET_MINUTE_SCREEN:
            if (ui32_type_display == NULL)
            {
                lcd.setCursor(COLUMN_MINUTE,ROW_MINUTE);
                lcd.print("  ");
            }
            else
            {
                lcd.setCursor(COLUMN_MINUTE,ROW_MINUTE);
                display_0_before(time_data.Minute);                
            }
        break;
        case SET_SECONDS_SCREEN:
            if (ui32_type_display == NULL)
            {
                lcd.setCursor(COLUMN_SECOND,ROW_SECOND);
                lcd.print("  ");
            }
            else
            {
                lcd.setCursor(COLUMN_SECOND,ROW_SECOND);
                display_0_before(time_data.Second);                
            }
        break;

        case SET_DAY_SCREEN:
            if (ui32_type_display == NULL)
            {
                lcd.setCursor(COLUMN_DAY,ROW_DAY);
                lcd.print("  ");
            }
            else
            {
                lcd.setCursor(COLUMN_DAY,ROW_DAY);
                display_0_before(time_data.Day);                
            }
        break;

        case SET_MONTH_SCREEN:
            if (ui32_type_display == NULL)
            {
                lcd.setCursor(COLUMN_MONTH,ROW_MONTH);
                lcd.print("  ");
            }
            else
            {
                lcd.setCursor(COLUMN_MONTH,ROW_MONTH);
                display_0_before(time_data.Month);                
            }
        break;
        case SET_YEAR_SCREEN:
            if (ui32_type_display == NULL)
            {
                lcd.setCursor(COLUMN_YEAR,ROW_YEAR);
                lcd.print("  ");
            }
            else
            {
                lcd.setCursor(COLUMN_YEAR,ROW_YEAR);
                display_0_before((time_data.Year+1970)-2000);                
            }
        break;

        case SET_STATE_ALARM_SCREEN:
            lcd.setCursor(COLUMN_STATE_ALARM,ROW_STATE_ALARM);
            if (ui32_type_display == NULL)
            {                
                lcd.print("   ");
            }
            else
            {               
                lcd.print(state_alarm[data_alarm[ui32_current_alarm].data.state]);                
            }
        break;

        case SET_HOURS_ALARM_SCREEN:
            lcd.setCursor(COLUMN_HOUR_ALARM,ROW_HOUR_ALARM);
            if (ui32_type_display == NULL)
            {                
                lcd.print("  ");
            }
            else
            {                
                display_0_before(data_alarm[ui32_current_alarm].data.hour);                
            }
        break;
        case SET_MINUTES_ALARM_SCREEN:
             lcd.setCursor(COLUMN_MINUTE_ALARM,ROW_MINUTE_ALARM);
            if (ui32_type_display == NULL)
            {                
                lcd.print("  ");
            }
            else
            {                
                display_0_before(data_alarm[ui32_current_alarm].data.minute);                
            }
        break;

        case SET_REPEAT_ALARM_SCREEN:
            lcd.setCursor(COLUMN_REPEAT,ROW_REPEAT);
            if (ui32_type_display == NULL)
            {              
                lcd.print("     ");
            }
            else
            {
                lcd.print(repeat_alarm[data_alarm[ui32_current_alarm].data.repeat]);              
            }
        break;

        case SET_WDAY_ALARM_SCREEN:
            lcd.setCursor(COLUMN_WDAY_ALARM,ROW_WDAY_ALARM);
            if (ui32_type_display == NULL)
            {                
                lcd.print("   ");
            }
            else
            {                
                lcd.print(daysOfTheWeek[data_alarm[ui32_current_alarm].data.wday_repeat]);              
            }
        break;

    default:
        break;
    }
}


