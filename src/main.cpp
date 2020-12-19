#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal_I2C.h>
#include "LowPower.h"
#include <Keypad.h>



#define LED_DEBUG 13


const byte rows = 4; //số hàng
const byte columns = 4; //số cột
 
int holdDelay = 700; //Thời gian trễ để xem là nhấn 1 nút nhằm tránh nhiễu
int n = 3; // 
int state = 0; //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
char key = 0;
 
//Định nghĩa các giá trị trả về
char keys[rows][columns] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
 

byte columnPins[columns] = {5, 6, 7, 8}; 
byte rowPins[rows] = {9, 10, 11, 12};//Cách nối chân với Arduino 
//cài đặt thư viện keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);


LiquidCrystal_I2C lcd(0x27,16,2);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
tmElements_t time_data;


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
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------"); 
}
void print_time()
{
  print2digits(time_data.Hour);
  Serial.write(':');
  print2digits(time_data.Minute);
  Serial.write(':');
  print2digits(time_data.Second);
  Serial.write(' ');
  print2digits(time_data.Wday);
  Serial.print(", Date (D/M/Y) = ");
  Serial.print(time_data.Day);
  Serial.write('/');
  Serial.print(time_data.Month);
  Serial.write('/');
  Serial.print(tmYearToCalendar(time_data.Year));
  Serial.println(); 
}
void loop()
{ 

  char temp = keypad.getKey();                                                      
 
  if ((int)keypad.getState() ==  PRESSED) {
    if (temp != 0) {
      key = temp;
    }
  }
  if ((int)keypad.getState() ==  HOLD) {
    state++;
    state = constrain(state, 1, n-1);
    delay(holdDelay);
  }
 
  if ((int)keypad.getState() ==  RELEASED) {
    key += state;
    state = 0;
    //Xuất lên Máy tính để xem kết quả
    Serial.println(key);
 
  }
  delay(100);  
  // if (RTC.read(time_data))
  // {
  //   print_time();  
  //   display_time_lcd(time_data);
  // }
  // else
  // {
  //   if (RTC.chipPresent())
  //   {
  //     Serial.println("The DS1307 is stopped.  Please run the SetTime");
  //     Serial.println("example to initialize the time and begin running.");
  //   }
  //   else
  //   {
  //     Serial.println("DS1307 read error!  Please check the circuitry.");
  //     Serial.println();
  //   }
  //   delay(1000);
  // }
  //delay(1000);
  //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  //LowPower.powerStandby(SLEEP_8S, ADC_OFF, BOD_OFF); 
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF,TIMER4_OFF,TIMER3_OFF,TIMER2_OFF,TIMER1_OFF, TIMER0_OFF, SPI_OFF,USART3_OFF,USART2_OFF,USART1_OFF, USART0_OFF, TWI_OFF);
}

