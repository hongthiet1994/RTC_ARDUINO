#include "Keypad.h"
#include <LiquidCrystal_I2C.h>
#include "module_keypad.h"
#include "module_display.h"
#include "module_realtime.h"

uint32_t ui32_hold_key_detect = false;
extern char daysOfTheWeek[8][12];
extern LiquidCrystal_I2C lcd;
extern uint32_t ui32_current_screen;
extern tmElements_t time_data;
uint32_t ui32_counter_hold_key = 0;
char key = 0;

//Định nghĩa các giá trị trả về
char keys[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

byte columnPins[NUMBER_OF_COLUMNS] = {5, 6, 7, 8};
byte rowPins[NUMBER_OF_ROWS] = {9, 10, 11, 12};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, NUMBER_OF_ROWS, NUMBER_OF_COLUMNS);

void get_key()
{
    char temp = keypad.getKey();
    if ((int)keypad.getState() == PRESSED)
    {
        if (temp != 0)
        {
            ui32_hold_key_detect = false;
            key = temp;
        }
    }
    if ((int)keypad.getState() == HOLD)
    {
        ui32_counter_hold_key++;
        //Serial.println("hold key");
        if ((ui32_counter_hold_key>=MAX_HOLD_KEY) && (ui32_hold_key_detect == false))
        {
            ui32_counter_hold_key = 0;
            ui32_hold_key_detect = true;
            Serial.print("Hold key : ");
            Serial.println(key);
            process_hold_key(key);
        }
        delay(HOLD_DELAY);
    }
    else
    {
        if ((int)keypad.getState() == RELEASED && (ui32_hold_key_detect==false))
        {
            ui32_counter_hold_key = 0;
            ui32_hold_key_detect = false;
            Serial.print("Press key : ");
            Serial.println(key);
            process_press_key(key);    
        }        
    }
    delay(100);
}

void process_press_key(uint32_t key)
{
    switch (key)
    {
        case KEY_SETING:
            if (ui32_current_screen==MAIN_SCREEN)
            {
                ui32_current_screen=SET_WDAY_SCREEN;                
            }
            else if (ui32_current_screen==SET_WDAY_SCREEN)
            {
                ui32_current_screen = SET_HOURS_SCREEN;    
                lcd.setCursor(COLUMN_WDAY,ROW_WDAY);
                lcd.print(daysOfTheWeek[time_data.Wday]);            
            }
            else if (ui32_current_screen==SET_HOURS_SCREEN)
            {
                ui32_current_screen = SET_MINUTE_SCREEN;   
                lcd.setCursor(COLUMN_HOUR,ROW_HOUR);
                display_0_before(time_data.Hour); 
                             
            }
            else if (ui32_current_screen==SET_MINUTE_SCREEN)
            {
                ui32_current_screen = SET_SECONDS_SCREEN;   
                lcd.setCursor(COLUMN_MINUTE,ROW_MINUTE);
                display_0_before(time_data.Minute);             
            } 

            else if (ui32_current_screen==SET_SECONDS_SCREEN)
            {
                ui32_current_screen = SET_DAY_SCREEN;   
                lcd.setCursor(COLUMN_SECOND,ROW_SECOND);
                display_0_before(time_data.Second);              
            } 

            else if (ui32_current_screen==SET_DAY_SCREEN)
            {
                ui32_current_screen = SET_MONTH_SCREEN; 
                lcd.setCursor(COLUMN_DAY,ROW_DAY);
                display_0_before(time_data.Day);               
            } 

            else if (ui32_current_screen==SET_MONTH_SCREEN)
            {
                ui32_current_screen = SET_YEAR_SCREEN; 
                lcd.setCursor(COLUMN_MONTH,ROW_MONTH);
                display_0_before(time_data.Month);               
            }   
            else if (ui32_current_screen==SET_YEAR_SCREEN)
            {
                ui32_current_screen = MAIN_SCREEN; 
                lcd.setCursor(COLUMN_YEAR,ROW_YEAR);
                display_0_before((time_data.Year+1970)-2000);                  
            }         
            
                      
            break;   
        case KEY_UP:
            change_value_up();
            Serial.println("button up");
            break;
        case KEY_DOWN:
            change_value_down();
            Serial.println("button down");
            break;
        case KEY_ENTER:
            set_time();   
            lcd.clear();
            ui32_current_screen=MAIN_SCREEN;         
            break;
        default:
            break;
    }
}

void process_hold_key(uint32_t key)
{
    switch (key)
    {
        case KEY_SETING: 
            ui32_current_screen = SET_TIMER_SCREEN;  
            display_set_timer();       
            break;   
        default:
            break;
    }
}


void change_value_up() 
{
    switch (ui32_current_screen)
    {
        case SET_WDAY_SCREEN:
            time_data.Wday = validate_wday(time_data.Wday+1);  
            Serial.println(time_data.Wday);        
            break;
        case SET_HOURS_SCREEN:
            time_data.Hour = validate_hours(time_data.Hour+1);
            Serial.println(time_data.Hour); 
            break;
        case SET_MINUTE_SCREEN:
            time_data.Minute = validate_minutes_seconds(time_data.Minute+1);
            Serial.println(time_data.Minute); 
            break;
        case SET_SECONDS_SCREEN:
            time_data.Second = validate_minutes_seconds(time_data.Second+1);
            Serial.println(time_data.Second); 
            break;
        case SET_DAY_SCREEN:
            time_data.Day = validate_days(time_data.Day+1);
            Serial.println(time_data.Day); 
            break;
        case SET_MONTH_SCREEN:
            time_data.Month = validate_months(time_data.Month+1);
            Serial.println(time_data.Month);
        case SET_YEAR_SCREEN:
            time_data.Year = validate_years(time_data.Year+1);
            Serial.println(time_data.Year); 
            break;
        default:
            break;
    }
}
void change_value_down()
{
    switch (ui32_current_screen)
    {
        case SET_WDAY_SCREEN:
            time_data.Wday = validate_wday(time_data.Wday-1);  
            Serial.println(time_data.Wday);      
            break;
        case SET_HOURS_SCREEN:
            time_data.Hour = validate_hours(time_data.Hour-1);
            break;
        case SET_MINUTE_SCREEN:
            time_data.Minute = validate_minutes_seconds(time_data.Minute-1);
            Serial.println(time_data.Minute); 
            break;
        case SET_SECONDS_SCREEN:
            time_data.Second = validate_minutes_seconds(time_data.Second-1);
            Serial.println(time_data.Second); 
            break;
        case SET_DAY_SCREEN:
            time_data.Day = validate_days(time_data.Day-1);
            Serial.println(time_data.Day); 
            break;
        case SET_MONTH_SCREEN:
            time_data.Month = validate_months(time_data.Month-1);
            Serial.println(time_data.Month);
        case SET_YEAR_SCREEN:
            time_data.Year = validate_years(time_data.Year-1);
            Serial.println(time_data.Year); 
            break;
        default:
            break;
    }

}