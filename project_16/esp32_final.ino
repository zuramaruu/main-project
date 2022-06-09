#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "BINTANG_HOME";
const char WIFI_PASSWORD[] = "bintangku";

String HOST_NAME = "http://192.168.1.10/"; // change to your PC's IP address
String PATH_NAME   = "/post_data.php";

void setup() {
  Serial.begin(9600); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int randomValue = random(9999);
  int randomHour = random(0,23);
  int randomMinute = random(0,59);
  int randomDay = random(1,31);
  int randomMonth = random(1,12);
  String queryString = String("?data=A&date=")+String(randomDay)+String("%2F")+String(randomMonth)+String("%2F2022&time=")+String(randomHour)+String(".")+String(randomMinute)+String("&value=")+String(randomValue);

  HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME + queryString); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  
  delay(5000);
}
