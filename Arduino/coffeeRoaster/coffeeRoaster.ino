#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <Adafruit_MAX31865.h>
#include <tcs3200.h>    // Include TCS3200 library 

#define WIFI_SSID "KASTARA GROUP INDONESIA"
#define WIFI_PASSWORD "KASTARA@2022"

#define API_KEY "AIzaSyDM16GhJdX3xRcSPJrPfNChROCKIEFsYZg"
#define DATABASE_URL "https://coffeeroaster-4bdb0-default-rtdb.firebaseio.com/"

//-- MAXMAX31865
#define RREF      430.0
#define RNOMINAL  100.0

//-- tcs3200
#define s_0 27
#define s_1 26
#define s_2 25
#define s_3 33
#define out_pin 32

// Use software SPI: CS, DI, DO, CLK
#define CS 5
#define DI 23
#define DO 19
#define CLK 18

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

Adafruit_MAX31865 thermo = Adafruit_MAX31865(CS, DI, DO, CLK);

#define num_of_colors 7   // Declares the number of colors the program can recognise (number of calibrated colors)
// distinctRGB[] array declares calibration values for each declared color in distinctColors[] array
int distinctRGB[num_of_colors][3] = {{250, 250, 250}, {0, 0, 0}, {142, 34, 41}, {166, 125, 71}, {35, 55, 38}, {150, 50, 43}, {22, 25, 45}};
// distinctColors[] array declares values to be returned from closestColor() function if specified color is recognised
String distinctColors[num_of_colors] = {"white", "black", "red", "yellow", "green", "orange", "blue"};

int red, green, blue;
tcs3200 tcs(s_0, s_1, s_2, s_3, out_pin); // (S0, S1, S2, S3, output pin) //

int suhuValue;
String warnaValue;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")) Serial.println("ok");
  else Serial.printf("%s\n", config.signer.signupError.message.c_str());
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  thermo.begin(MAX31865_3WIRE);
}

void loop() {
  if (Firebase.ready()) {
    //-- MAX31865
    uint16_t rtd = thermo.readRTD();
    Serial.print("RTD value: "); Serial.println(rtd);
    float ratio = rtd;
    ratio /= 32768;
    //    Serial.print("Ratio = "); Serial.println(ratio, 8);
    //    Serial.print("Resistance = "); Serial.println(RREF * ratio, 8);
    Serial.print("Temperature = "); Serial.println(thermo.temperature(RNOMINAL, RREF));

    Serial.print("Color = ");
    Serial.println(tcs.closestColor(distinctRGB, distinctColors, num_of_colors));
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

    Firebase.RTDB.setIntAsync(&fbdo, "suhu", thermo.temperature(RNOMINAL, RREF));
    Firebase.RTDB.setStringAsync(&fbdo, "warna", tcs.closestColor(distinctRGB, distinctColors, num_of_colors));
    if (Firebase.RTDB.getInt(&fbdo, "/suhu")) {
      if (fbdo.dataType() == "int") {
        suhuValue = fbdo.intData();
        Serial.println(suhuValue );
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getString(&fbdo, "/warna")) {
      if (fbdo.dataType() == "string") {
        warnaValue = fbdo.stringData();
        Serial.println(warnaValue);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }
  delay(1000);
}
void thermoReadFault() {
  uint8_t fault = thermo.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold");
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold");
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias");
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage");
    }
    thermo.clearFault();
  }
}
