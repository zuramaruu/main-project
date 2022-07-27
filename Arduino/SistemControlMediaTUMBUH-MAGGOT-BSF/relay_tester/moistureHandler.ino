int pinMoisture[3] = {A0, A1, A2};
float kfSensorVolts = 0.0048828125;
void bacaMoisture() {
  if (DEBUG) {
    Serial.println("Moisture 1 = " + String(analogRead(pinMoisture[0])));
    Serial.println("Moisture 2 = " + String(analogRead(pinMoisture[1])));
    Serial.println("Moisture 3 = " + String(analogRead(pinMoisture[2])));
  }
  delay(1000);
}
void bacaTeganganMoisture() {

}
