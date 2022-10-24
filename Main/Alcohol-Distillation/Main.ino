#include "Main.h"
#include "Cfg.h"

MainSys sys;

void MainSys::Init(void(*StartCallback)(void)) {

  StartCallback();
}

void MainSys::Handler() {
}
