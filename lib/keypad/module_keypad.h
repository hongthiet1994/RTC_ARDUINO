



#define NUMBER_OF_ROWS              4
#define NUMBER_OF_COLUMNS           4
#define HOLD_DELAY                  300

#define KEY_SETING                  'A'
#define KEY_UP                      'B' 
#define KEY_DOWN                    'C' 
#define KEY_ENTER                   'D'

void get_key();
void process_key(uint32_t key);
void change_value_up();
void change_value_down();