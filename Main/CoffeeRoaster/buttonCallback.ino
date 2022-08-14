void lightButton_isPressed() {
  SP = 100; /* Suhu 193 */
  SP_Time = 1; /* Menit 18 */
  if (t_minute == SP_Time) {
    timerReset(); SP = 0;
    servoTutup();
    _reset = 1;
  }
}
void brownButton_isPressed() {
  SP = 203; /* Suhu 203 */
  SP_Time = 24; /* Menit 24 */
  if (t_minute == SP_Time) {
    timerReset(); SP = 0;
    servoTutup();
    _reset = 1;
  }
}
void darkButton_isPressed() {
  SP = 213; /* Suhu 213 */
  SP_Time = 26; /* Menit 26 */
  if (t_minute == SP_Time) {
    timerReset(); SP = 0;
    servoTutup();
    _reset = 1;
  }
}
void manualStateOn() {
  servoManual();
}
void manualStateOff() {
  _reset_btn_manual = 1;
}
