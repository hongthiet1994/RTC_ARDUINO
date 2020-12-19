#include <TimeLib.h>

#define ROW_WDAY        0
#define COLUMN_WDAY     1

enum SCREEN_DISPLAY
{
    MAIN_SCREEN,
    SET_WDAY_SCREEN,
    SET_HOURS_SCREEN,
    SET_MINUTE_SCREEN,
    SET_SECONDS_SCREEN,
    SET_DAY_SCREEN,
    SET_MONTH_SCREEN,
    SET_YEAR_SCREEN
};
void init_lcd();
void display_time_lcd(tmElements_t tm);
void display_test();
void blink_wday(uint32_t ui32_wday,uint32_t ui32_type_display);