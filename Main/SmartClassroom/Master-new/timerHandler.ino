uint32_t tmTmr;

void timerInit() {
  timer.setInterval(1000);
  timer.setCallback(timerCallback);
  timer.start();

  timer2.setInterval(1000);
  timer2.setCallback(timerCallback2);
  timer2.start();
}

void timerCtrl() {
  if (millis() - tmTmr >= 1000) {
    if (!motorState[0]) {
      t_second_forward = 5;
      timer.reset();
    }

    if (!motorState[1]) {
      t_second_backward = 5;
      timer2.reset();
    }

    tmTmr = millis();
  }

  //  if (motorState[1] == 1) timer2.start();
  //  else timer2.reset();
}

void timerCallback() {
  if (motorState[0]) {
    t_second_forward -= 1;
    if (t_second_forward == 0) {
      motorState[0] = 0;
    }
  }
}

void timerCallback2() {
  if (motorState[1]) {
    t_second_backward -= 1;
    if (t_second_backward == 0) {
      motorState[1] = 0;
    }
  }
}

void FireTimer_Init()
{
  msTimer.begin(3000);

  dariNANOTimer.begin(3000);
  keNANOTimer.begin(3000);
  thingSpeakTmr.begin(20000);
}
