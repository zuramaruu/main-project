#define    LM_PIN           A1
#define    LM_SAMPLING      500

#define    V_OUT(ADC) (ADC / 1023 * 5)
#define    TEMP_C(VO) (VO * 100)

void lm35_Init() {
        pinMode(LM_PIN, INPUT);
}

void lm35_ReadSens(bool _debug) {
        if (millis() - u_time[1] >= LM_SAMPLING) {

                lm35Value = V_OUT(float (analogRead(LM_PIN)));
                lm35Value = TEMP_C(lm35Value);

                if (_debug) {
                        Serial.print("Adc = ");
                        Serial.println(analogRead(LM_PIN));
                        Serial.print("Suhu = ");
                        Serial.println(lm35Value);
                }

                u_time[1] = millis();
        }
}
