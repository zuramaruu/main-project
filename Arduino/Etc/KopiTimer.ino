/*
   Library link : - https://github.com/brunocalou/Timer
                  - https://www.arduino.cc/reference/en/libraries/max6675-library/
*/

#include "max6675.h"
#include "timer.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

//-- Mengatur Pin
#define reset_        3
#define mSO           4
#define mCS           5
#define mSCK          6
#define push_button   7
#define motor_dua     8
#define motor_satu    9
#define heater        10
#define TIME_MILLIS   5000 // 60000 = 1 menit 

Timer timer;
int u_time[4] = {0, 0, 0, 0};
int t_second = 0, t_minute = 0;
uint8_t flag_btn = 0;
uint8_t flag_s = 0;

MAX6675 Module(mSCK, mCS, mSO);
double t_celcius, t_fahrenheit;

void setup() {
  Serial.begin(9600);
  pinMode(push_button, INPUT);
  pinMode(reset_, INPUT);
  pinMode(heater, OUTPUT);
  pinMode(motor_satu, OUTPUT);
  pinMode(motor_dua, OUTPUT);
  Serial.println("Initialize");

  lcd.init();                      // inisialisasi the lcd
  lcd.backlight();
  lcd.setCursor(0, 1);

  timer.setInterval(1000);
  timer.setCallback(timerCallback);
  timer.start();
}

void loop() {
  timer.update();
  if (digitalRead(push_button) == HIGH and flag_btn == 0) flag_btn = 1;
  if (digitalRead(reset_) == HIGH) flag_btn = 0;

  if (millis() - u_time[0] >= 1000) {
    u_time[0] = millis();
    t_celcius, t_fahrenheit = readThermo(Module);
    if (flag_btn) {
      lcd.setCursor(2, 1);
      lcd.print("Suhu : " + String(t_celcius));
    }
  }

  if (flag_btn) is_running();
  else reset_s();

  if (flag_s == 0) stop_state();
  if (flag_s == 1) state_satu();
  if (flag_s == 2) state_dua();
  if (flag_s == 3) reset_s();

  if (flag_btn) {
    lcd.setCursor(3, 0);
    lcd.print("Time " + String(t_minute) + " : " + String(t_second));
  }

  delay(10);
}

double readThermo(MAX6675 _module) {
  return _module.readCelsius(), _module.readFahrenheit();
}

void is_running() {
  if (millis() - u_time[1] >= 1000) flag_s = 1;
  if (millis() - u_time[1] >= TIME_MILLIS) flag_s = 2;
  if (millis() - u_time[1] >= (TIME_MILLIS + TIME_MILLIS)) {
    flag_s = 3;
    u_time[1] = millis();
  }
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

void stop_state() {
  digitalWrite(heater, LOW);
  digitalWrite(motor_satu, LOW);
  digitalWrite(motor_dua, LOW);
}

void reset_s() {
  t_second = 0;
  t_minute = 0;
  u_time[1] = millis();
  stop_state();
  flag_s = 0;
  flag_btn = 0;
  lcd.clear();
}

void timerCallback() {
  t_second += 1;
  if (t_second == 60) {
    lcd.clear();
    t_minute += 1;
    t_second = 0;
  }
}
