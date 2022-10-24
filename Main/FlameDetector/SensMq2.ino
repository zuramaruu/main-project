#define    BOARD           "Arduino UNO"
#define    TYPE            "MQ-2"

#define    PIN             A2
#define    VOLT_RES        5
#define    ADC_RES         10
#define    RatioCleanAir   9.83
#define    MQ_SAMPLING     500

#define    EXPONENTIAL     1
#define    LINEAR          0

#define    EXPONEN_A       36974
#define    EXPONEN_B       -3.109

MQUnifiedsensor MQ2(BOARD, VOLT_RES, ADC_RES, PIN, TYPE);

void mq2_Init() {
  MQ2.setRegressionMethod(EXPONENTIAL);
  MQ2.setA(EXPONEN_A); MQ2.setB(EXPONEN_B);
  MQ2.init();
}

void mq2_Calibrate() {
  Serial.print("Calibrating.");
  float calcR0 = 0;
  for (int i = 1; i <= 10; i ++)
  {
    MQ2.update();
    calcR0 += MQ2.calibrate(RatioCleanAir);
    Serial.print(".");
  }
  MQ2.setR0(calcR0 / 10);

  if (isinf(calcR0)) Serial.println("Open circuit");
  if (calcR0 == 0) Serial.println("Analog pin shorts");

  MQ2.serialDebug(true);
}

void mq2_readSens(bool _debug) {
  if (millis() - u_time[0] >= MQ_SAMPLING) {

    MQ2.update();
    mq2Value = MQ2.readSensor();
    if (_debug) {
      //      MQ2.serialDebug();
      Serial.print("CO = ");
      Serial.println(mq2Value);
    }

    u_time[0] = millis();
  }
}
