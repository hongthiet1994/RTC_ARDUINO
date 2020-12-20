

#define MAX_OF_MONTH              12
#define MAX_OF_DAY                31
#define MAX_OF_HOUR               24
#define MAX_OF_MINUTE             60
#define MAX_OF_SECOND             60 
#define MAX_OF_WDAY                7
#define MAX_OF_YEARS              99


void set_time();
void get_time();
uint32_t validate_wday(int ui32_wday);
uint32_t validate_minutes_seconds(int32_t i32_value);
uint32_t validate_months(int32_t i32_value);
uint32_t validate_hours(int32_t i32_value);
uint32_t validate_days(int32_t i32_value);
uint32_t validate_years(int32_t i32_value);