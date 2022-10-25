#define    IR_PIN           2
#define    IR_SAMPLING      20

void ir_Init() {
        pinMode(LED_BUILTIN, OUTPUT);
        pinMode(IR_PIN, INPUT);
}

void ir_readSens(bool _debug) {
        if (millis() - u_time[2] >= IR_SAMPLING) {

                irState = !digitalRead(IR_PIN);
                if (_debug) {
                        Serial.print("State = ");
                        Serial.println(irState);
                }

                u_time[2] = millis();
        }
}
