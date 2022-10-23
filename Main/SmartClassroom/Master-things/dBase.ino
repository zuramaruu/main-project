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
  Firebase.RTDB.setString(&fbdo, F("/pzemA/voltage"), String(voltage[0])) ? "ok" : fbdo.errorReason().c_str();
  if (current[0] > 0.2) {
    Firebase.RTDB.setString(&fbdo, F("/pzemA/current"), String(current[0])) ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemA/energy"), String(energy[0])) ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemA/power"), String(power[0])) ? "ok" : fbdo.errorReason().c_str();
  } else {
    Firebase.RTDB.setString(&fbdo, F("/pzemA/current"), "0") ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemA/energy"), "0") ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemA/power"), "0") ? "ok" : fbdo.errorReason().c_str();
  }

  Firebase.RTDB.setString(&fbdo, F("/pzemB/voltage"), String(voltage[1])) ? "ok" : fbdo.errorReason().c_str();
  if (current[1] > 0.2) {
    Firebase.RTDB.setString(&fbdo, F("/pzemB/current"), String(current[1])) ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemB/energy"), String(energy[1])) ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemB/power"), String(power[1])) ? "ok" : fbdo.errorReason().c_str();
  } else {
    Firebase.RTDB.setString(&fbdo, F("/pzemB/current"), "0") ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemB/energy"), "0") ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemB/power"), "0") ? "ok" : fbdo.errorReason().c_str();
  }

  Firebase.RTDB.setString(&fbdo, F("/pzemC/voltage"), String(voltage[2])) ? "ok" : fbdo.errorReason().c_str();
  if (current[2] > 0.2) {
    Firebase.RTDB.setString(&fbdo, F("/pzemC/current"), String(current[2])) ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemC/energy"), String(energy[2])) ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemC/power"), String(power[2])) ? "ok" : fbdo.errorReason().c_str();
  } else {
    Firebase.RTDB.setString(&fbdo, F("/pzemC/current"), "0") ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemC/energy"), "0") ? "ok" : fbdo.errorReason().c_str();
    Firebase.RTDB.setString(&fbdo, F("/pzemC/power"), "0") ? "ok" : fbdo.errorReason().c_str();
  }

  Firebase.RTDB.setString(&fbdo, F("/sensors/dimmer"), String(outVal)) ? "ok" : fbdo.errorReason().c_str();
  Firebase.RTDB.setString(&fbdo, F("/sensors/temperature"), String(bme_val[0])) ? "ok" : fbdo.errorReason().c_str();
  Firebase.RTDB.setString(&fbdo, F("/sensors/humidity"), String(bme_val[1])) ? "ok" : fbdo.errorReason().c_str();
  Firebase.RTDB.setString(&fbdo, F("/sensors/rcwl"), String(FLAG)) ? "ok" : fbdo.errorReason().c_str();
  Firebase.RTDB.setString(&fbdo, F("/sensors/rtc"), String("NaN")) ? "ok" : fbdo.errorReason().c_str();

  //  Firebase.RTDB.setString(&fbdo, F("/state/relay1"), String(stateRelay[0])) ? "ok" : fbdo.errorReason().c_str();
  //  Firebase.RTDB.setString(&fbdo, F("/state/relay2"), String(stateRelay[1])) ? "ok" : fbdo.errorReason().c_str();
  //  Firebase.RTDB.setString(&fbdo, F("/state/relay3"), String(stateRelay[2])) ? "ok" : fbdo.errorReason().c_str();
  //  Firebase.RTDB.setString(&fbdo, F("/state/relay4"), String(stateRelay[3])) ? "ok" : fbdo.errorReason().c_str();

  String relay0 = Firebase.RTDB.getString(&fbdo, F("/state/relay1")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
  String relay1 = Firebase.RTDB.getString(&fbdo, F("/state/relay2")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
  String relay2 = Firebase.RTDB.getString(&fbdo, F("/state/relay3")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
  String relay3 = Firebase.RTDB.getString(&fbdo, F("/state/relay4")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
  stateRelay[0] = relay0.toInt();
  stateRelay[1] = relay1.toInt();
  stateRelay[2] = relay2.toInt();
  stateRelay[3] = relay3.toInt();
}
