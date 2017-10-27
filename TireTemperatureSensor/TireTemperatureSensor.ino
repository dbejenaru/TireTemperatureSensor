//Tire Temperature Sensors made by Draagood
#include <Adafruit_MLX90614.h>
#include <Wire.h>
#include <U8glib.h>
#include "U8glib.h"
Adafruit_MLX90614 mlx1 = Adafruit_MLX90614(0x5A); 
Adafruit_MLX90614 mlx2 = Adafruit_MLX90614(0x5B);
int med = 0, front=0, back=0, count=0;
String s;
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK); 
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
//extern uint8_t I2C_SLA;
uint8_t I2C_SLA = 0x3C;
void setup(void)
{
  u8g.setColorIndex(1);
  I2C_SLA = 0x3C;
  u8g.firstPage();
  Serial.begin(9600);
  mlx1.begin();
  mlx2.begin();
}
void draw(void) 
              {
          u8g.setFont(u8g_font_unifont);
          u8g.drawStr( 30, 10, "DRAAGOOD");
          u8g.drawStr( 15, 60, "Back");
          u8g.setPrintPos(85, 60);
          u8g.print(back);
          u8g.drawStr( 15, 43, "Front");
          u8g.setPrintPos(85, 43);
          u8g.print(front);
          u8g.setPrintPos(count, 27);
          u8g.print(s);
              }
void loop(void)
{ 
 I2C_SLA = 0x3C;
  u8g.firstPage();  
        do 
        {
            draw();
            count++;
        }
  while( u8g.nextPage());
    front = (mlx1.readObjectTempC());
   back = (mlx2.readObjectTempC());
   med = (front+back)/2;
        if (med<35)
      {
        s = "D A N G E R";
        count = 15;
      }
         else
         {
          s = "RACE";
          count = 46;
         } 
   //Serial.print("Back = "); Serial.print(back); Serial.println("*C");
   //delay(500);
   //Serial.print("*Front = "); Serial.print(front); Serial.println("*C");
   //delay(1000);
}

