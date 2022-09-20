#define   R      14
#define   Y      27
#define   G      26
#define   B      25
#define   IN1    18
#define   IN2    19

uint32_t ledTmr;
uint8_t state = 1;
const byte pinL[6] = {R, Y, G, B, IN1, IN2};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 6; i++) {
    if (i < 4) pinMode(pinL[i], OUTPUT);
    else pinMode(pinL[i], INPUT);
  }
}

void loop() {

  if (millis() - ledTmr >= 180) {

    if (digitalRead(pinL[4])) {
      if (state == 2) state = 1;
      else state = 2;
    }

    if (digitalRead(pinL[5])) {
      if (state == 3) state = 4;
      else state = 3;
    }

    switch (state) {
      case 1: write(1); break;
      case 2: write(2); break;
      case 3: write(1, 3); break;
      case 4: write(2, 4); break;
    }

    ledTmr = millis();
  }

}

void write(int num) {
  for (int i = 0; i < 4; i++) {
    if (i == num - 1) digitalWrite(pinL[i], HIGH);
    else digitalWrite(pinL[i], LOW);
  }
}

void write(int num, int sec) {
  for (int i = 0; i < 4; i++) {
    if (i == num - 1 || i == sec - 1) {
      digitalWrite(pinL[i], HIGH);
    }
    else digitalWrite(pinL[i], LOW);
  }
}
