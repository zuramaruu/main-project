#pragma once

struct Sensor {
    void Init();

    void Handler();

    struct mq3Sens {
        void Calibrate(uint16_t ratioCleanAir);

        void readSens();

        void Debug(bool _st);

        float getValue();

        float getValueF();

    private:
        float value;
        bool _debug = false;
        uint32_t mqTmr;

        void errMsg(bool err);
    } mq3;

    struct thermoCouple {
        void readSens();

        void Debug(bool _st);

        float getValue();

        float getValueF();

    private:
        float value;
        uint32_t thrTmr;
        bool _debug = false;

        void errMsg();
    } thermo;

private:
    void errMsg();
};

extern Sensor sens;
