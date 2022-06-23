#define BTN_START 52
#define A_POSITIF 22
#define A_NEGATIF 23
#define B_POSITIF 24
#define B_NEGATIF 25
#define C_POSITIF 26
#define C_NEGATIF 27

#define LS_A0 30
#define LS_A1 31
#define LS_B0 32
#define LS_B1 33
#define LS_C0 34
#define LS_C1 35

uint8_t flagButton = 0;

uint8_t flagLS_A0 = 0;
uint8_t flagLS_A1 = 0;
uint8_t flagLS_B0 = 0;
uint8_t flagLS_B1 = 0;
uint8_t flagLS_C0 = 0;
uint8_t flagLS_C1 = 0;

void setup() {
  // inisiasi pin INPUT
  pinMode(BTN_START, INPUT);
  pinMode(LS_A0, INPUT);
  pinMode(LS_A1, INPUT);
  pinMode(LS_B0, INPUT);
  pinMode(LS_B1, INPUT);
  pinMode(LS_C0, INPUT);
  pinMode(LS_C1, INPUT);

  // inisiasi pin OUTPUT
  pinMode(A_POSITIF, OUTPUT);
  pinMode(A_NEGATIF, OUTPUT);
  pinMode(B_POSITIF, OUTPUT);
  pinMode(B_NEGATIF, OUTPUT);
  pinMode(C_POSITIF, OUTPUT);
  pinMode(C_NEGATIF, OUTPUT);
}
void loop() {
  if ((digitalRead(BTN_START) == HIGH) and (flagButton == 0)) {
    flagButton = 1;
  } else if ((digitalRead(BTN_START) == HIGH) and (flagButton == 1)) {
    flagButton = 0;
  }

  if (flagButton == 1) {
    if ((digitalRead(LS_A0) == HIGH) and (flagLS_A0 == 0)) {
      flagLS_A0 = 1;
    } else if ((digitalRead(LS_A0) == HIGH) and (flagLS_A0 == 1)) {
      flagLS_A0 = 0;
    }
    if ((digitalRead(LS_A1) == HIGH) and (flagLS_A1 == 0)) {
      flagLS_A1 = 1;
    } else if ((digitalRead(LS_A1) == HIGH) and (flagLS_A1 == 1)) {
      flagLS_A1 = 0;
    }
    if ((digitalRead(LS_B0) == HIGH) and (flagLS_B0 == 0)) {
      flagLS_B0 = 1;
    } else if ((digitalRead(LS_B0) == HIGH) and (flagLS_B0 == 1)) {
      flagLS_B0 = 0;
    }
    if ((digitalRead(LS_B1) == HIGH) and (flagLS_B1 == 0)) {
      flagLS_B1 = 1;
    } else if ((digitalRead(LS_B1) == HIGH) and (flagLS_B1 == 1)) {
      flagLS_B1 = 0;
    }
    if ((digitalRead(LS_C0) == HIGH) and (flagLS_C0 == 0)) {
      flagLS_C0 = 1;
    } else if ((digitalRead(LS_C0) == HIGH) and (flagLS_C0 == 1)) {
      flagLS_C0 = 0;
    }
    if ((digitalRead(LS_C1) == HIGH) and (flagLS_C1 == 0)) {
      flagLS_C1 = 1;
    } else if ((digitalRead(LS_C1) == HIGH) and (flagLS_C1 == 1)) {
      flagLS_C1 = 0;
    }

    if (flagLS_A0 == 1) {
      digitalWrite(A_POSITIF, HIGH);
      digitalWrite(A_NEGATIF, LOW);
      flagLS_A0 = 0;
    }
    if (flagLS_A1 == 1) {
      digitalWrite(A_POSITIF, LOW);
      digitalWrite(A_NEGATIF, HIGH);
      flagLS_A1 = 0;
    }

    if (digitalRead(A_POSITIF) == HIGH) {
      if (flagLS_B0 == 1) {
        digitalWrite(B_POSITIF, HIGH);
        digitalWrite(B_NEGATIF, LOW);
        flagLS_B0 = 0;
      }
      if (flagLS_B1 == 1) {
        digitalWrite(B_POSITIF, LOW);
        digitalWrite(B_NEGATIF, HIGH);
        flagLS_B1 = 0;
      }
    }

    if ((digitalRead(A_POSITIF) == LOW) and (digitalRead(B_POSITIF) == LOW)) {
      if (flagLS_C0 == 1) {
        digitalWrite(C_POSITIF, HIGH);
        digitalWrite(C_NEGATIF, LOW);
        flagLS_C0 = 0;
      }
      if (flagLS_C1 == 1) {
        digitalWrite(C_POSITIF, LOW);
        digitalWrite(C_NEGATIF, HIGH);
        flagLS_C1 = 0;
      }
    }
  } else if (flagButton == 0) {
    /* State awal sebelum tombol ditekan
       A_0, B_0, C_0 Aktif            */
    digitalWrite(A_POSITIF, LOW);
    digitalWrite(B_POSITIF, LOW);
    digitalWrite(C_POSITIF, LOW);

    digitalWrite(A_NEGATIF, HIGH);
    digitalWrite(B_NEGATIF, HIGH);
    digitalWrite(C_NEGATIF, HIGH);
  }


  delay(30);
}
