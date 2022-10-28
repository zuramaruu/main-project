#include "WiFi.h"
#include "esp_camera.h"
#include "Arduino.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "driver/rtc_io.h"
#include "config.h"
#include <SPIFFS.h>
#include <FS.h>
#include <Firebase_ESP_Client.h>  
#include <addons/TokenHelper.h>

String IMAGE_PATH = "/pictures/image.jpg";

const char* ssid = "KASTARA GROUP INDONESIA";
const char* password = "KASTARA@2022";

boolean new_image = true;

FirebaseData fbdo;
FirebaseAuth authentication;
FirebaseConfig configuration;

bool done = false;
uint32_t sysTmr;

void setup() {
  Serial.begin(115200);

  WiFiInit();
  cameraInitConfig();
  InitFireBase();
}

void loop() {
  SerialParseIn();
  if (new_image) {
    captureSave_photo();
    if (Firebase.ready()) {
      Serial.print("Uploading Photo... ");

      if (Firebase.Storage.upload(&fbdo,
                                  STORAGE_BUCKET_ID,
                                  IMAGE_PATH,
                                  mem_storage_type_flash,
                                  IMAGE_PATH,
                                  "image/jpeg" )) {
        Serial.printf("\nDownload URL: %s\n", fbdo.downloadURL().c_str());
      }
      else {
        Serial.println(fbdo.errorReason());
      }
    }
    new_image = false;
  }
}
