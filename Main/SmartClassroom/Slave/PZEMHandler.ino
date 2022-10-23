#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

#define PZEM_RX_PIN_A 4
#define PZEM_TX_PIN_A 5

#define PZEM_RX_PIN_B 6
#define PZEM_TX_PIN_B 7

#define PZEM_RX_PIN_C 8
#define PZEM_TX_PIN_C 9

SoftwareSerial pzemSWSerial1(PZEM_RX_PIN_A, PZEM_TX_PIN_A);
SoftwareSerial pzemSWSerial2(PZEM_RX_PIN_B, PZEM_TX_PIN_B);
SoftwareSerial pzemSWSerial3(PZEM_RX_PIN_C, PZEM_TX_PIN_C);

PZEM004Tv30 pzemA(pzemSWSerial1);
PZEM004Tv30 pzemB(pzemSWSerial2);
PZEM004Tv30 pzemC(pzemSWSerial3);

uint32_t pzemTmr;

void startPZEM() {
  if (millis() - pzemTmr >= 100) {

    allString[1] = "PZEM" + String("#") +
                   String(pzemA.voltage()) + "#" + String(pzemB.voltage()) + "#" + String(pzemC.voltage()) + "#" +
                   String(pzemA.current()) + "#" + String(pzemB.current()) + "#" + String(pzemC.current()) + "#" +
                   String(pzemA.power()) + "#" + String(pzemB.power()) + "#" + String(pzemC.power()) + "#" +
                   String(pzemA.energy()) + "#" + String(pzemB.energy()) + "#" + String(pzemC.energy()) + "#" +
                   String(pzemA.frequency()) + "#" + String(pzemB.frequency()) + "#" + String(pzemC.frequency()) + "#" +
                   String(pzemA.pf()) + "#" + String(pzemB.pf()) + "#" + String(pzemC.pf()) + "#";

#ifdef _RANDOMIZE
    allString[1] = "PZEM" + String("#") +
                   String(random(20, 100)) + "#" + String(random(20, 100)) + "#" + String(random(20, 100)) + "#" +
                   String(random(20, 100)) + "#" + String(random(20, 100)) + "#" + String(random(20, 100)) + "#" +
                   String(random(20, 100)) + "#" + String(random(20, 100)) + "#" + String(random(20, 100)) + "#" +
                   String(random(20, 100)) + "#" + String(random(20, 100)) + "#" + String(random(20, 100)) + "#" +
                   String(random(20, 100)) + "#" + String(random(20, 100)) + "#" + String(random(20, 100)) + "#" +
                   String(random(20, 100)) + "#" + String(random(20, 100)) + "#" + String(random(20, 100)) + "#";
#endif

#ifdef _DEBUG_PZEM

    Serial.print("PZEM-A: " + String(pzemA.voltage())  + " V \t"
                 + String(pzemA.current())  + " A \t"
                 + String(pzemA.power())    + " W \t"
                 + String(pzemA.energy())   + " kWH \t"
                 + String(pzemA.frequency())      + " Hz \t"
                 + String(pzemA.pf())       + "\n"   );
    Serial.print("PZEM-B: " + String(pzemB.voltage())  + " V \t"
                 + String(pzemB.current())  + " A \t"
                 + String(pzemB.power())    + " W \t"
                 + String(pzemB.energy())   + " kWH \t"
                 + String(pzemB.frequency())      + " Hz \t"
                 + String(pzemB.pf())       + "\n"   );
    Serial.print("PZEM-C: " + String(pzemC.voltage())  + " V \t"
                 + String(pzemC.current())  + " A \t"
                 + String(pzemC.power())    + " W \t"
                 + String(pzemC.energy())   + " kWH \t"
                 + String(pzemC.frequency())      + " Hz \t"
                 + String(pzemC.pf())       + "\n\n\n"   );

#endif

    pzemTmr = millis();
  }
}
