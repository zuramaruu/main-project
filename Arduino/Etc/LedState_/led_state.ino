#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define LED_BUILTIN_ 2

const char* ssid     = "KASTARA GROUP INDONESIA";
const char* password = "KASTARA@2022";

const char* server_n = "http://192.168.200.239/led_data/post_data.php";

//String HOST_NAME = "http://192.168.200.239/";
//String PATH_NAME = "led_data/post_data.php";

int led_state = 0;
unsigned int u_time = 0;
String apiKeyValue = "tPmAT5Ab3j7F9";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println(WiFi.localIP());
  pinMode(LED_BUILTIN_, OUTPUT);
}
void loop() {
  if (millis() - u_time >= 1000) {
    u_time = millis();
    led_state = (led_state == 0) ? 1 : 0;
  }
  digitalWrite(LED_BUILTIN_, led_state);


  WiFiClient wifiClient;
  HTTPClient http;
  http.begin(wifiClient, server_n); //HTTP

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String post_data = "api_key=" + apiKeyValue + "&value_led_s=" + led_state;

  String payload = http.getString();
  Serial.println(post_data);
  Serial.println(payload);

  auto httpCode = http.POST(post_data);

  //  int httpCode = http.GET();
  //  // httpCode will be negative on error
  //  if (httpCode > 0) {
  //    // file found at server
  //    if (httpCode == HTTP_CODE_OK) {
  //      String payload = http.getString();
  //      Serial.println(payload);
  //    } else {
  //      // HTTP header has been send and Server response header has been handled
  //      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  //    }
  //  } else {
  //    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  //  }

  http.end();

  delay(1000);
}
