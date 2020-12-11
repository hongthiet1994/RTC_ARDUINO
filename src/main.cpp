#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal_I2C.h>

#define LED_DEBUG 13
LiquidCrystal_I2C lcd(0x27,16,2);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
tmElements_t tm;


void display_time_lcd(tmElements_t tm)
{

  lcd.setCursor(4, 1);
    if(tm.Hour<=9)
    {
      lcd.print("0");
      lcd.print(tm.Hour);
    }
    else 
    {
     lcd.print(tm.Hour); 
    }
    lcd.print(':');
    if(tm.Minute<=9)
    {
      lcd.print("0");
      lcd.print(tm.Minute);
    }
    else {
     lcd.print(tm.Minute); 
    }
    lcd.print(':');
    if(tm.Second<=9)
    {
      lcd.print("0");
      lcd.print(tm.Second);
    }
    else {
     lcd.print(tm.Second); 
    }
    lcd.print("   ");

    lcd.setCursor(1, 0);
    lcd.print(daysOfTheWeek[tm.Wday]);
    lcd.print(",");
    if(tm.Day<=9)
    {
      lcd.print("0");
      lcd.print(tm.Day);
    }
    else {
     lcd.print(tm.Day); 
    }
    lcd.print('/');
    if(tm.Month<=9)
    {
      lcd.print("0");
      lcd.print(tm.Month);
    }
    else {
     lcd.print(tm.Month); 
    }
    lcd.print('/');
    lcd.print(tmYearToCalendar(tm.Year));
}


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
  while (!Serial)
    ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");
}

void loop()
{ 
  
  
  if (RTC.read(tm))
  {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.write(' ');
    print2digits(tm.Wday);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
    
    display_time_lcd(tm);

  }
  else
  {
    if (RTC.chipPresent())
    {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
      tm.Day=11;
      tm.Month = 12;
      tm.Year = 50;
      tm.Wday = 5;
      RTC.write(tm);
    }
    else
    {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

