bool sendToServer() {
  bool a = false;
  String httpRequestData = String(DOMAIN)
                           + String("/api/board/api.php?flow=in&data=")
                           + String(voltage[0]) + ";"
                           + String(voltage[1]) + ";"
                           + String(voltage[2]) + ";"
                           + String(current[0]) + ";"
                           + String(current[1]) + ";"
                           + String(current[2]) + ";"
                           + String(power[0]) + ";"
                           + String(power[1]) + ";"
                           + String(power[2]) + ";"
                           + String(energy[0]) + ";"
                           + String(energy[1]) + ";"
                           + String(energy[2]) + ";"
                           + String(bme_val[0]) + ";"
                           + String(bme_val[1]) + ";"
                           + String(totalHarga[0]) + ";"
                           + String(totalHarga[1]) + ";"
                           + String(totalHarga[2]) + ";";

  if (statusWifi == 1) {
    HTTPClient http;

    http.begin(httpRequestData);
    //    Serial.println("httpRequestData = " + String(httpRequestData));
    int httpResponseCode = http.GET();
    String payload = http.getString();
    //    Serial.print(httpRequestData);

    if (httpResponseCode == 200) {

      //      Serial.println("payload = " + String(payload));
      //      String Buff_Response = parseString(payload, "#", 0);
      a = true;
      //      a  = Buff_Response.toInt();
    }
    //    Serial.println("httpResponseCode = " + String(httpResponseCode));
    http.end();
  }
  else {
    WIFI_INIT();
    a = false;
  }
  return a;
}

int getState(String dat) {
  int a = 0;
  String httpRequestData = String(DOMAIN)
                           + String("/api/board/") //r1, r2, r3, rlampu, rmotor, ldimmer;
                           + String(dat) + ".php?flow=out";
  if (statusWifi == 1) {
    HTTPClient http;

    //GET methode
    http.begin(httpRequestData);
    //    Serial.println("httpRequestData = " + String(httpRequestData));
    int httpResponseCode = http.GET();
    String payload = http.getString();
    //    Serial.print(httpRequestData);

    if (httpResponseCode == 200) {

      //      Serial.println("payload = " + String(payload));
      String Buff_Response = parseString(payload, "#", 0);
      a  = Buff_Response.toInt();
    }
    //    Serial.println("httpRes = " + String(httpResponseCode));
    http.end();
  }
  else {
    WIFI_INIT();
    a = 0;
  }
  return a;
}

void readRelayState() {
  stateRelay[0] = getState("r1");
  uint8_t buff = getState("r2");
  stateRelay[2] = getState("r3");
  uint8_t buff_motor = getState("rmotor");
  outVal = getState("ldimmer");
  if (readSuhu() == 1 || buff == 1) stateRelay[1] = 1;
  else stateRelay[1] = 0;
}

void checkIsNanAndSend() {
  //  sendToServer();
  if (isnan(voltage[0]) || isnan(voltage[1]) || isnan(voltage[2]) || bme_val[0] == 0) {
    Serial.println("Ada Nan atau 0");
  } else {
    sendToServer();
  }
}
