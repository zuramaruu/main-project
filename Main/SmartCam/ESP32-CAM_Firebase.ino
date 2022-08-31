#include <FirebaseESP32.h>

//FirebaseData firebaseData;
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

//const char* ssid = "KASTARA GROUP INDONESIA";
//const char* password = "KASTARA@2022";

const char* ssid = "AJ_KRI_LT8_2G";
const char* password = "kri_2022";

#define API_KEY "AIzaSyBlVfeKCPRbhCE1aGNw0d1-ij5J55ZltKg"
#define DATABASE_URL "https://esp32cam-7a3b6-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
//#define USER_EMAIL "USER_EMAIL"
//#define USER_PASSWORD "USER_PASSWORD"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config_db;

////////////////////////////////////////////////////////////////////////////////////////

//#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "Base64.h"
#include "esp_camera.h"
//#include "camera_pins.h"

// WARNING!!! Make sure that you have either selected ESP32 Wrover Module,
//            or another board which has PSRAM enabled

//CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  ////////////////////////////////////////////////////////////////////////////////////////
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  initWifi();
  initCamera();

  ////////////////////////////////////////////////////////////////////////////////////////

  initFirebase();
}

void loop() {

  if (Firebase.ready()) {
    Firebase.RTDB.setStringAsync(&fbdo, "test", Photo2Base64());
    Serial.println(Photo2Base64());
  }

  delay(2000);
}
