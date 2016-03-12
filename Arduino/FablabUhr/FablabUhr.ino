
/*
60 Pixel Kreis als uhr
Die getRTCtime Funktion funktioniert mit Zeitzonen und Sommer-Winterzeit umstellung, die RTC uhr muss auf UTC zeit eingestellt sein
 */

#include "RGBpixelmatrix.h"
#include <avr/delay.h>

#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include "RGBpixelmatrix.h" //My pixel Matrix library (use Arduino 1.0.5, timing seems to be off in later versions)
#include <util/delay.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)


#define WIDTH 72 
#define HEIGHT 1 //and two lines
#define NOOFPIXELS WIDTH*HEIGHT
#define F_CPU 16000000UL

RGBpixelmatrix pixelmatrix(WIDTH, HEIGHT); //create a RGBpixelmatrix
RGB colorbuffer1[WIDTH][HEIGHT]; //primärer buffer für fading
RGB colorbuffer2[WIDTH][HEIGHT]; //sekundärer buffer für fading


#define BAUDRATE 115200

byte mode = 1;


void setup()
{

  Serial.begin(BAUDRATE);
  pinMode(7, OUTPUT);
  randomSeed(analogRead(A0));
  mode = random(3);
  pinMode(4, INPUT);
  digitalWrite(4, HIGH); //pullup

  //setup RTC
  setSyncProvider(getRTCtime);   // the function to get the time from the RTC (includes day light saving time and timezone, see clock.ino)

  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");

  setSyncInterval(1);    //zeit alle 5 sekunden synchronisieren mit RTC modul

  pixelmatrix.clear();
  Serial.println("setup done");
}
float starthue = 0;
void loop()
{
  pixelmatrix.clear();
  starthue += 0.15;
  if(starthue > 255) starthue -= 255; //prevent overflow
  RGB result;
  float hue = starthue;
  uint8_t i = 0;
  /*
  for (i = 0; i < 60; i++)
   {
   hue += (255 / 60);
   result = hsv_to_rgb (byte(hue), 255, 10);
   pixelmatrix.setColor(i,  0, result);
   }*/
  RGB centercolor = hsv_to_rgb (hue, 240, 200);  
  for (i = 60; i < 72; i++)
  {
    pixelmatrix.setColor(i,  0, centercolor);
  }


  /*
  RGB hourcolor = hsv_to_rgb (0, 255, 255);
   RGB minutecolor = hsv_to_rgb (30, 255, 255);
   RGB secondcolor = hsv_to_rgb (512/3, 255, 255);
   drawHands(hourcolor, minutecolor, secondcolor, 1);
   */
  drawFace(hsv_to_rgb (hue, 200, 60));
  drawHands(2, 40, 110, 1);

  pixelmatrix.sendColors();
  delay(10);
}




