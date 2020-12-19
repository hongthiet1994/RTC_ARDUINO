#include <Arduino.h>
#include <arduino-timer.h>
#include "module_timer.h"

auto timer = timer_create_default(); // create a timer with default settings

void init_timer()
{    // call the toggle_led function every 1000 millis (1 second)
  timer.every(1000, function_timer_1_second);
}

bool function_timer_1_second()
{
    
    return true; // repeat? true
}


void tick_timer()
{
    timer.tick(); // tick the timer
}