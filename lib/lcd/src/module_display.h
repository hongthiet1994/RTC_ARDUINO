#include <TimeLib.h>

#define ROW_WDAY            0
#define COLUMN_WDAY         1

#define ROW_HOUR            1
#define COLUMN_HOUR         4

#define ROW_MINUTE          1
#define COLUMN_MINUTE       7


#define ROW_SECOND          1
#define COLUMN_SECOND       10


#define ROW_DAY            0
#define COLUMN_DAY         5


#define ROW_MONTH            0
#define COLUMN_MONTH          8

#define ROW_YEAR            0
#define COLUMN_YEAR          13




enum SCREEN_DISPLAY
{
    MAIN_SCREEN,
    SET_WDAY_SCREEN,
    SET_HOURS_SCREEN,
    SET_MINUTE_SCREEN,
    SET_SECONDS_SCREEN,
    SET_DAY_SCREEN,
    SET_MONTH_SCREEN,
    SET_YEAR_SCREEN,
    SET_ALARM_SCREEN,
    SET_STATE_ALARM_SCREEN,
    SET_HOURS_ALARM_SCREEN,
    SET_MINUTES_ALARM_SCREEN,
    SET_REPEAT_ALARM_SCREEN,
    SET_WDAY_ALARM_SCREEN
};
void init_lcd();
void display_time_lcd(tmElements_t tm);
void display_test();
void blink_value(uint32_t ui32_type_display);
void display_0_before(uint32_t ui32_value);
