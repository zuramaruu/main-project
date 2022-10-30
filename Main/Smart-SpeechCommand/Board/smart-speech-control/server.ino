#include "WiFi.h"
#include "HTTPClient.h"
#include "server.h"

#define   self (*this)
#define   SSID_WIFI "KASTARA GROUP INDONESIA"
#define   PASS_WIFI "KASTARA@2022"
#define   DOMAIN    "http://192.168.200.6:5000"

Serv server;

void Serv::Init() {
  self.initWifi();
}

bool Serv::send(int data) {
  String req = String(DOMAIN) +
               "/set_value?set=" +
               String(data);

  bool check = false;
  if (!self.wifiStatus) return false;
  else {
    HTTPClient http;
    http.begin(req);

    if (int(http.GET()) == 200) {
      check = true;
    }
  }

  return check;
}

String Serv::read(uint8_t indx) {
  String buff = "";
  String req = String(DOMAIN) + "/state";

  if (!self.wifiStatus) buff = "";
  else {
    HTTPClient http;
    http.begin(req);

    if (int(http.GET()) == 200) {
      buff = self.parseStr(http.getString(), " ", indx - 1);
    }
  }

  return buff;
}

String Serv::parseStr(String data,
                      char separator[],
                      int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator[0] || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void Serv::initWifi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_WIFI, PASS_WIFI);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }

  Serial.println("\n Connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP()); //IP address assigned to your ESP

  self.wifiStatus = 1;
  delay(100);
}
