int pinRelay[9] = {37, 31, 23, 33, 25, 27, 29, 35, 39};

void Relay_Init() {
  for (int i = 0; i < 9; i++) {
    pinMode(pinRelay[i], OUTPUT);
    digitalWrite(pinRelay[i], HIGH);
  }
}

void LoopTest_Relay() {
  for (int i = 0; i < 9; i++) {
    Serial.println("LOOP TEST RELAY UTAMA : " + String(i));
    digitalWrite(pinRelay[i], LOW);
    delay(1000);
    digitalWrite(pinRelay[i], HIGH);
    delay(1000);
  }
}
void Control_Pompa(int pompa, int state) {
  int i = pompa - 1;  // 1 - 1 = 0
  if (state == 1)  digitalWrite(pinRelay[i], HIGH);
  if (state == 0)  digitalWrite(pinRelay[i], LOW);
}
