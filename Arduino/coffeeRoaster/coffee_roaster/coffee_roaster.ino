#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "KASTARA GROUP INDONESIA"
#define WIFI_PASSWORD "KASTARA@2022"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDM16GhJdX3xRcSPJrPfNChROCKIEFsYZg"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://coffeeroaster-4bdb0-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
bool signupOK = false;

float max31865_temperature;
float max31865_resistance;

String tcs_color;
int r, g, b;

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

  /* Assign the api key (required) */
  config.api_key = API_KEY;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  max31865_Init();
  Tcs3200_Init();
  relay_Init();
  Servo_Init();
}

void loop() {
  max31865_Begin();
  float suhu = getTemperatureMax31865();
  
  //-- Polynomial Regression
  suhu = -6.1423382062643057 + (0.92142277067818967 * suhu);

  Serial.println("Suhu = " + String(suhu) + " C");

  //  Serial.println("Suhu = " + String(int(getTemperatureMax31865())) + " C");
  //  Serial.println("Warna = " + tcs3200getColor());

  //  Serial.println("Nilai R = " + String(tcs3200getRValue()));
  //  Serial.println("Nilai G = " + String(tcs3200getGValue()));
  //  Serial.println("Nilai B = " + String(tcs3200getBValue()));

  if (Firebase.ready() && signupOK) {
    Firebase.RTDB.setIntAsync(&fbdo, "suhu", int(getTemperatureMax31865()));
    Firebase.RTDB.setStringAsync(&fbdo, "warna", String(tcs3200getColor()));
  }

  //  if (Firebase.RTDB.getFloat(&fbdo, "/test/float")) {
  //    if (fbdo.dataType() == "float") {
  //      floatValue = fbdo.floatData();
  //      Serial.println(floatValue);
  //    }
  //  }
  //  else {
  //    Serial.println(fbdo.errorReason());
  //  }

  //  relaySatuOn();
  //  delay(1000);
  //  relaySatuOff();
  //  delay(1000);
  //  relayDuaOn();
  //  delay(1000);
  //  relayDuaOff();
  //  delay(1000);
  //  relaySatuOff();

  //  servoBuka();
  //  delay(1000);
  //  servoTutup();
  //  delay(1000);

  delay(500);
}
