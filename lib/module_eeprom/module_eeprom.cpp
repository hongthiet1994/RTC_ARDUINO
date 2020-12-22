#include "Arduino.h"
#include "module_eeprom.h"
#include <EEPROM.h>
#include "module_alarm.h"

extern ALARM_DATA data_alarm[NUMBER_OF_ALARM];

void write_data_alarm()
{
    uint32_t i =0,j = 0;
    uint32_t ui32_counter_addr = 0;
    uint32_t ui32_size_of_data_alarm = sizeof(ALARM_DATA);
    Serial.print("len alarm data");
    Serial.println(ui32_size_of_data_alarm);
    for (i=0; i < NUMBER_OF_ALARM; i++)
    {       
        for (j= 0; j < ui32_size_of_data_alarm; j++)
        {
            EEPROM.write(ui32_counter_addr, data_alarm[i].bufferDeviceinfor[j]); 
            ui32_counter_addr++;            
        }        
    }
}

void read_data_alarm()
{
    uint32_t i =0,j = 0;
    uint32_t ui32_counter_addr = 0;
    uint32_t ui32_size_of_data_alarm = sizeof(ALARM_DATA);
    Serial.print("len alarm data");
    Serial.println(ui32_size_of_data_alarm);
    for (i=0; i < NUMBER_OF_ALARM; i++)
    {       
        for (j= 0; j < ui32_size_of_data_alarm; j++)
        {
            data_alarm[i].bufferDeviceinfor[j] = EEPROM.read(ui32_counter_addr); 
            ui32_counter_addr++;            
        }        
    }
}