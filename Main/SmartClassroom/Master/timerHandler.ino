void timerInit() {
  timer.setInterval(1000);
  timer.setCallback(timerCallback);
  timer.start();
}

void timerCallback() {
  if (motorState[0] == 1) {
    t_second_forward -= 1;
    if (t_second_forward == 0) {
      motorState[0] = 0;
    }
  } else {
    t_second_forward = 5;
  }

  if (motorState[1] == 1) {
    t_second_backward -= 1;
    if (t_second_backward == 0) {
      motorState[1] = 0;
    }
  } else {
    t_second_backward = 5;
  }
}
