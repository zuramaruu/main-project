#include <tcs3200.h>    // Include TCS3200 library 
#define s_0 27
#define s_1 26
#define s_2 25
#define s_3 33
#define out_pin 32

//#define num_of_colors 7   // Declares the number of colors the program can recognise (number of calibrated colors)
//// distinctRGB[] array declares calibration values for each declared color in distinctColors[] array
//int distinctRGB[num_of_colors][3] = {{250, 250, 250}, {0, 0, 0}, {142, 34, 41}, {166, 125, 71}, {35, 55, 38}, {150, 50, 43}, {22, 25, 45}};
//// distinctColors[] array declares values to be returned from closestColor() function if specified color is recognised
//String distinctColors[num_of_colors] = {"putih", "hitam", "merah", "kuning", "hijau", "orange", "blue"};

#define num_of_colors 3
int distinctRGB[num_of_colors][3] = {{18, 10, 11}, {25, 11, 12}, {10, 7, 9}};
String distinctColors[num_of_colors] = {"light", "brown", "dark"};

int red, green, blue;


tcs3200 tcs(s_0, s_1, s_2, s_3, out_pin); // (S0, S1, S2, S3, output pin) //  ---  see:  https://www.mouser.com/catalog/specsheets/TCS3200-E11.pdf

void Tcs3200_Init() {
  //  pinMode(s_0, OUTPUT);
  //  pinMode(s_1, OUTPUT);
  //  pinMode(s_2, OUTPUT);
  //  pinMode(s_3, OUTPUT);
  //  pinMode(out_pin, INPUT);
  //
  //  digitalWrite(s_0, HIGH);
  //  digitalWrite(s_1, LOW);
}
String tcs3200getColor() {
  return tcs.closestColor(distinctRGB, distinctColors, num_of_colors);
}

int tcs3200getRValue() {
  return tcs.colorRead('r');
}
int tcs3200getGValue() {
  return tcs.colorRead('g');
}
int tcs3200getBValue() {
  return tcs.colorRead('b');
}

void Tcs3200_Main() {

  Serial.println(tcs.closestColor(distinctRGB, distinctColors, num_of_colors) );

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

  Serial.println();

  delay(200);

}
