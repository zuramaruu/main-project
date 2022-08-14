#include <Adafruit_Fingerprint.h>


#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial mySerial(2, 3);
#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white
#define mySerial Serial2
#endif


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;


uint8_t pinMHSensor[2] = {25, 26};

int mh_analog_val = 0;
bool mh_digital_val = true;

void setup()
{
  Serial.begin(115200);
  Serial.println("INITIALIZE");
  //  rfid_Init();
  //  Servo_Init();
  //  mhSensor_Init();
  //  lcd_Init();
  FingerPrint_Init();
  ValidationFingerInit();
}

void loop()
{
  //  mhSensor_Test();
  //  testServo();
  //  bacaKeypad();
  //  bacaRfid();
  //  Serial.println("Coba");

  //  Serial.println("Ready to enroll a fingerprint!");
  //  Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
  //  id = readnumber();
  //  if (id == 0) {// ID #0 not allowed, try again!
  //    return;
  //  }
  //  Serial.print("Enrolling ID #");
  //  Serial.println(id);
  //
  //  while (!  getFingerprintEnroll() );
  getFingerprintID();
  //  deleteFingerprint(id);
}
