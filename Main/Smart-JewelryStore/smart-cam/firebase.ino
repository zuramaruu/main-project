bool WiFiInit() {
  bool state = false;
  WiFi.begin(ssid, password);
  if (WiFi.status() == WL_CONNECTED) state = true;
  return state;
}

void InitFireBase() {
  configuration.api_key = API_KEY;
  authentication.user.email = USER_EMAIL;
  authentication.user.password = USER_PASSWORD;
  configuration.token_status_callback = tokenStatusCallback;

  Firebase.begin(&configuration, &authentication);
  Firebase.reconnectWiFi(true);
}
