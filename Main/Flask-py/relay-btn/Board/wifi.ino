void InitWifi() {
  WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_WIFI, PASS_WIFI);

  Serial.print("Connecting to ");
  Serial.println(SSID_WIFI);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }

  Serial.println("\n Connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP()); //IP address assigned to your ESP

  wifiStatus = 1;
  delay(100);
}

void WiFiCheck() {
  Serial.println("Wifi = " + String(wifiStatus));
  if ((WiFi.status() != WL_CONNECTED)) {
    wifiStatus = 0;
    InitWifi();
  }
  else if (WiFi.isConnected()) wifiStatus = 1;
}
