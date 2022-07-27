ke#define DEBUG 0
void setup() {
  Serial.begin(9600);
  PompaExt_Init();
  Relay_Init();
  Dht_Init();
  ph_Init();
}

void loop() {
  //  LoopTest_Pompa();
  //  LoopTest_Relay();
  bacaTemperature();
  bacaKelembapan();
  bacaMoisture();
  bacaPh();
  Control_PompaExt(1, 1);
  Control_PompaExt(2, 1);
  Control_PompaExt(3, 1);
  Control_PompaExt(4, 1);
  Control_PompaExt(5, 1);
  Control_PompaExt(6, 1);
}
