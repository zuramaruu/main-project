#pragma once

struct Sensor {
    void Init();

    void Handler();

    struct mq3Sens {
        void Calibrate(uint16_t ratioCleanAir);

        void readSens();

        void Debug(bool _st);

        float getValue();

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

    private:
        float value;
        float ratio;
        uint8_t fault;
        uint16_t rtd;
        uint32_t thrTmr;
        bool _debug = false;

        void errMsg(uint8_t _fault);
    } thermo;

private:
    void errMsg();
};

extern Sensor sens;
