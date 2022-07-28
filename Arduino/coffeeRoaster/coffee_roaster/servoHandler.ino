#include <Servo_ESP32.h>
Servo_ESP32 servo1;

void Servo_Init() {
  servo1.attach(33);
  servo1.write(90);
}
void servoBuka() {
  servo1.write(0);
}

void servoTutup() {
  servo1.write(90);
}
