//#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include "PID_Kontrol.h"

#ifndef _DEBUG
#define _DEBUG
#endif

TaskHandle_t FireBase_task;

/*--------- FIRE BASE DATA OBJECT ---------*/
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define WIFI_SSID "KASTARA GROUP INDONESIA"
#define WIFI_PASSWORD "KASTARA@2022"
//#define WIFI_SSID "HUMANOID-COM"
//#define WIFI_PASSWORD "bismillah"
//#define WIFI_SSID "bobo ciang"
//#define WIFI_PASSWORD "pengenjajan"
#define API_KEY "AIzaSyDM16GhJdX3xRcSPJrPfNChROCKIEFsYZg"
#define DATABASE_URL "https://coffeeroaster-4bdb0-default-rtdb.firebaseio.com/"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

/*--------- Timer OBJECT ---------*/
#include "timer.h"
Timer timer;
uint16_t t_second = 0;
uint16_t t_minute = 0;

/*--------- SERVO OBJECT ---------*/
#include <Servo_ESP32.h>
Servo_ESP32 servo1;

/*--------- TCS OBJECT ---------*/
#include <tcs3200.h>    // Include TCS3200 library 
#define s_0 25
#define s_1 26
#define s_2 18
#define s_3 5
#define out_pin 27
#define num_of_colors 3
int distinctRGB[num_of_colors][3] = {{18, 10, 11}, {25, 11, 12}, {10, 7, 9}};
String distinctColors[num_of_colors] = {"light", "brown", "dark"};
int red, green, blue;
tcs3200 tcs(s_0, s_1, s_2, s_3, out_pin); // (S0, S1, S2, S3, output pin)
String tcs_color;

/*--------- MAX31865 OBJECT ---------*/
#include <Adafruit_MAX31865.h>
Adafruit_MAX31865 thermo = Adafruit_MAX31865(15, 13, 12, 14); // CS, DI, DO, CLK
#define RREF      430.0 // The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RNOMINAL  100.0 // 100.0 for PT100, 1000.0 for PT1000
float ratio;
float max31865_temperature;
float max31865_resistance;
float suhu = 0.0;

/*--------- PID Control ---------*/
int kp = 90;   int ki = 30;   int kd = 200;
//float set_temperature = 0;
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
float PID_value = 0;
int PID_p = 0;    int PID_i = 0;    int PID_d = 0;
int SP;      /* -- SetPoint Suhu -- */
int SP_Time; /* -- Time Sampling -- */
float out = 0;

/*--------- Button Pin ---------*/
uint8_t buttonPin[4] = {34, 35, 36, 39};
uint8_t relay[2] = {4, 2};

String st_btn_color[4] = {"0", "0", "0", "0"};
String st_btn[4] = {"0", "0", "0", "0"};
String st_btn_emergency = "0";

uint8_t _reset = 0, _reset_btn_manual = 0;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
int u_time = 0;
byte time_state = false;
void setup() {
  Serial.begin(115200);
  RTOS_Init();
  relay_Init();
  Servo_Init();
  //pinMode(INPUT_PULLUP,buttonA);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  /* TIMER OBJECT */
  timer.setInterval(1000);
  timer.setCallback(timerCallback);
  timer.start();

  GPIO_Init();
  LCD_Init();
  max31865_Init();
  Tcs3200_Init();
  //  servo_PID.setSampling(10, 10);
  //  servo_PID.mulai();
}

void loop()
{
  timer.update();
  /* Polynomial Regression */
  max31865_Begin();
  suhu = getTemperatureMax31865();
  suhu = -6.1423382062643057 + (0.92142277067818967 * suhu) + 4.0;
  //  suhu += 1;
  //  suhu = random(80, 100);

  //  if (digitalRead(buttonPin[2])) relaySatuOn();
  //  else relaySatuOff();
  //  if (digitalRead(buttonPin[3])) relayDuaOn();
  //  else relayDuaOff();

  if ((st_btn[0] == "1") and (st_btn[1] == "1")) {
    relaySatuOn();
    manualStateOn();
  }
  if ((st_btn[0] == "0") and (st_btn[1] == "0") and
                       (st_btn_color[0] == "0") and (st_btn_color[1] == "0") and
                       (st_btn_color[2] == "0")) {
    relaySatuOff();
  }
  if ((st_btn[2] == "1") and (st_btn[3] == "1")) {
    relayDuaOn();
  }
  if ((st_btn[2] == "0") and (st_btn[3] == "0")) {
    relayDuaOff();
  }

  //  LoopTest_Relay();

  Serial.println("Suhu = " + String(suhu) + " C");
  //  Serial.println("Warna = " + tcs3200getColor());

  Serial.println("st_btn 1 = " + st_btn[0]);
  Serial.println("st_btn 2 = " + st_btn[1]);
  Serial.println("st_btn 3 = " + st_btn[2]);
  Serial.println("st_btn 4 = " + st_btn[3]);

  LCD_Print();

  if (st_btn_color[0] == "1") {
    timerStart();
    relaySatuOn();
    lightButton_isPressed();
    PID_Control(SP, suhu);
    servoHeater(int(out));
    Serial.println("/* --- Light State --- */");
    PID_readStatus();
  }

  if (st_btn_color[1] == "1") {
    timerStart();
    relaySatuOn();
    brownButton_isPressed();
    PID_Control(SP, suhu);
    servoHeater(int(out));
    Serial.println("/* --- Brown State --- */");
    PID_readStatus();
  }

  if (st_btn_color[2] == "1") {
    timerStart();
    relaySatuOn();
    darkButton_isPressed();
    PID_Control(SP, suhu);
    servoHeater(int(out));
    Serial.println("/* --- Dark State --- */");
    PID_readStatus();
  }

  if ((st_btn_color[0] == "0") and
      (st_btn_color[1] == "0") and
      (st_btn_color[2] == "0") and
      (st_btn[0] == "0") and (st_btn[1] == "0"))
  {
    timerStop();
    timerReset();
    t_second = 0;
    servoTutup();
    relaySatuOff();
  }

  //    servo_PID.kalkulasi(suhu);
  //    Out += servo_PID.getOutput();
  //    if (Out < 1) Out = 0;
  delay(500);
}
void FireBase_taskCallback( void * pvParameters ) {
  Serial.print("FireBase Init on core ");
  Serial.println(xPortGetCoreID());
  delay(500);

  for (;;) {
    if (millis() - u_time >= 3000) {
      u_time = millis();
      kirimDataFireBase();
      BacaButtonFireBase();
    }
    vTaskDelay( 20 / portTICK_PERIOD_MS );
  }
}
