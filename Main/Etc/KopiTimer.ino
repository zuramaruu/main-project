#include "max6675.h"
#include "timer.h"

//#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

//-- Mengatur Pin
#define mSO           4
#define mCS           5
#define mSCK          6
#define push_button   7
#define motor_dua     8
#define motor_satu    9
#define heater        10
#define TIME_MINUTE   10 //-- Satuan Menit

Timer timer;

int u_time = 0;
uint16_t t_second = 0;
uint16_t t_minute = 0;
uint8_t flag_btn = 0;

MAX6675 Module(mSCK, mCS, mSO);
float t_celcius, t_fahrenheit;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 1);

  pinMode(push_button, INPUT);
  pinMode(heater, OUTPUT);
  pinMode(motor_satu, OUTPUT);
  pinMode(motor_dua, OUTPUT);

  Serial.println("Initialize");
  timer.setInterval(1000);
  timer.setCallback(timerCallback);
  timer.start();
}

void loop() {
  timer.update();

  if (millis() - u_time >= 1000) {
    u_time = millis();
    t_celcius = Module.readCelsius();
    lcd.setCursor(2, 1);
    lcd.print("Suhu " + String(t_celcius) + " C");
    Serial.println("Suhu " + String(t_celcius) + " C");
  }

  if (digitalRead(push_button) == HIGH) {
    lcd.clear();
    if (flag_btn == 0) {
      flag_btn = 1;
      delay(1000);
    } else {
      flag_btn = 0;
      delay(1000);
    }
  }

  if (flag_btn) {
    if (t_minute == 0) state_satu();
    else if (t_minute == TIME_MINUTE) state_dua();
    else if (t_minute == TIME_MINUTE * 2) {
      state_stop();
      flag_btn = 0;
    }
  }
  else state_stop();
  printLcd();

  delay(300);

}
void printLcd() {
  lcd.setCursor(0, 0);
  lcd.print("Time " + String(t_minute) + " : " + String(t_second));
  lcd.setCursor(13, 0);
  if (flag_btn) lcd.print("ON ");
  else lcd.print("OFF");
}

void state_satu() {
  digitalWrite(heater, HIGH);
  digitalWrite(motor_satu, HIGH);
  digitalWrite(motor_dua, LOW);
}

void state_dua() {
  digitalWrite(heater, LOW);
  digitalWrite(motor_satu, LOW);
  digitalWrite(motor_dua, HIGH);
}

void state_stop() {
  digitalWrite(heater, LOW);
  digitalWrite(motor_satu, LOW);
  digitalWrite(motor_dua, LOW);
  t_second = 0;
  t_minute = 0;
}

void timerCallback() {
  t_second += 1;
  if (t_second == 60) {
    lcd.clear();
    t_minute += 1;
    t_second = 0;
  }
}
