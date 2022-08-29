#include <tcs3200.h>
#define COLORS (7)
#define S0 (4)
#define S1 (5)
#define S2 (6)
#define S3 (7)
#define OUT (8)

tcs3200 tcs(S0, S1, S2, S3, OUT); // (S0, S1, S2, S3, OUT pin)

int rgbVal[COLORS][3] =
{
  {250, 250, 250},
  {0, 0, 0},
  {142, 34, 41},
  {166, 125, 71},
  {35, 55, 38},
  {150, 50, 43},
  {22, 25, 45}
};

String colour[COLORS] = {"white",
                         "black",
                         "red",
                         "yellow",
                         "green",
                         "orange",
                         "blue"
                        };

uint16_t red, green, blue;

String getClosestColor() {
  return String(tcs.closestColor(rgbVal, colour, COLORS));
}

void readTCS3200() {

  red = tcs.colorRead('r');
  Serial.print("R= ");
  Serial.print(red);
  Serial.print("    ");

  green = tcs.colorRead('g');
  Serial.print("G= ");
  Serial.print(green);
  Serial.print("    ");

  blue = tcs.colorRead('b');
  Serial.print("B= ");
  Serial.print(blue);
  Serial.print("    ");

  Serial.println();
  delay(200);
}
