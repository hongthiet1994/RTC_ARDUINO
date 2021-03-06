#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
//#include <LiquidCrystal_I2C.h>
#include "LowPower.h"
#include "module_keypad.h"
#include "module_realtime.h"
#include "module_display.h"
#include "module_timer.h"
#include "module_alarm.h"
#include "module_eeprom.h"
#define LED_DEBUG 13




void setup()
{
  Serial.begin(115200);
  pinMode(LED_DEBUG, OUTPUT);
  init_lcd();
  init_timer();
  Serial.println("Init project realtime clock");
  Serial.println("---------------------------"); 
  //set_time();
  read_data_alarm();
}



void loop()
{ 
  get_key();   
  tick_timer();
  //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  //LowPower.powerStandby(SLEEP_8S, ADC_OFF, BOD_OFF); 
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF,TIMER4_OFF,TIMER3_OFF,TIMER2_OFF,TIMER1_OFF, TIMER0_OFF, SPI_OFF,USART3_OFF,USART2_OFF,USART1_OFF, USART0_OFF, TWI_OFF);
}

