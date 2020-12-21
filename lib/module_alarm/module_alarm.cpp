#include "Arduino.h"
#include "module_alarm.h"
#include <LiquidCrystal_I2C.h>
#include "module_display.h"


extern char daysOfTheWeek[8][12];
extern LiquidCrystal_I2C lcd;
uint32_t ui32_current_alarm = 0;

enum STATE_ALARM
{
	ALARM_OFF,
    ALARM_ON
};

enum REPEAT_ALARM
{
	NOREPEAT,
    REPEAT
    
};

char state_alarm[2][4] = {"OFF","ON"};
char repeat_alarm[2][6] = {"NOREP","REP"};



ALARM_DATA data_alarm[NUMBER_OF_ALARM];


uint32_t validate_number_of_alarm(int32_t ui32_alarm)
{
    if (ui32_alarm >= NUMBER_OF_ALARM)
    {
        ui32_alarm = 0;
    }
    else if (ui32_alarm < 0)
    {
        ui32_alarm = (NUMBER_OF_ALARM -1);      
    }
    return ui32_alarm;
}


void display_set_alarm()
{    
    lcd.setCursor(1,0);
    lcd.print("ALARM ");    
    lcd.setCursor(COLUMN_NUM_OF_ALARM,ROW_NUM_OF_ALARM);  
    lcd.print(ui32_current_alarm);  
    lcd.print(":");
    lcd.setCursor(COLUMN_STATE_ALARM,ROW_STATE_ALARM);
    if (data_alarm[ui32_current_alarm].state == ALARM_ON)
    {
        lcd.print(state_alarm[ALARM_ON]);
    }
    else
    {
        lcd.print(state_alarm[ALARM_OFF]);        
    }
    lcd.setCursor(COLUMN_HOUR_ALARM,ROW_HOUR_ALARM);
    display_0_before(data_alarm[ui32_current_alarm].hour);
    lcd.print(":");
    lcd.setCursor(COLUMN_MINUTE_ALARM,ROW_MINUTE_ALARM);
    display_0_before(data_alarm[ui32_current_alarm].minute);

    lcd.setCursor(COLUMN_REPEAT,ROW_REPEAT);

    if (data_alarm[ui32_current_alarm].repeat == REPEAT)
    {
        lcd.print(repeat_alarm[REPEAT]);
    }
    else
    {
        lcd.print(repeat_alarm[NOREPEAT]);        
    }

    lcd.setCursor(COLUMN_WDAY_ALARM,ROW_WDAY_ALARM);
    lcd.print(daysOfTheWeek[data_alarm[ui32_current_alarm].wday_repeat]);
    

    //display_0_before((time_data.Year+1970)-2000);  
}