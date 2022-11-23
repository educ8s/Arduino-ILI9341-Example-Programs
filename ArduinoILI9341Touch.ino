#include "Adafruit_GFX.h"     
#include "Adafruit_ILI9341.h" 
#include "URTouch.h"          

#define TFT_DC 9              
#define TFT_CS 10            
#define TFT_RST 8
#define TFT_MISO 12         
#define TFT_MOSI 11           
#define TFT_CLK 13            

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define t_SCK 3              
#define t_CS 4                
#define t_MOSI 5              
#define t_MISO 6             
#define t_IRQ 7              

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

void setup(){
  tft.begin();                     
  tft.setRotation(3);           
 
  ts.InitTouch();                   
  ts.setPrecision(PREC_EXTREME);
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextColor(ILI9341_RED);  
  tft.setTextSize(2);               
  tft.setCursor(85,5);              
  tft.print("Touch Demo"); 

  
  tft.setTextColor(ILI9341_GREEN);  
  tft.setCursor(20,220);           
  tft.print("http://www.educ8s.tv");
}
 
void loop()
{
  int x, y;                        
 
  while(ts.dataAvailable())        
  {
    ts.read();                      
    x = ts.getX();                 
    y = ts.getY();                  
    if((x!=-1) && (y!=-1))          
    {
      x += 13;                      
      y += 4;                       
      int radius = 4;               
      tft.fillCircle(x, y, radius, ILI9341_YELLOW);
    }
  }
}
