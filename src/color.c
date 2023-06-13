#include <stdbool.h>
#include "color.h"

bool isRedish(unsigned char red, unsigned char green, unsigned char blue)
{
  float avgRed = (float)red;
  float avgGreenBlue = (float)(green + blue);

  return ((avgRed / 255) - (avgGreenBlue / 255)) > 0.5;
}