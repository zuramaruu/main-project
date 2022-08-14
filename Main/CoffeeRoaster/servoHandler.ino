void Servo_Init() {
  servo1.attach(33);
  servo1.write(180);
  //  servoBuka();
}
void servoBuka() {
  servo1.write(0);
}
void servoTutup() {
  servo1.write(180);
}
void servoHeater(int _input) {
  servo1.write(150 - _input);
}
void servoManual() {
  servo1.write(0);
}
