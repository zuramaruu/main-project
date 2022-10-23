/* RTC */
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 RTC;
char daysOfTheWeek[7][12] = {"Sunday",
                             "Monday",
                             "Tuesday",
                             "Wednesday",
                             "Thursday",
                             "Friday",
                             "Saturday"
                            };
/* KEYPAD */
#include <Keypad_I2C.h>
#include <Keypad.h>        // GDY120705
#define I2CADDR 0x21
#define ROWS 4 //four rows
#define COLS 4 //four columns

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'E', '0', 'F', 'D'}
};
byte rowPins[ROWS] = {3, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad
Keypad_I2C customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR);

/* BME */
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
Adafruit_BME280 BME;

uint32_t bmeTmr;

void START_I2C_BUS() {
  Wire.begin();
  customKeypad.begin();
  lcd.init();
  lcd.backlight();
  if (!BME.begin(0x76)) {
    Serial.println("BME TIDAK TERDETEKSI");
    while (1);
  }

  // RTC Rusak
  if (!RTC.begin()) {
    Serial.println("RTC TIDAK TERDETEKSI");
    while (1);
  } else {
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //    RTC.adjust(DateTime(2022, 8, 07, 13, 34, 0));
  }
}

void bacaRTC() {
  DateTime now = RTC.now();
  YYMMDD[0] = now.year();
  YYMMDD[1] = now.month();
  YYMMDD[2] = now.day();

  HHMMMSS[0] = now.hour();
  HHMMMSS[1] = now.minute();
  HHMMMSS[2] = now.second();
#ifdef _DEBUG_RTC
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");

  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
#endif
}

void bacaBME() {
  if (millis() - bmeTmr >= 3000) {
    bme_val[0] = BME.readTemperature();
    bme_val[1] = BME.readHumidity();
#ifdef _DEBUG_BME
    Serial.print("SUHU: ");
    Serial.print(BME.readTemperature());
    Serial.println(" C");
    Serial.print("KELEMBAPAN: ");
    Serial.print(BME.readHumidity());
    Serial.println(" %");
#endif

    bmeTmr = millis();
  }
}

void bacaKeypad() {
  customKey = customKeypad.getKey();
  if (customKey != NO_KEY) {
    Serial.print("Key = ");
    Serial.println(customKey);
  }
}

uint8_t readSuhu() {
  uint8_t buff;
  if (bme_val[0] > 28) buff = 1;
  else buff = 0;
  return buff;
}
