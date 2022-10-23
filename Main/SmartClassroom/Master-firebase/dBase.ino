void FirebaseInit() {
  config.api_key = API_KEY;
  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void FirebaseHandler() {
  
  String relay0 = Firebase.RTDB.getString(&fbdo, F("/state/relay1")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
  String relay1 = Firebase.RTDB.getString(&fbdo, F("/state/relay2")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
  String relay2 = Firebase.RTDB.getString(&fbdo, F("/state/relay3")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
  String relay3 = Firebase.RTDB.getString(&fbdo, F("/state/relay4")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
  stateRelay[0] = relay0.toInt();
  stateRelay[1] = relay1.toInt();
  stateRelay[2] = relay2.toInt();
  stateRelay[3] = relay3.toInt();
}
