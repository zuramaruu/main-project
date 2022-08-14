void dariNANO()
{
  if (Serial2.available())
  {
    String _read = Serial2.readString();
    String RCWL_FLAG = parseString(_read, "#", 1);

    String voltage_1 = parseString(_read, "#", 3);
    String voltage_2 = parseString(_read, "#", 4);
    String voltage_3 = parseString(_read, "#", 5);

    String current_1 = parseString(_read, "#", 6);
    String current_2 = parseString(_read, "#", 7);
    String current_3 = parseString(_read, "#", 8);

    String power_1 = parseString(_read, "#", 9);
    String power_2 = parseString(_read, "#", 10);
    String power_3 = parseString(_read, "#", 11);

    String energy_1 = parseString(_read, "#", 12);
    String energy_2 = parseString(_read, "#", 13);
    String energy_3 = parseString(_read, "#", 14);

    FLAG = RCWL_FLAG.toInt();

    voltage[0] = voltage_1.toFloat();
    voltage[1] = voltage_2.toFloat();
    voltage[2] = voltage_3.toFloat();

    current[0] = current_1.toFloat();
    current[1] = current_2.toFloat();
    current[2] = current_3.toFloat();

    power[0] = power_1.toFloat();
    power[1] = power_2.toFloat();
    power[2] = power_3.toFloat();

    energy[0] = energy_1.toFloat();
    energy[1] = energy_2.toFloat();
    energy[2] = energy_3.toFloat();
  }
}

void keNANO() {
  if (statusWifi == 1)
  {

  } else
  {
    allString[0] = "STMOTOR#" + String(motorState[0]) + "#" + String(motorState[1]) + "#";
    allString[1] = "DIMMER#" + String(outVal) + "#";
    String dataSend = allString[0] + allString[1];
    Serial2.print(dataSend);
  }
}



//#include "SerialTransfer.h"
//
//SerialTransfer myTransfer;
//void keNANO()
//{
//
//}
//
///////////////////////////////////////////////////////////////////// Callbacks
//void dariNANO()
//{
//  Serial.println("hi");
//}
//
//// supplied as a reference - persistent allocation required
//const functionPtr callbackArr[] = { dariNANO };
/////////////////////////////////////////////////////////////////////
//
//
//void SerialConfig()
//{
//  Serial1.begin(9600);
//
//  ///////////////////////////////////////////////////////////////// Config Parameters
//  configST myConfig;
//  myConfig.debug        = false;
//  myConfig.callbacks    = callbackArr;
//  myConfig.callbacksLen = sizeof(callbackArr) / sizeof(functionPtr);
//  /////////////////////////////////////////////////////////////////
//
//  myTransfer.begin(Serial1, myConfig);
//}
//
//
//void SerialStart()
//{
//  myTransfer.tick();
//}
