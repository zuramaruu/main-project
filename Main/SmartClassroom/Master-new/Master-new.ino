#ifndef _DEBUG
#define _DEBUG
#endif

#include <WiFi.h>
#include <HTTPClient.h>
#include <RBDdimmer.h>

#include "FireTimer.h"
#include "timer.h"
Timer timer;
Timer timer2;

#define outputPin  27
#define zerocross  33

dimmerLamp dimmer(outputPin, zerocross);

uint16_t t_second_forward = 5;
uint16_t t_second_backward = 5;

FireTimer msTimer;
FireTimer dariNANOTimer, keNANOTimer, thingSpeakTmr;

#define RXp2 16
#define TXp2 17

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

TaskHandle_t SerialTask;

//#define SSID_WIFI "KASTARA GROUP INDONESIA"
//#define PASS_WIFI "KASTARA@2022"
#define SSID_WIFI "nakama"
#define PASS_WIFI "Tu46gPZh"
#define DOMAIN "https://www.imakeofficial.com/project/2022/1"

uint8_t statusWifi = 0;

#define RELAY_1 13 /* Pin Relay */
#define RELAY_2 12
#define RELAY_3 14
#define RELAY_4 27

float bme_val[2] = {0.0, 0.0};

int YYMMDD[3] = {0, 0, 0};
int HHMMMSS[3] = {0, 0, 0};
String day = "";
String days_now = "";

float voltage[3] = {0.0, 0.0, 0.0};
float current[3] = {0.0, 0.0, 0.0};
float power[3] = {0.0, 0.0, 0.0};
float energy[3] = {0.0, 0.0, 0.0};
int stateRelay[4] = {0, 0, 0, 0};
uint8_t motorState[3] = {0, 0, 0};
float totalHarga[3] = {0, 0, 0};
uint32_t pzmTmr;

uint8_t FLAG = 0;
uint8_t lcd_flg = 0;

int outVal = 0;

char customKey;

int indexes = 0;
String allString[3];
uint32_t wifiTmr;

enum KeyMode {MenuMode,
              MonitoringMode,
              TempMode,
              MainControl,
              ExtrasMode,
              ResetMode
             };

enum ctrlMode {CtrlMenuCondition,
               RelayCondition,
               LampCondition,
               MotorCondition
              };

enum PZEMMode {PZEMMenu,
               PZEMA,
               PZEMB,
               PZEMC
              };

byte _ctrlMode = CtrlMenuCondition;
byte _mode = MenuMode;
byte _PZEMMode = PZEMMenu;

void setup()
{
  //  RelayInit();
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  WIFI_INIT();
  //  FirebaseInit();
  RTOS_Init();
  //  ThinkSpeakInit();
  START_I2C_BUS();
  FireTimer_Init();
  timerInit();
  dimmer.begin(NORMAL_MODE, ON);
}

void loop()
{

  bacaRTC();
  bacaBME();
  timerCtrl();

  LCD_mainMenu();
  bacaKeypad();

  if (outVal < 5) dimmer.setState(OFF);
  else {
    dimmer.setState(ON);
    dimmer.setPower(int(map(outVal, 0, 100, 0, 25)));
  }

  //  Serial.println("getState(r1) = " + String(getState("r1")));
  //  Serial.println("getState(r2) = " + String(getState("r2")));
  //  Serial.println("getState(r3) = " + String(getState("r3")));
  //  Serial.println("getState(ldimmer) = " + String(getState("ldimmer")));
  //  Serial.println("getState(rmotor) = " + String(getState("rmotor")));
  //  Serial.println("motorState[0] = " + String(motorState[0]));
  //  Serial.println("motorState[1] = " + String(motorState[1]));
  //  Serial.println("Suhu = " + String(bme_val[0]));
  //  Serial.println("Kelembapan = " + String(bme_val[1]));
  //  Serial.println("statusWifi = " + String(statusWifi));
  //  Serial.println("readSuhu() = " + String(readSuhu()));
  //  Serial.println("getState(r1) = " + String(stateRelay[0]));
  //  Serial.println("getState(r2) = " + String(stateRelay[1]));
  //  Serial.println("getState(r3) = " + String(stateRelay[2]));

  timer2.update();
  timer.update();
  delay(30);
}

void SerialTask_callback( void * pvParameters ) {
  Serial.print("SerialTask Init on core ");
  Serial.println(xPortGetCoreID());
  delay(500);

  for (;;) {
    if (dariNANOTimer.fire()) dariNANO();
    if (keNANOTimer.fire()) keNANO();

    //    hitungTotal();
    if (statusWifi) checkIsNanAndSend();
    if (statusWifi) readRelayState();

    if (millis() - wifiTmr >= 5000) {
      koneksiWifiChecker();

      wifiTmr = millis();
    }

    vTaskDelay( 20 / portTICK_PERIOD_MS );
  }
}
