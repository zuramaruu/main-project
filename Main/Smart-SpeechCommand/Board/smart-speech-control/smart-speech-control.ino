#include "server.h"

#define   POT      13
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
    
    if (server.read(RL_1) == ON)
      digitalWrite(pin[0], LOW);
    else if (server.read(RL_1) == OFF)
      digitalWrite(pin[0], HIGH);

    if (server.read(RL_2) == ON)
      digitalWrite(pin[1], LOW);
    else if (server.read(RL_2) == OsFF)
      digitalWrite(pin[1], HIGH);

    sysTmr[0] = millis();
  }

  if (millis() - sysTmr[1] >= 30) {
    int val = analogRead(POT);
    server.send(val);

    sysTmr[1] = millis();
  }
}

void InitPin() {
  for (uint8_t i = 0; i < 3; i++) {
    if (i > 1) pinMode(pin[i], INPUT);
    else pinMode(pin[i], OUTPUT);
  }
}
