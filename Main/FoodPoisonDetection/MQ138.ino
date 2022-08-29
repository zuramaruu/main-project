#define Pin_MQ138 (A1)

void MQ138_Init() {
  pinMode(Pin_MQ138, INPUT);
}

int getMQ138Val() {
  return analogRead(Pin_MQ138);
}
