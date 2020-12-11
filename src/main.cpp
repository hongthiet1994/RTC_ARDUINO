#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#define LED_DEBUG    13

void setup() 
{
  pinMode(LED_DEBUG,OUTPUT); 
}

void loop() 
{
  digitalWrite(LED_DEBUG,HIGH);
  delay(1000);
  digitalWrite(LED_DEBUG,LOW);
  delay(1000); 
}