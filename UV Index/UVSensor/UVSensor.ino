#include "U8glib.h"

#define  SENSOR A0

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
 

int uv_sensor = 0;
int pos = 0;
String UV_index = "0";
String str; 
int voltage = 0;

void draw()
{
 
  u8g.drawRFrame(0, 16, 67, 48, 4);
  u8g.drawRFrame(67, 16, 61, 48, 4);
  u8g.drawRFrame(0, 0, 128, 16, 4);
  u8g.drawBox(11, 48, 45, 12 );
  u8g.setFont(u8g_font_8x13B);
  u8g.setColorIndex(0);
  u8g.drawStr( 13, 59, "mV");
  u8g.setColorIndex(1);
  u8g.drawStr( 24, 13, "UV INDEX");

  u8g.setFont(u8g_font_fur25);
  u8g.setPrintPos(10, 45);
  u8g.print( str);
  
  if (UV_index.length() <= 1)
  {
    pos = 88;
  }
  else
  {
    pos = 78;
  }
  u8g.setPrintPos(pos, 52);
  u8g.print(UV_index);
}
 
void setup(void)
{
  Serial.begin(9600);
  pinMode(SENSOR, INPUT);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }
}
 
void loop(void)
{
  index_UV();

  
  u8g.firstPage();
  do
  {
    draw();
  }
  while ( u8g.nextPage() );
  delay(150);
}
 
void index_UV()
{
  uv_sensor = analogRead(SENSOR);
  
  voltage = (uv_sensor * (5.0 / 1023.0)) * 1000;
  str = (String)voltage;
  
  if (voltage > 0 && voltage < 50) UV_index = "0";
  
  else if (voltage > 50 && voltage <= 227) UV_index = "0";
  
  else if (voltage > 227 && voltage <= 318) UV_index = "1";
  
  else if (voltage > 318 && voltage <= 408) UV_index = "2";
  
  else if (voltage > 408 && voltage <= 503) UV_index = "3";

  else if (voltage > 503 && voltage <= 606) UV_index = "4";

  else if (voltage > 606 && voltage <= 696) UV_index = "5";

  else if (voltage > 696 && voltage <= 795) UV_index = "6";
  
  else if (voltage > 795 && voltage <= 881) UV_index = "7";
 
  else if (voltage > 881 && voltage <= 976) UV_index = "8";
  
  else if (voltage > 976 && voltage <= 1079) UV_index = "9";
 
  else if (voltage > 1079 && voltage <= 1170) UV_index = "10";
  
  else if (voltage > 1170) UV_index = "11";
 
}
