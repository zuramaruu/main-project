void keESP32() {
  if (keESP32Timer.fire())
  {
    //    char data[500];
    String dataSend = allString[0] + allString[1];
    //    dataSend.toCharArray(data, dataSend.length() + 1);
    Serial.print(dataSend);

    //    Serial.println();
    //    Serial.println(" Time 1 ="  + String(t_second_forward) + " Time 2 =" + String(t_second_backward) + "++");
  }
}
void dariESP32() {
  if (dariESP32Timer.fire()) {
    if (Serial.available()) {
      String _read = Serial.readString();

      String forward_state = parseString(_read, "#", 1);
      String backward_state = parseString(_read, "#", 2);
      String dimmer_out = parseString(_read, "#", 4);

      motorState[0] = forward_state.toInt();
      motorState[1] = backward_state.toInt();
      outVal = dimmer_out.toInt();

      //      Serial.println();
      //      Serial.println("||" + String(motorState[0]) + "||" + String(motorState[1]) + "||" + String(outVal) + "||");
    }
  }
}


//void keESP32()
//{
//  uint16_t sendSize = 0;
//  char data[500];
//
//  String dataSend = allString[0] + allString[1];
//  dataSend.toCharArray(data, dataSend.length() + 1);
//  ///////////////////////////////////////// Stuff buffer with struct
//  sendSize = Transfer2ESP32.txObj(data, sendSize);
//  ///////////////////////////////////////// Stuff buffer with array
//  Transfer2ESP32.sendData(sendSize);
//}
//
///////////////////////////////////////////////////////////////////// Callbacks
//void dariESP32()
//{
//  Serial.println("hi");
//}
//
//// supplied as a reference - persistent allocation required
//const functionPtr callbackArr[] = { dariESP32 };
/////////////////////////////////////////////////////////////////////
//
//
//void SerialConfig()
//{
//  ///////////////////////////////////////////////////////////////// Config Parameters
//  configST myConfig;
//  myConfig.debug        = true;
//  myConfig.callbacks    = callbackArr;
//  myConfig.callbacksLen = sizeof(callbackArr) / sizeof(functionPtr);
//  /////////////////////////////////////////////////////////////////
//
//  TransferFromESP32.begin(Serial, myConfig);
//}
//
//
//void SerialStart()
//{
//  TransferFromESP32.tick();
//}
