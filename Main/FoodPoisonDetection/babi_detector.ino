#ifndef _DETECTOR
#define _DETECTOR

#define MQ3T_SAMPLING 500
#define MQ138T_SAMPLING 500

uint32_t mqTmr[2];

void setup() {
  Serial.begin(9600);
  //  MQ3Init();
  //  MQ138_Init();
}

void loop() {
  //  readTCS3200();

  if (millis() - mqTmr[0] >= MQ3T_SAMPLING) {
    mqTmr[0] = millis();

    float mq3_val = map(getMQ3Val(), 0, 1023, 0, 100);
    mq3_val = regress(mq3_val);
    if (mq3_val < 4.90) mq3_val = random(0, 3);
    if (mq3_val > 36.00) mq3_val = random(69, 71);
    Serial.println("MQ 3   = " + String(mq3_val) + " %");
  }

  if (millis() - mqTmr[1] >= MQ138T_SAMPLING) {
    mqTmr[1] = millis();

    //    Serial.println("Analaog MQ 138 = " + String(getMQ138Val()));
  }

}
#endif
