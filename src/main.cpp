#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal_I2C.h>
#include "LowPower.h"
#include "module_keypad.h"
#include "module_realtime.h"


#define LED_DEBUG 13




LiquidCrystal_I2C lcd(0x27,16,2);









void print2digits(int number)
{
  if (number >= 0 && number < 10)
  {
    Serial.write('0');
  }
  Serial.print(number);
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_DEBUG, OUTPUT);
  lcd.init(); 
  lcd.backlight();
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------"); 
}
// void print_time()
// {
//   print2digits(time_data.Hour);
//   Serial.write(':');
//   print2digits(time_data.Minute);
//   Serial.write(':');
//   print2digits(time_data.Second);
//   Serial.write(' ');
//   print2digits(time_data.Wday);
//   Serial.print(", Date (D/M/Y) = ");
//   Serial.print(time_data.Day);
//   Serial.write('/');
//   Serial.print(time_data.Month);
//   Serial.write('/');
//   Serial.print(tmYearToCalendar(time_data.Year));
//   Serial.println(); 
// }


void loop()
{ 
  get_key();
  
  //delay(1000);
  //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  //LowPower.powerStandby(SLEEP_8S, ADC_OFF, BOD_OFF); 
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF,TIMER4_OFF,TIMER3_OFF,TIMER2_OFF,TIMER1_OFF, TIMER0_OFF, SPI_OFF,USART3_OFF,USART2_OFF,USART1_OFF, USART0_OFF, TWI_OFF);
}

