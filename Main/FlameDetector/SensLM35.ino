#define    LM_PIN           A1
#define    LM_SAMPLING      500

#define    V_OUT(ADC) (ADC / 1023 * 5)
#define    TEMP_C(VO) (VO * 100)

void lm35_Init() {
        pinMode(LM_PIN, INPUT);
}

void lm35_ReadSens() {
        if (millis() - u_time[1] >= LM_SAMPLING) {

                lm35Value = V_OUT(float (analogRead(LM_PIN)));
                lm35Value = TEMP_C(lm35Value);

                u_time[1] = millis();
        }
}
