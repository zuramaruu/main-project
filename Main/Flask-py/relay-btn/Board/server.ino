String readState(uint8_t indx) {
  String a = "";

  String httpRequestData = String(DOMAIN) + "/state";

  if (wifiStatus == 1) {
    WiFiClient client;
    HTTPClient http;

    http.begin(httpRequestData);
    int httpResponseCode = http.GET();
    String payload = http.getString();

    if (httpResponseCode == 200) {
      String Buff_Response = parseStr(payload, " ", indx);
      a  = Buff_Response;
    }
    http.end();
  }
  return a;
}

bool getState(uint8_t indx) {
  if (readState(indx) == ON) {
    return true;
  } else {
    return false;
  }
}

void setState(uint8_t num) {
  String httpRequestData = String(DOMAIN) + "/set_state?set=" + String(num);
  Serial.println("setState = " + String(num));
  if (wifiStatus == 1) {
    HTTPClient http;

    http.begin(httpRequestData);
    int httpResponseCode = http.GET();
    String payload = http.getString();

    if (httpResponseCode == 200) {}
    http.end();
  }
}

String parseStr(String data, char separator[], int index)
{
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

void SerialParseIn() {
  if (millis() - sysTmr[1] >= 10) {

    if (Serial.available() > 1) {
      String read[3];
      read[0] = Serial.readString();
      read[1] = parseStr(read[0], "#", 0);
      if (read[1] == "st1") {
        read[2] = parseStr(read[0], "#", 1);
        state[0] = read[2].toInt();
      } else if (read[1] == "st2") {
        read[2] = parseStr(read[0], "#", 1);
        state[1] = read[2].toInt();
      } else if (read[1] == "st3") {
        read[2] = parseStr(read[0], "#", 1);
        state[2] = read[2].toInt();
      } else if (read[1] == "st4") {
        read[2] = parseStr(read[0], "#", 1);
        state[3] = read[2].toInt();
      }
    }

    sysTmr[1] = millis();
  }
}
