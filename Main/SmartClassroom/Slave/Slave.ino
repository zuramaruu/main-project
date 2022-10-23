#ifndef _DEBUG
#define _DEBUG
#endif

//#ifndef _RANDOMIZE
//#define _RANDOMIZE
//#endif

//#include "SerialTransfer.h"
//SerialTransfer Transfer2ESP32;
//SerialTransfer TransferFromESP32;

//#include <RBDdimmer.h>
#include "FireTimer.h"
#include "timer.h"

//#define outputPin  3
//#define zerocross  2 // for boards with CHANGEBLE input pins
//dimmerLamp dimmer(outputPin); //initialase port for dimmer for MEGA, Leonardo, UNO, Arduino M0, Arduino Zero

#define RELAY_1 A0 /* Pin Relay */
#define RELAY_2 A1
#define RELAY_3 A2

#define BUZZER  A6 /* Pin Indicator */

#define ENA     11 /* L298N */
#define IN1     12
#define IN2     13

#define RCWL    10 /* Pin RCWL-0156 */

FireTimer keESP32Timer, dariESP32Timer;

Timer timer;
Timer timer2;

uint16_t t_second_forward = 5;
uint16_t t_second_backward = 5;

void(*_ResetMode) (void) = 0; /* perintah reset */

String allString[2];
int relayState[3] = {0, 0, 0};
int motorState[2] = {0, 0};
int outVal = 0;
uint8_t FLAG = 0;

void setup() {
  Serial.begin(9600);
  FireTimer_Init();
  //  Transfer2ESP32.begin(Serial);
  //  SerialConfig();

  pinMode_Init();
  //  Dimmer_Init();
  timerInit();

  //  digitalWrite(RELAY_1, LOW);
  //  digitalWrite(RELAY_2, LOW);
  //  digitalWrite(RELAY_3, LOW);
}

void loop() {
  startPZEM();
  startMotion();

  keESP32();
  dariESP32();
  mainControl();
}
