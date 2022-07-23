#include "max6675.h"
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

int u_time[3] = {0, 0, 0};
uint8_t flag_btn = 0;
uint8_t flag_state = 0;
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
}
void loop() {
  if (digitalRead(push_button) == HIGH and flag_btn == 0) flag_btn = 1;
  if (digitalRead(reset_) == HIGH) flag_btn = 0;

  if (millis() - u_time[0] >= 500) {
    u_time[0] = millis();
    t_celcius, t_fahrenheit = readThermo(Module);
    String t_celcius_ = String(t_celcius);
    lcd.setCursor(2, 1);
    lcd.print("Suhu : " + t_celcius_);
    //    Serial.print("Suhu : ");
    //    Serial.print(t_celcius);
    //    Serial.print(" C");
    //    Serial.println();
  }

  if (flag_btn) {
    is_running();
  } else {
    flag_s = 4; u_time[1] = millis();
  }

  if (flag_s == 1) state_satu();
  if (flag_s == 2) state_dua();
  if (flag_s == 3) {//-- Reseting
    digitalWrite(push_button, LOW);
    stop_state();
    flag_btn = 0;
  }
  if (flag_s == 4) stop_state();

  lcd.setCursor(3, 0);
  String t_minute = String(millis() / 60000);
  String t_second_ = String(millis() / 1000);
  lcd.print("Time " + t_minute + " : " + t_second_);

  delay(30);
}
double readThermo(MAX6675 _module) {
  return _module.readCelsius(), _module.readFahrenheit();
}
void is_running() {
  if (millis() - u_time[1] >= 1000) flag_s = 1;
  if (millis() - u_time[1] >= 6000) flag_s = 2;
  if (millis() - u_time[1] >= 11000) {
    flag_s = 3; u_time[1] = millis();
  }
}

void state_satu() {
  digitalWrite(heater, HIGH);
  digitalWrite(motor_satu, HIGH);
  digitalWrite(motor_dua, LOW);
  //  Serial.println("State Satu");

}
void state_dua() {
  digitalWrite(heater, LOW);
  digitalWrite(motor_satu, LOW);
  digitalWrite(motor_dua, HIGH);
  //  Serial.println("State Dua");
}
void stop_state() {
  digitalWrite(heater, LOW);
  digitalWrite(motor_satu, LOW);
  digitalWrite(motor_dua, LOW);
  //  Serial.println("State Stop");
}
