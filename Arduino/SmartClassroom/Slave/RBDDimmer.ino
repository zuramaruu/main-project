void Dimmer_Init() {
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE)
}
void dimmerSet(int _out_val) {
  dimmer.setPower(_out_val); // name.setPower(0%-100%)
}
