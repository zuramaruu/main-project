#include "MQUnifiedsensor.h"

#define   DEBUG_TIME   500

float lm35Value;
float mq2Value;
uint16_t irState;

uint32_t u_time[4];
uint32_t sysTmr;

void setup() {
        Serial.begin(9600);
        mq2_Init();
        mq2_Calibrate();
        lm35_Init();
        ir_Init();
}

void loop() {
        mq2_readSens();
        lm35_ReadSens();
        ir_readSens();
        debug();

        if (lm35Value >= 50) Serial.println("Warning !! Kebakaran");
        if ((lm35Value < 50 && lm35Value >= 40) && mq2Value > 30) Serial.println("Warning !! Kebakaran");
        if ((lm35Value < 40 && lm35Value >= 35) && mq2Value > 40 && irState == 1)
                Serial.println("Warning !! Kebakaran");

        if (millis() - sysTmr >= 30) {

                if (irState) digitalWrite(LED_BUILTIN, HIGH);
                else digitalWrite(LED_BUILTIN, LOW);

                sysTmr = millis();
        }
}

void debug() {
        if (millis() - u_time[3] >= DEBUG_TIME) {

                Serial.print("Suhu  = ");
                Serial.println(lm35Value);
                Serial.print("State = ");
                Serial.println(irState);
                Serial.print("CO    = ");
                Serial.println(mq2Value);

                u_time[3] = millis();
        }
}
