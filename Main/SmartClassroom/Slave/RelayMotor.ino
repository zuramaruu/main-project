void mainControl() {
  if (relayState[0] == 1) FLAG = 1;
  else if (relayState[0] == 0) FLAG = 0;

  if (FLAG) relayTigaOn();
  else relayTigaOff();

  if (relayState[1]) relayDuaOn();
  else relayDuaOff();
  if (relayState[2]) relaySatuOn();
  else relaySatuOff();

  if (motorState[0] && !motorState[1]) runMotorA();
  if (!motorState[0] && motorState[1]) runMotorB();

  if (!motorState[0] && !motorState[1]) motorStop();
  //  if (motorState[0] && motorState[1]) motorStop();
}

void relaySatuOn() {
  digitalWrite(RELAY_1, LOW);
}
void relayDuaOn() {
  digitalWrite(RELAY_2, LOW);
}
void relayTigaOn() {
  digitalWrite(RELAY_3, LOW);
}

void relaySatuOff() {
  digitalWrite(RELAY_1, HIGH);
}
void relayDuaOff() {
  digitalWrite(RELAY_2, HIGH);
}
void relayTigaOff() {
  digitalWrite(RELAY_3, HIGH);
}

void runMotorA() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);
}

void runMotorB() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 255);
}

void motorStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);
}
