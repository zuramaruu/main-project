#ifndef _DEBUG
#define _DEBUG_RTC
#endif

#include <WiFi.h>
#include "ThingSpeak.h"

WiFiClient  aclient;
WiFiClient  bclient;
WiFiClient  cclient;

#define myChannelNumber 1863962
#define BmyChannelNumber 1864039
#define CmyChannelNumber 1864189
#define myWriteAPIKey "1M5HCOB84PVHEITS"
#define BmyWriteAPIKey "6MT7E196XEEYPOB3"
#define CmyWriteAPIKey "5GLW9KW1L0WP91PF"

String myStatus = "";
String BmyStatus = "";
String CmyStatus = "";

ThingSpeakClass ThingSpeakb;
ThingSpeakClass ThingSpeakc;

#include "FireTimer.h"
#include "timer.h"
Timer timer;

#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define API_KEY "AIzaSyCZWYrKd51Sa34_qqYhR0HBKXXK2MKlPO4"
#define DATABASE_URL "https://smartclassroom-5821a-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define USER_EMAIL "cobafirebase@gmail.com"
#define USER_PASSWORD "cobafirebase"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

uint16_t t_second_forward = 5;
uint16_t t_second_backward = 5;

FireTimer msTimer;
FireTimer dariNANOTimer, keNANOTimer, thingSpeakTmr;

#define RXp2 16
#define TXp2 17

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

TaskHandle_t SerialTask;

#define SSID_WIFI "KASTARA GROUP INDONESIA"
#define PASS_WIFI "KASTARA@2022"
#define DOMAIN "mydomain"

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
bool motorState[3] = {0, 0, 0};

uint8_t FLAG = 0;
uint8_t lcd_flg = 0;

int outVal = 0;

char customKey;

int indexes = 0;
String allString[3];

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
  FirebaseInit();
  RTOS_Init();
  ThinkSpeakInit();
  START_I2C_BUS();
  FireTimer_Init();
  timerInit();
}

void loop()
{
  //  koneksiWifiChecker();
  timer.update();
  bacaRTC();
  bacaBME();

  if (statusWifi == 1)
  {

  } else {

  }

  LCD_mainMenu();
  bacaKeypad();

  delay(30);
}
void SerialTask_callback( void * pvParameters ) {
  Serial.print("SerialTask Init on core ");
  Serial.println(xPortGetCoreID());
  delay(500);

  for (;;) {
    if (dariNANOTimer.fire()) dariNANO();
    //    if (keNANOTimer.fire()) keNANO();
    if (Firebase.ready() and msTimer.fire()) FirebaseHandler();
    if (thingSpeakTmr.fire()) ThingSpeakHandler();

    vTaskDelay( 20 / portTICK_PERIOD_MS );
  }
}
