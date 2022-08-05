#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void LCD_Init()
{
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print(" VINCENT ALVIN");
  lcd.setCursor(1, 1);
  delay(2000);
  lcd.clear();
}
void LCD_Print()
{
  lcd.setCursor(1, 0);
  lcd.print("SUHU = " + String(suhu) + " 'C ");
  lcd.setCursor(3, 1);
  lcd.print("WAKTU " + String(t_minute) + " : " + String(t_second) + "   ");
}
