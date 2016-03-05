/*
mögliche uhren:
-stunde:2 oder drei breit, minute und sekunde 1 breit. Hintergrundfarbe könnte ändern, einmal im farbkreis pro stunde, zeiger genau invertieren, bei überlappung schwarz oder sättigung verringern oder hue addieren
-mit einer zufallsfarbe füllen oder mit farbschemas füllen zwischen den Zeigern. bei überlappung farben addieren

animationen:
farben abwechseln, sektoren teilen und überschreiben oder sektoren rotieren
überblenden auch möglich, müsste man farbbuffer wieder einführen
Animationen kann man mit uhr überlagern, dann zeiger einfach schwarz oder weiss färben


*/

void rotatesectors(uint8_t color1width, uint8_t segments, RGB color1, RGB color2)
{
  static uint8_t rotation = 0;
  uint8_t i;

  //check if segmentation is possible, set to default if not
  if ((color1width + 1)* segments > 60)
  {
    segments = 6;
    color1width = 5;
  }

  uint8_t color2width = (60 / segments) - color1width;
  uint8_t maxrotation = color1width + color2width;

  for (i = 0; i < 60; i++)
  {

    pixelmatrix.setColor(i + rotation,  0, color1);



  }


}



void addcolor(uint8_t x, uint8_t y, RGB color)
{
  RGB result = pixelmatrix.getColor(x, y);
  uint16_t redsum = (uint16_t)result.r + (uint16_t)color.r;
  uint16_t greensum = (uint16_t)result.g + (uint16_t)color.g;
  uint16_t bluesum = (uint16_t)result.b + (uint16_t)color.b;

  if (redsum > 255) redsum = 255;
  if (greensum > 255) greensum = 255;
  if (bluesum > 255) bluesum = 255;

  result.r = redsum;
  result.g = greensum;
  result.b = bluesum;

  pixelmatrix.setColor(x,  y, result);

}



RGB fadecolorRGB(uint8_t fadestep, uint8_t totalfadesteps, RGB startcolor,
                 RGB endcolor) {
  RGB returncolor;
  float factor = (float) (fadestep) / (float) totalfadesteps;
  returncolor.r = (uint8_t)(
                    startcolor.r
                    - (factor)
                    * ((int16_t) startcolor.r - (int16_t) endcolor.r));
  returncolor.g = (uint8_t)(
                    startcolor.g
                    - (factor)
                    * ((int16_t) startcolor.g - (int16_t) endcolor.g));
  returncolor.b = (uint8_t)(
                    startcolor.b
                    - (factor)
                    * ((int16_t) startcolor.b - (int16_t) endcolor.b));
  return returncolor;
}

