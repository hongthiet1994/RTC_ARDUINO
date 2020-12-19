#include "Keypad.h"
#include <LiquidCrystal_I2C.h>
#include "module_keypad.h"
#include "module_display.h"
#include "module_realtime.h"


extern LiquidCrystal_I2C lcd;
extern uint32_t ui32_current_screen;
extern tmElements_t time_data;
int n = 3;     //
int state = 0; //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
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
            key = temp;
        }
    }
    if ((int)keypad.getState() == HOLD)
    {
        state++;
        state = constrain(state, 1, n - 1);
        delay(HOLD_DELAY);
    }

    if ((int)keypad.getState() == RELEASED)
    {
        key += state;
        state = 0;
        //Xuất lên Máy tính để xem kết quả
        Serial.println(key);
        process_key(key);
    }
    delay(100);
}

void process_key(uint32_t key)
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
                ui32_current_screen=SET_HOURS_SCREEN;
            }
            else if (ui32_current_screen==SET_HOURS_SCREEN)
            {
                ui32_current_screen=SET_MINUTE_SCREEN;
            }
            else if (ui32_current_screen==SET_MINUTE_SCREEN)
            {
                ui32_current_screen=SET_SECONDS_SCREEN;
            }
            else if (ui32_current_screen==SET_SECONDS_SCREEN)
            {
                ui32_current_screen=SET_DAY_SCREEN;
            }
            else if (ui32_current_screen==SET_MONTH_SCREEN)
            {
                ui32_current_screen=SET_YEAR_SCREEN;
            }                       
            break;   
        case KEY_UP:
            change_value_wday_up();
            Serial.println("button up");
            break;
        case KEY_DOWN:
            change_value_wday_down();
            Serial.println("button down");
            break;
        default:
            break;
    }
}


void change_value_wday_up() 
{
    switch (ui32_current_screen)
    {
    case SET_WDAY_SCREEN:
        time_data.Wday = validate_wday(time_data.Wday+1);  
        Serial.println(time_data.Wday);        
        break;
    default:
        break;
    }
}
void change_value_wday_down()
{
    switch (ui32_current_screen)
    {
    case SET_WDAY_SCREEN:
        time_data.Wday = validate_wday(time_data.Wday-1);  
        Serial.println(time_data.Wday);      
        break;
    default:
        break;
    }

}