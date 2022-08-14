void startMotion() {
  int readMotion = digitalRead(RCWL);
  if ((readMotion > 0) && (FLAG == 0)) {
    /* "Motion Detected" */
    FLAG = 1;
  }
  if (readMotion == 0) {
    /* "No Motion" */
    FLAG = 0;
  }
  allString[0] = "RCWL" + String("#") + String(FLAG) + String("#");
  //  delay(50);
}
