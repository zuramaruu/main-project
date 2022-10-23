uint32_t rcTmr;
uint32_t stTmr;
uint8_t count = 0;

#define read_s digitalRead(RCWL)

void startMotion() {
  if (millis() - rcTmr >= 1) {
    if (read_s && !relayState[0]) FLAG = 1;
    //    count++;
    //    if (count > 30 && read_s) {
    //      if (read_s) FLAG = 1;
    //    }
    //
    //    if (read_s) count = 0;
    //
    //    Serial.println("count = " + String(count));
    //    Serial.println("readMotion = " + String(read_s));
    //    Serial.println("FLAG = " + String(FLAG));

    rcTmr = millis();
  }

  //  if (millis() - stTmr >= 10) {
  //
  //    stTmr = millis();
  //  }

  allString[0] = "RCWL" + String("#") + String(FLAG) + String("#");
  //  Serial.println("Motion = " + String(readMotion));
}
