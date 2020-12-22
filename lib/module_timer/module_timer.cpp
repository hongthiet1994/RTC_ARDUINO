#include <Arduino.h>
#include "TimeLib.h"
#include <arduino-timer.h>
#include "module_timer.h"
#include "module_display.h"
#include "module_realtime.h"
#include "module_alarm.h"


extern tmElements_t time_data;
extern uint32_t ui32_current_screen;
auto timer = timer_create_default(); // create a timer with default settings
uint32_t ui32_counter_timer_250ms = 0;

void init_timer()
{    // call the toggle_led function every 1000 millis (1 second)
  timer.every(250, function_timer_250ms);
}

bool function_timer_250ms()
{
    ui32_counter_timer_250ms++;
    switch (ui32_current_screen)
    {
        case MAIN_SCREEN:
            get_time(); 
            break;
        case SET_ALARM_SCREEN:
             display_set_alarm(); 
            break;
        default:
            if (ui32_counter_timer_250ms%2==0)
            {
                blink_value(NULL);
            }
            else
            {
                blink_value(!NULL);
            } 
            break;
    }
    return true; // repeat? true
}


void tick_timer()
{
    timer.tick(); // tick the timer
}