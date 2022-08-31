void initWifi() {
  Serial.println();
  Serial.println("ssid: " + (String)ssid);
  Serial.println("password: " + (String)password);

  WiFi.begin(ssid, password);

  long int StartTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if ((StartTime + 10000) < millis()) break;
  }

  if (WiFi.status() == WL_CONNECTED) {
    char* apssid = "ESP32-CAM";
    char* appassword = "12345678";         //AP password require at least 8 characters.
    Serial.println("");
    Serial.print("Camera Ready! Use 'http://");
    Serial.print(WiFi.localIP());
    Serial.println("' to connect");
    WiFi.softAP((WiFi.localIP().toString() + "_" + (String)apssid).c_str(), appassword);
  }
  else {
    Serial.println("Connection failed");
    return;
  }
}


void initFirebase() {
  config_db.api_key = API_KEY;

  //  auth.user.email = USER_EMAIL;
  //  auth.user.password = USER_PASSWORD;

  config_db.database_url = DATABASE_URL;

  if (Firebase.signUp(&config_db, &auth, "", "")) Serial.println("ok firebase kenek");
  else Serial.printf("%s\n", config_db.signer.signupError.message.c_str());

  config_db.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  Firebase.begin(&config_db, &auth);
  Firebase.reconnectWiFi(true);

  //  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //  Firebase.reconnectWiFi(true);
  //  Firebase.setMaxRetry(firebaseData, 3);
  //  Firebase.setMaxErrorQueue(firebaseData, 30);
  //  Firebase.enableClassicRequest(firebaseData, true);

  //  FirebaseJson json;
  //  json.setDoubleDigits(3);
  //  json.add("photo", Photo2Base64());
  //
  //  String jsonData = "{\"photo\":\"" + Photo2Base64() + "\"}";
  //  String photoPath = "/esp32-cam";
  //
  //  Firebase.RTDB.pushJSON(&fbdo, photoPath, &json) ? "ok" : fbdo.errorReason().c_str();

  //  if (Firebase.pushJSON(firebaseData, photoPath, jsonData)) {
  //    Serial.println(firebaseData.dataPath());
  //    Serial.println(firebaseData.pushName());
  //    Serial.println(firebaseData.dataPath() + "/" + firebaseData.pushName());
  //  } else {
  //    Serial.println(firebaseData.errorReason());
  //  }
}
