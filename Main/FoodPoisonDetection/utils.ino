double regress(double x) {
  double terms[] = {
    -8.9350380868172977e+001,
    8.3001052233658505e+000,
    -2.3565580107732514e-001,
    2.1978231349853786e-003
  };

  double t = 1;
  double r = 0;
  for (double c : terms) {
    r += c * t;
    t *= x;
  }
  return r;
}

double regress_(double x) {
  double terms[] = {
    -8.8346329082757824e-001,
    8.7505270872137431e-001,
    8.4219463691464127e-003,
    -1.1364262909187352e-005
  };

  double t = 1;
  double r = 0;
  for (double c : terms) {
    r += c * t;
    t *= x;
  }
  return r;
}
