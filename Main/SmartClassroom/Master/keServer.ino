void kirimKeServerPZEM() {
  String httpRequestData = String(DOMAIN)
                           + String("/api/board/PZEM.php")
                           + String("?voltage1=") + voltage[0]
                           + String("&voltage2=") + voltage[1]
                           + String("&voltage3=") + voltage[2]
                           + String("&current1=") + current[0]
                           + String("&current2=") + current[1]
                           + String("&current3=") + current[2]
                           + String("&power1=") + power[0]
                           + String("&power2=") + power[1]
                           + String("&power3=") + power[2]
                           + String("&energy1=") + energy[0]
                           + String("&energy2=") + energy[1]
                           + String("&energy3=") + energy[2]
                           + String("&power1=") + power[0]
                           + String("&power2=") + power[1]
                           + String("&power3=") + power[2]
                           + String("&energy1=") + energy[0]
                           + String("&energy2=") + energy[1]
                           + String("&energy3=") + energy[2];
  HTTPClient http;

  //GET methode
  http.begin(httpRequestData);
  int httpResponseCode = http.GET();
  String payload = http.getString();
  Serial.println(httpResponseCode);
  if (httpResponseCode == 200) {
    // kirimKeServer();
  }
  http.end();

  //  if (statusWifi == 1) {
  //  }
  //  else {
  //    WIFI_INIT() ;
  //  }
}
void kirimKeServerBME() {
  String httpRequestData = String(DOMAIN)
                           + String("/api/board/BME.php")
                           + String("?suhu=") + bme_val[0]
                           + String("&kelembapan=") + bme_val[1];
  HTTPClient http;

  //GET methode
  http.begin(httpRequestData);
  int httpResponseCode = http.GET();
  String payload = http.getString();
  Serial.println(httpResponseCode);
  if (httpResponseCode == 200) {
    // kirimKeServer();
  }
  http.end();

  //  if (statusWifi == 1) {
  //  }
  //  else {
  //    WIFI_INIT() ;
  //  }
}


//void kirimKeServerStateRelay() {
//  String httpRequestData = String(DOMAIN)
//                           + String("/api/board/stateRelay.php")
//                           + String("?stateRelay1=") + stateRelay[0]
//                           + String("&stateRelay2=") + stateRelay[1]
//                           + String("&stateRelay3=") + stateRelay[2];
//  HTTPClient http;
//
//  //GET methode
//  http.begin(httpRequestData);
//  int httpResponseCode = http.GET();
//  String payload = http.getString();
//  Serial.println(httpResponseCode);
//  if (httpResponseCode == 200) {
//    // kirimKeServer();
//  }
//  http.end();
//
//  //  if (statusWifi == 1) {
//  //
//  //  }
//  //  else {
//  //    WIFI_INIT() ;
//  //  }
//}
