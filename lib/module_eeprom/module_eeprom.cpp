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
    for ( i = 0; i < NUMBER_OF_ALARM; i++)
    {
        Serial.print("TIMER ");
        Serial.println(i);
        Serial.print("Hour : ");
        Serial.println(data_alarm[i].data.hour);              
        Serial.print("Minute : ");
        Serial.println(data_alarm[i].data.minute);
        Serial.print("Repeat : ");
        Serial.println(data_alarm[i].data.repeat);
        Serial.print("State : ");
        Serial.println(data_alarm[i].data.state);
        Serial.print("Wday_repeat : ");
        Serial.println(data_alarm[i].data.wday_repeat);
        if ((data_alarm[i].data.hour<0)||(data_alarm[i].data.hour>60))
        {
            data_alarm[i].data.hour = 0;
        }   
        if ((data_alarm[i].data.minute<0)||(data_alarm[i].data.minute>60))
        {
            data_alarm[i].data.minute = 0;
        }
        if ((data_alarm[i].data.repeat<0)||(data_alarm[i].data.repeat>1))
        {
            data_alarm[i].data.repeat = 0;
        } 
        if ((data_alarm[i].data.state<0)||(data_alarm[i].data.state>1))
        {
            data_alarm[i].data.state = 0;
        }  
        if ((data_alarm[i].data.wday_repeat<0)||(data_alarm[i].data.wday_repeat>7))
        {
            data_alarm[i].data.wday_repeat = 0;
        } 
        write_data_alarm();  
    }
    
    // if (data_alarm[0].data.hour>60)
    // {
    //     data_alarm[0].data.hour = 01;
    //     data_alarm[0].data.minute = 01;   
    //     data_alarm[0].data.repeat = 0;
    //     data_alarm[0].data.state = 0; 
    //     data_alarm[0].data.wday_repeat = 0;  
    //     write_data_alarm();   
    // }
   

}