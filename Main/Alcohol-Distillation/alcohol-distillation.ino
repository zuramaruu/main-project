#include "Main.h"
#include "Cfg.h"
#include "Sensors.h"
#include "UI.h"

void Start() {
        pid.SetConstants(0.1, 0.03, 0, 0.1);
        pid.SetLimit(0, 255);
        ui.Init();
        sens.Init();
}

void setup() {
        sys.Init(Start);
}

void loop() {
        sens.mq3.readSens();
        sens.mq3.Debug(true);
        sens.thermo.readSens();
        sens.thermo.Debug(true);
}
