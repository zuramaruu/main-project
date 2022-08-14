#include <tcs3200.h>

int red, green, blue, white;

tcs3200 tcs(27, 26, 25, 33, 32); // (S0, S1, S2, S3, output pin)  //

void setup() {
  Serial.begin(115200);
}

void loop() {
  //red = tcs.colorRead('r', 0);    //scaling can also be put to 0%, 20%, and 100% (default scaling is 20%)   ---    read more at: https://www.mouser.com/catalog/specsheets/TCS3200-E11.pdf
  //red = tcs.colorRead('r', 20);
  //red = tcs.colorRead('r', 100);

  red = tcs.colorRead('r');   //reads color value for red
  Serial.print("R= ");
  Serial.print(red);
  Serial.print("    ");

  green = tcs.colorRead('g');   //reads color value for green
  Serial.print("G= ");
  Serial.print(green);
  Serial.print("    ");

  blue = tcs.colorRead('b');    //reads color value for blue
  Serial.print("B= ");
  Serial.print(blue);
  Serial.print("    ");

  white = tcs.colorRead('c');    //reads color value for white(clear)
  Serial.print("W(clear)= ");
  Serial.print(white);
  Serial.print("    ");

  Serial.println();

  delay(200);

}
