#include "Sensors.h"
#include "Cfg.h"
#include "UI.h"
#include "MQUnifiedsensor.h"
#include "Adafruit_MAX31865.h"

#define   Board           "Arduino UNO"
#define   Type            "MQ-3"

#define   VoltRes         5
#define   ADCRes          10
#define   RatioCleanAir   60
#define   Mq3SamplingT    500

#define   Exponential     1
#define   Linear          0
#define   Inf             1
#define   Zero            0

#define   RREF            430.0
#define   RNOMINAL        100.0
#define   MAX_3WIRE       1
#define   MAX_4WIRE       0
#define   T_SAMPLING      1000

#define   GET_RESIST(REF, RAT) REF * RAT

Sensor sens;

MQUnifiedsensor MQ3(Board, VoltRes, ADCRes, MQ3p, Type);
Adafruit_MAX31865 th = Adafruit_MAX31865(CS, DI, DO, CLK);

void Sensor::Init() {
        MQ3.setRegressionMethod(Exponential);
        MQ3.setA(4.8387); MQ3.setB(-2.68);
        MQ3.init();

        th.begin(MAX_3WIRE);
}

void Sensor::Handler() {
}

void Sensor::mq3Sens::Calibrate(uint16_t ratioCleanAir) {
        Serial.print("Calibrating.");
        float calcR0 = 0;
        for (int i = 1; i <= 10; i ++) {
                MQ3.update();
                calcR0 += MQ3.calibrate(ratioCleanAir);
                Serial.print(".");
        }
        MQ3.setR0(calcR0 / 10);

        if (isinf(calcR0)) errMsg(Inf);
        if (calcR0 == 0) errMsg(Zero);

        Serial.print("Done.");
        MQ3.serialDebug(true);
}

void Sensor::mq3Sens::readSens() {
        if (millis() - mqTmr >= Mq3SamplingT) {

                MQ3.update();
                this->value = MQ3.readSensor();

                if (this->_debug) MQ3.serialDebug();

                mqTmr = millis();
        }
}

float Sensor::mq3Sens::getValue() {
        return this->value;
}

void Sensor::mq3Sens::Debug(bool _st) {
        this->_debug = _st;
}

void Sensor::mq3Sens::errMsg(bool err) {
        switch (err) {
                case Inf: Serial.println("Open circuit detected"); while (1); break;
                case Zero: Serial.println("Analog pin shorts"); while (1); break;
        }
}

void Sensor::thermoCouple::readSens() {
        if (millis() - thrTmr >= T_SAMPLING) {

                this->rtd = th.readRTD();
                this->ratio = rtd;
                this->ratio /= 32768;
                this->fault = th.readFault();

                if (fault) errMsg(fault);
                this->value = th.temperature(RNOMINAL, RREF);

                if (this->_debug) {
                        Serial.print("Ratio = "); Serial.println(ratio, 8);
                        Serial.print("Resistance = "); Serial.println(GET_RESIST(RREF, ratio), 8);
                        Serial.print("Temperature = "); Serial.println(th.temperature(RNOMINAL, RREF));
                }

                thrTmr = millis();
        }
}

void Sensor::thermoCouple::Debug(bool _st) {
        this->_debug = _st;
}

float Sensor::thermoCouple::getValue() {
        return this->value;
}

void Sensor::thermoCouple::errMsg(uint8_t _fault) {
        Serial.print("Fault 0x"); Serial.println(fault, HEX);
        if (fault & MAX31865_FAULT_HIGHTHRESH) Serial.println("RTD High Threshold");
        if (fault & MAX31865_FAULT_LOWTHRESH) Serial.println("RTD Low Threshold");
        if (fault & MAX31865_FAULT_REFINLOW) Serial.println("REFIN- > 0.85 x Bias");
        if (fault & MAX31865_FAULT_REFINHIGH) Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
        if (fault & MAX31865_FAULT_RTDINLOW) Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
        if (fault & MAX31865_FAULT_OVUV) Serial.println("Under/Over voltage");
        th.clearFault();
        Serial.println();
}
