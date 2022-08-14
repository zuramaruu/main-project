//This code is created by SARATH KUMAR//
#include <LiquidCrystal_I2C.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 20, 4);

int SensorPin = A5;

void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("----INFOTAINMENT----");
  lcd.setCursor(0, 1);
  lcd.print("SOIL MOISTURE LEVEL.");
  lcd.setCursor(2, 2);
  lcd.print("Analog Value: ");
  lcd.setCursor(2, 3);
  lcd.print("Output: ");

}

void loop() {

  int SensorValue = analogRead(SensorPin);
  float SensorVolts = analogRead(SensorPin) * 0.0048828125;

  //  lcd.setCursor(16, 2);
  //  lcd.print(SensorValue);
  Serial.print(SensorValue);
  //  lcd.setCursor(9, 3);
  //  lcd.print(SensorVolts);
  //  lcd.print("V");
  Serial.print(SensorVolts);
  Serial.print("V");
  delay(100);

  //  sensorValue = analogRead(sensorPin);
  //  lcd.setCursor(4,2);
  //  lcd.print(sensorValue);
  //  delay(1000);

}
