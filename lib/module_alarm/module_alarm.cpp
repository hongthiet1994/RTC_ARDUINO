#include "Arduino.h"
#include "module_alarm.h"



struct ALARM_DATA
{
    uint32_t state;
    uint32_t hour;
    uint32_t minute;
    uint32_t repeat;
    char label[LEN_LABEL];
    char wday[LEN_WEEKDAY];
};

ALARM_DATA data_alarm;