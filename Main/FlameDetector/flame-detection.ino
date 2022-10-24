#include "MQUnifiedsensor.h"

float lm35Value;
float mq2Value;
uint16_t irState;

uint32_t u_time[3];
uint32_t sysTmr;

void setup() {
  Serial.begin(9600);
  mq2_Init();
  mq2_Calibrate();
  //  lm35_Init();
  ir_Init();
}

void loop() {
  mq2_readSens(true);
  //  lm35_ReadSens(true);
  ir_readSens(true);

  if (millis() - sysTmr >= 30) {

    if (irState) digitalWrite(LED_BUILTIN, HIGH);
    else digitalWrite(LED_BUILTIN, LOW);

    sysTmr = millis();
  }
}
