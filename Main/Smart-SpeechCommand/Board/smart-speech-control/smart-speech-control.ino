#include "server.h"

#define   POT      34
#define   SW_1     12
#define   SW_2     14
#define   ON       "ON"
#define   OFF      "OFF"

#define   RL_1      1
#define   RL_2      2

const uint8_t pin[3] = {POT, SW_1, SW_2};
uint32_t sysTmr[2];

void setup() {
  Serial.begin(115200);
  server.Init();
  InitPin();
}

void loop() {
  if (millis() - sysTmr[0] >= 30) {
    Serial.println("server.read(RL_1) = " + server.read(RL_1));
    Serial.println("server.read(RL_2) = " + server.read(RL_2));

    if (server.read(RL_1) == ON)
      digitalWrite(pin[1], LOW);
    else if (server.read(RL_1) == OFF)
      digitalWrite(pin[1], HIGH);

    if (server.read(RL_2) == ON)
      digitalWrite(pin[2], LOW);
    else if (server.read(RL_2) == OFF)
      digitalWrite(pin[2], HIGH);

    sysTmr[0] = millis();
  }

  if (millis() - sysTmr[1] >= 30) {
    int val = analogRead(pin[0]);
    Serial.println("val = " + String(val));
    server.send(val);

    sysTmr[1] = millis();
  }
}

void InitPin() {
  for (uint8_t i = 0; i < 3; i++) {
    if (i < 1) pinMode(pin[i], INPUT);
    else pinMode(pin[i], OUTPUT);
  }
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);

  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
}
