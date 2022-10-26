#include "WiFi.h"
#include "HTTPClient.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define   SSID_WIFI     "Polinema Hotspot LT8 Barat"
#define   PASS_WIFI     ""
#define   DOMAIN        "http://192.168.245.207:5000"
#define   ON            "ON"
#define   OFF           "OFF"

/* Inisialisasi Pin */
#define   ON1           13
#define   OFF1          12
#define   ON2           14
#define   OFF2          27

const uint8_t btnPin[4] = {ON1, OFF1, ON2, OFF2};

uint8_t wifiStatus = 0;
uint32_t sysTmr[3];
uint8_t state[4] = {0, 0, 0, 0};

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(btnPin[i], INPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  InitWifi();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) return; // Address 0x3D for 128x64
  
}

void loop() {

  if (millis() - sysTmr[2] >= 300) {

    for (uint8_t i = 0; i < 4; i++) {
      state[i] = digitalRead(btnPin[i]);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(0, 10);
    display.println("State 1 = ");

    display.setCursor(11, 10);
    if (getState(0)) display.println("ON");
    else display.println("OFF");

    display.setCursor(0, 20);
    display.println("State 2 = ");

    display.setCursor(11, 20);
    if (getState(1)) display.println("ON");
    else display.println("OFF");

    display.display();

    sysTmr[2] = millis();
  }

  if (millis() - sysTmr[0] >= 500) {

    for (uint8_t i = 0; i < 4; i++) {
      if (state[i]) {
        setState(i);
        delay(300);
        state[i] = 0;
      }
    }

    Serial.print("readState(0) = ");
    Serial.println(readState(0));
    Serial.print("readState(1) = ");
    Serial.println(readState(1));

    if (getState(0)) digitalWrite(LED_BUILTIN, HIGH);
    else digitalWrite(LED_BUILTIN, LOW);

    sysTmr[0] = millis();
  }
}
