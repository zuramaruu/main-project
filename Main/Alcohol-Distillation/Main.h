#pragma once

struct MainSys {
    void Init(void(*Start)(void));
    void Handler();

  private:
    uint32_t mainTmr;
};

extern MainSys sys;
