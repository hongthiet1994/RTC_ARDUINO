
#define TIME_TURN_ON_ALARM           4*10

#define ROW_NUM_OF_ALARM          0
#define COLUMN_NUM_OF_ALARM       7

#define ROW_STATE_ALARM            0
#define COLUMN_STATE_ALARM        12

#define ROW_HOUR_ALARM            1
#define COLUMN_HOUR_ALARM         0

#define ROW_MINUTE_ALARM            1
#define COLUMN_MINUTE_ALARM         3

#define ROW_REPEAT                  1
#define COLUMN_REPEAT               6


#define ROW_WDAY_ALARM              1
#define COLUMN_WDAY_ALARM               12


#define LEN_LABEL                 8
#define LEN_WEEKDAY               4
#define NUMBER_OF_ALARM                 5


typedef union
{
	struct alarm_data
	{
        int32_t state;
        int32_t hour;
        int32_t minute;
        int32_t repeat;
        int32_t wday_repeat;
	} data;
	char bufferDeviceinfor[sizeof(alarm_data)];
} ALARM_DATA;

void display_set_alarm();
uint32_t validate_number_of_alarm(int32_t ui32_alarm);
void check_alarm();