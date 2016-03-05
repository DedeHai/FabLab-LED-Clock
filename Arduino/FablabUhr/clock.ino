//draw hands of clock

#define HOURTAIL 3
#define MINUTETAIL 5
#define SECONDTAIL 10

void drawFace(RGB tickcolor)
{
  uint8_t i;
  for(i=0; i<12;i++)
  {
    
       pixelmatrix.setColor(60 - ((i*5 + 30) % 61),  0, tickcolor);
  
    }
  
  }

void drawHands(RGB hourcolor, RGB mincolor, RGB seccolor, uint8_t tail)
{


  uint8_t hourpixel = 60 - (((hour() % 12) * 5 + (int)minute() * 5 / 60 + 30) % 61);
  uint8_t minutepixel = 60 - ((minute() + 30) % 61);
  uint8_t secondpixel = 60 - ((second() + 30) % 61);

  addcolor(minutepixel,  0, mincolor);
  addcolor(secondpixel,  0, seccolor);
  addcolor(hourpixel,  0, hourcolor);

  if (tail)
  {
    RGB black;
    black.r = 0;
    black.g = 0;
    black.b = 0;

    uint8_t i;

    for (i = 1; i <= HOURTAIL; i++)
    {
      hourpixel++;
      hourpixel = hourpixel % 60;
      addcolor(hourpixel,  0,  fadecolorRGB(i, HOURTAIL, hourcolor,black));
     
    }
    
    for (i = 1; i <= MINUTETAIL; i++)
    {
      minutepixel++;
      minutepixel = minutepixel % 60;
      addcolor(minutepixel,  0,  fadecolorRGB(i, MINUTETAIL, mincolor,black));
    }
    
    
    for (i = 1; i <= SECONDTAIL; i++)
    {
      secondpixel++;
      secondpixel = secondpixel % 60;
      addcolor(secondpixel,  0,  fadecolorRGB(i, SECONDTAIL, seccolor,black));
    }
    }


}



void drawHands(uint8_t hourhue, uint8_t minhue, uint8_t sechue, uint8_t tail)
{


  uint8_t hourpixel = 60 - (((hour() % 12) * 5 + (int)minute() * 5 / 60 + 30) % 60);
  uint8_t minutepixel = 60 - ((minute() + 30) % 60);
  uint8_t secondpixel = 60 - ((second() + 30) % 60);

  addcolor(minutepixel,  0,  hsv_to_rgb (minhue, 255, 255));
  addcolor(secondpixel,  0, hsv_to_rgb (sechue, 255, 255));
  addcolor(hourpixel,  0, hsv_to_rgb (hourhue, 255, 255));

  if (tail)
  {
    RGB black;
    black.r = 0;
    black.g = 0;
    black.b = 0;

    uint8_t i;

    for (i = 1; i <= HOURTAIL; i++)
    {
      hourpixel++;
      hourpixel = hourpixel % 60;
      addcolor(hourpixel,  0,  hsv_to_rgb (hourhue, 255,((int)255*(HOURTAIL-i)/HOURTAIL)));
     
    }
    
    for (i = 1; i <= MINUTETAIL; i++)
    {
      minutepixel++;
      minutepixel = minutepixel % 60;
      addcolor(minutepixel,  0,  hsv_to_rgb (minhue, 255,((int)255*(MINUTETAIL-i)/MINUTETAIL)));
    }
    
    
    for (i = 1; i <= SECONDTAIL; i++)
    {
      secondpixel++;
      secondpixel = secondpixel % 60;
      addcolor(secondpixel,  0,    hsv_to_rgb (sechue, 255,((int)255*(SECONDTAIL-i)/SECONDTAIL)));
    }
    }


}
