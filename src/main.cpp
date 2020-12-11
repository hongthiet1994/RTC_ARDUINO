#include <Arduino.h>
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