#ifndef _DETECTOR
#define _DETECTOR

#define MQ3T_SAMPLING 500
#define MQ138T_SAMPLING 500

uint32_t mqTmr[2];

void setup() {
  Serial.begin(9600);
  MQ3_Init();
  //  MQ138_Init();
}

void loop() {
  //  readTCS3200();

  if (millis() - mqTmr[0] >= MQ3T_SAMPLING) {
    mqTmr[0] = millis();

    //    Serial.println("Analaog MQ 3   = " + String(getMQ3Val()));
    //    Serial.println("PPM MQ 3   = " + String(getPpm()));
    //    Serial.println("Volt MQ 3   = " + String(getMQ3Voltage()));

    readMQ3();

  }

  if (millis() - mqTmr[1] >= MQ138T_SAMPLING) {
    mqTmr[1] = millis();

    //    Serial.println("Analaog MQ 138 = " + String(getMQ138Val()));
  }

}
#endif
