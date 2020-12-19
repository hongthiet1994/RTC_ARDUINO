#include <Arduino.h>
#include "TimeLib.h"
#include <arduino-timer.h>
#include "module_timer.h"
#include "module_display.h"



extern tmElements_t time_data;
extern uint32_t ui32_current_screen;
auto timer = timer_create_default(); // create a timer with default settings
uint32_t ui32_counter_timer_500ms = 0;

void init_timer()
{    // call the toggle_led function every 1000 millis (1 second)
  timer.every(500, function_timer_500ms);
}

bool function_timer_500ms()
{
    ui32_counter_timer_500ms++;
    switch (ui32_current_screen)
    {
        case SET_WDAY_SCREEN:
            if (ui32_counter_timer_500ms%2==0)
            {
                blink_wday(time_data.Wday,NULL);
            }
            else
            {
                blink_wday(time_data.Wday,!NULL);
            }       
            break;
        
        default:
            break;
    }
    return true; // repeat? true
}


void tick_timer()
{
    timer.tick(); // tick the timer
}