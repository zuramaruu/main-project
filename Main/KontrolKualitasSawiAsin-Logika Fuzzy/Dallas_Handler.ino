void Suhu_Init(DeviceAddress deviceAddress) {
  sensors.begin();
  sensors.setResolution(insideThermometer, 9);

  getSuhu[0] = sensors.getTempC(deviceAddress);
  if (getSuhu[0] == DEVICE_DISCONNECTED_C)
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
}

void Suhu_GetTemp() {
  //  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  printTemperature(insideThermometer);
}

void printTemperature(DeviceAddress deviceAddress)
{
  // method 2 - faster
  getSuhu[0] = sensors.getTempC(deviceAddress);
  if (  getSuhu[0] == DEVICE_DISCONNECTED_C)
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
}
