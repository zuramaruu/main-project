#include "Main.h"
#include "Cfg.h"
#include "Sensors.h"
#include "UI.h"

void Start() {
  ui.Init();
  sens.Init();
}

void setup() {
  sys.Init(Start);
}

void loop() {
  sens.mq3.readSens();
  sens.mq3.Debug(true);
}
