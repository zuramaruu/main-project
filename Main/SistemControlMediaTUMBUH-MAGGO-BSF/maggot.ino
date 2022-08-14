#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define DEBUG 1

int pinRelayPompaExt[6] = {47, 49, 22, 45, 43, 41};
int pinRelay[9] = {37, 31, 23, 33, 25, 27, 29, 35, 39};
int pinDht[3] = {3, 4, 2};
int pinMoisture[3] = {A0, A1, A2};

uint8_t relay_lampu[3] = {0, 0, 0};
uint8_t relay_pompa[3] = {0, 0, 0};
uint8_t relay_kipas[3] = {0, 0, 0};
uint8_t relay_pompaExt[6] = {0, 0, 0, 0, 0, 0};

float suhu_value[3] = {0, 0, 0};
int moisture_value[3] = {0, 0, 0};
float ph_value[3] = {0, 0, 0};

int u_time[3] = {0, 0, 0};
int flag_lcd = 0;

String read1, read2, read3, read4;

float callback_ph_satu = 0.0;
float callback_ph_dua = 0.0;
float callback_ph_tiga = 0.0;

void setup() {
  Serial.begin(9600);
  Lora_Init();
  PompaExt_Init();
  Relay_Init();
  Dht_Init();
  ph_Init();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("RIKI - MAGGOT");
  delay(1000);
  lcd.clear();
  Serial.println("INIT");
}

void loop() {
  bacaTemperature();
  bacaMoisture();
  bacaPh();
  ControlAtas();
  ControlTengah();
  ControlBawah();
  LCD_Control();

  Lora_KirimData(String(suhu_value[0]) + "#" + String(suhu_value[1]) + "#" + String(suhu_value[2]) + "#"
                 + String(moisture_value[0]) + "#" + String(moisture_value[1]) + "#" + String(moisture_value[2]) + "#"
                 + String(ph_value[0]) + "#" + String(ph_value[1]) + "#" + String(ph_value[2]) + "#"
                 + String(relay_kipas[0]) + "#" + String(relay_lampu[0]) + "#" + String(relay_pompa[0]) + "#"
                 + String(relay_kipas[1]) + "#" + String(relay_lampu[1]) + "#" + String(relay_pompa[1]) + "#"
                 + String(relay_kipas[2]) + "#" + String(relay_lampu[2]) + "#" + String(relay_pompa[2]) + "#"
                 + String(relay_pompaExt[0]) + "#" + String(relay_pompaExt[1]) + "#" + String(relay_pompaExt[2]) + "#"
                 + String(relay_pompaExt[3]) + "#" + String(relay_pompaExt[4]) + "#" + String(relay_pompaExt[5]) + "#");
  delay(50);
}
