    /////////////////////////////////////////////////////////////////
   //                 Arduino ILI9341 RTC                v1.01    //
  //       Get the latest version of the code here:              //
 /        http://educ8s.tv/arduino-2-8-ili9341-tutorial         //
/////////////////////////////////////////////////////////////////


#include "Adafruit_GFX.h"     
#include "Adafruit_ILI9341.h" 
#include <Wire.h>
#include "Sodaq_DS3231.h"
#include  <SPI.h>

#define TFT_DC 9              
#define TFT_CS 10             
#define TFT_RST 8             
#define TFT_MISO 12           
#define TFT_MOSI 11           
#define TFT_CLK 13          

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

float maxTemperature=0;
float minTemperature=200;
char charMinTemperature[10];
char charMaxTemperature[10];
char timeChar[100];
char dateChar[50];
char temperatureChar[10];

float temperature = 0;
float previousTemperature = 0;

uint32_t old_ts;

String dateString;
int minuteNow=0;
int minutePrevious=0;
  
void setup(){
  
  Serial.begin(9600);
  tft.begin();                      
  tft.setRotation(0);            
  tft.fillScreen(ILI9341_BLACK);

  Wire.begin();
  rtc.begin();

  printText("TEMPERATURE", ILI9341_GREEN,20,130,3);
  printText("MAX", ILI9341_RED,37,260,2);
  printText("MIN", ILI9341_BLUE,173,260,2);
 
  //setRTCTime();
}
 
void loop()
{
  float temperature = rtc.getTemperature();
  DateTime now = rtc.now(); //get the current date-time
  uint32_t ts = now.getEpoch();

    if (old_ts == 0 || old_ts != ts) {
  old_ts = ts;
  
  minuteNow = now.minute();
  if(minuteNow!=minutePrevious)
  {
    dateString = getDayOfWeek(now.dayOfWeek())+", ";
    dateString = dateString+String(now.date())+"/"+String(now.month());
    dateString= dateString+"/"+ String(now.year()); 
    minutePrevious = minuteNow;
    String hours = String(now.hour());
    if(now.minute()<10)
    {
      hours = hours+":0"+String(now.minute());
    }else
    {
      hours = hours+":"+String(now.minute());
    }
    
    hours.toCharArray(timeChar,100);
    tft.fillRect(50,50,135,40,ILI9341_BLACK);
    printText(timeChar, ILI9341_WHITE,55,55,4);
    dateString.toCharArray(dateChar,50);
    printText(dateChar, ILI9341_GREEN,8,5,2);
  }
  
  if(temperature != previousTemperature)
  {
    previousTemperature = temperature;
    String temperatureString = String(temperature,1);
    temperatureString.toCharArray(temperatureChar,10);
    tft.fillRect(50,175,150,40,ILI9341_BLACK);
    printText(temperatureChar, ILI9341_WHITE,50,180,4);
    printText("o", ILI9341_WHITE,158,175,3);
    printText("C", ILI9341_WHITE,180,180,4);

if(temperature>maxTemperature)
    {
      maxTemperature = temperature;
      dtostrf(maxTemperature,5, 1, charMaxTemperature); 
      tft.fillRect(8,280,90,28,ILI9341_BLACK);
      printText(charMaxTemperature, ILI9341_WHITE,8,290,2);
      printText("o", ILI9341_WHITE,70,280,2);
      printText("C", ILI9341_WHITE,85,290,2);
    }
if(temperature  < minTemperature) 

 {
      minTemperature = temperature;
      dtostrf(minTemperature,5, 1, charMinTemperature); 
      tft.fillRect(145,280,90,28,ILI9341_BLACK);
      printText(charMinTemperature, ILI9341_WHITE,145,290,2);
      printText("o", ILI9341_WHITE,207,280,2);
      printText("C", ILI9341_WHITE,222,290,2);
    }
  }
}
    delay(1000);
}

void setRTCTime()
{
  DateTime dt(2018, 4, 2, 13, 13, 30, 1); // Year, Month, Day, Hour, Minutes, Seconds, Day of Week
  rtc.setDateTime(dt); //Adjust date-time as defined 'dt' above 
}

void printText(char *text, uint16_t color, int x, int y,int textSize)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setTextWrap(true);
  tft.print(text);
}

String getDayOfWeek(int i)
{
  switch(i)
  {
    case 1: return "Monday";break;
    case 2: return "Tuesday";break;
    case 3: return "Wednesday";break;
    case 4: return "Thursday";break;
    case 5: return "Friday";break;
    case 6: return "Saturday";break;
    case 7: return "Sunday";break;
    default: return "Monday";break;
  }
}
