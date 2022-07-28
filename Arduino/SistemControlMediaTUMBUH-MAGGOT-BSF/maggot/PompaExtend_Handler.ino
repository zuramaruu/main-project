int pinRelayPompaExt[6] = {47, 49, 22, 45, 43, 41};

void PompaExt_Init() {
  for (int i = 0; i < 6; i++) {
    pinMode(pinRelayPompaExt[i], OUTPUT);
    digitalWrite(pinRelayPompaExt[i], HIGH);
  }
}

void LoopTest_Pompa() {
  for (int i = 0; i < 6; i++) {
    Serial.println("LOOP TEST RELAY POMPA : " + String(i));
    digitalWrite(pinRelayPompaExt[i], LOW);
    delay(1000);
    digitalWrite(pinRelayPompaExt[i], HIGH);
    delay(1000);
  }
}

void Control_PompaExt(int pompa, int state) {
  int i = pompa - 1;  // 1 - 1 = 0
  if (state == 1)  digitalWrite(pinRelayPompaExt[i], HIGH);
  if (state == 0)  digitalWrite(pinRelayPompaExt[i], LOW);
}
