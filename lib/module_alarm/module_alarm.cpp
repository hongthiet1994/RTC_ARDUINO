#include "Arduino.h"
#include "module_alarm.h"
#include "TimeLib.h"
#include <LiquidCrystal_I2C.h>
#include "module_display.h"
#include "module_eeprom.h"


extern uint32_t ui32_current_screen;
extern tmElements_t time_data;
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

uint32_t ui32_status_alarm = false;
uint32_t ui32_counter_time_turn_on_alarm = 0;

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
    if (data_alarm[ui32_current_alarm].data.state == ALARM_ON)
    {
        lcd.print(state_alarm[ALARM_ON]);
    }
    else
    {
        lcd.print(state_alarm[ALARM_OFF]);        
    }
    lcd.setCursor(COLUMN_HOUR_ALARM,ROW_HOUR_ALARM);
    display_0_before(data_alarm[ui32_current_alarm].data.hour);
    lcd.print(":");
    lcd.setCursor(COLUMN_MINUTE_ALARM,ROW_MINUTE_ALARM);
    display_0_before(data_alarm[ui32_current_alarm].data.minute);

    lcd.setCursor(COLUMN_REPEAT,ROW_REPEAT);

    if (data_alarm[ui32_current_alarm].data.repeat == REPEAT)
    {
        lcd.print(repeat_alarm[REPEAT]);
    }
    else
    {
        lcd.print(repeat_alarm[NOREPEAT]);        
    }

    lcd.setCursor(COLUMN_WDAY_ALARM,ROW_WDAY_ALARM);
    lcd.print(daysOfTheWeek[data_alarm[ui32_current_alarm].data.wday_repeat]);
    //display_0_before((time_data.Year+1970)-2000);  
}

void check_alarm()
{
    uint32_t i = 0;
    if(ui32_current_screen == MAIN_SCREEN)
    {
        for (i = 0; i < NUMBER_OF_ALARM; i++)
        {
            if (data_alarm[i].data.state == ALARM_ON)
            {
                
                if (data_alarm[i].data.repeat == REPEAT)  // all day
                {
                    
                    if (data_alarm[i].data.wday_repeat == 0) // all day
                    {
                        if ((data_alarm[i].data.hour == time_data.Hour) && (data_alarm[i].data.minute == time_data.Minute)&& (time_data.Second==0))
                        {
                            ui32_current_screen = TURN_ON_TIMER_SCREEN;
                            lcd.clear();
                            lcd.print("TIMER ");
                            lcd.print(i);
                            lcd.print(" ON");
                            ui32_counter_time_turn_on_alarm = 0;
                            ui32_status_alarm = true;
                            turn_on_buzzer();
                        } 

                    }
                    else
                    {
                        if (data_alarm[i].data.wday_repeat == time_data.Wday) 
                        {
                            if ((data_alarm[i].data.hour == time_data.Hour) && (data_alarm[i].data.minute == time_data.Minute) && (time_data.Second==0))
                            {
                                ui32_current_screen = TURN_ON_TIMER_SCREEN;
                                lcd.clear();
                                lcd.print("TIMER ");
                                lcd.print(i);
                                lcd.print(" ON");
                                ui32_counter_time_turn_on_alarm = 0;
                                ui32_status_alarm = true;
                                turn_on_buzzer();
                            } 
                        }
                        
                    }
                    
                    
                }
                else
                {
                    if ((data_alarm[i].data.hour == time_data.Hour) && (data_alarm[i].data.minute == time_data.Minute)&& (time_data.Second==0))
                    {
                        ui32_current_screen = TURN_ON_TIMER_SCREEN;
                        data_alarm[i].data.state = ALARM_OFF;
                        write_data_alarm();
                        lcd.clear();
                        lcd.print("TIMER ");
                        lcd.print(i);
                        lcd.print(" ON");
                        ui32_counter_time_turn_on_alarm = 0;
                        ui32_status_alarm = true;
                        turn_on_buzzer();
                    } 
                }
                
                
                                        
            }       
        }
    }
}

void turn_on_alarm()
{
   if (ui32_status_alarm == true)
   {
       ui32_counter_time_turn_on_alarm++;
       if (ui32_counter_time_turn_on_alarm>=TIME_TURN_ON_ALARM)
       {
           ui32_status_alarm = false;
           lcd.clear();
           ui32_current_screen = MAIN_SCREEN;
           turn_off_buzzer();
       }
       
   }
    
}

void init_buzzer()
{
    pinMode(PIN_BUZZER,OUTPUT);
    digitalWrite(PIN_BUZZER,HIGH);
}

void turn_on_buzzer()
{
    digitalWrite(PIN_BUZZER,LOW);
}

void turn_off_buzzer()
{
    digitalWrite(PIN_BUZZER,HIGH);
}
