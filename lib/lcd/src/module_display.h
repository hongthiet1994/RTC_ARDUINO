#include <TimeLib.h>


enum SCREEN_DISPLAY
{
    MAIN_SCREEN,
    SET_WDAY_SCREEN
};
void init_lcd();
void display_time_lcd(tmElements_t tm);
void display_test();