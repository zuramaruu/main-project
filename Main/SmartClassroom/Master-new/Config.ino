void RTOS_Init() {
  xTaskCreatePinnedToCore(
    SerialTask_callback,   /* Task function. */
    "SerialTask",     /* name of task. */
    20000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &SerialTask,      /* Task handle to keep track of created task */
    1);       /* pin task to core 0 */
}

String parseString(String data, char separator[], int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator[0] || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void hitungTotal() {
  if (millis() - pzmTmr >= 1000) {
    pzmTmr = millis();

    //    totalHarga[0] += energy[0];
    //    totalHarga[0] = totalHarga[0] * 3.6;
    //
    //    totalHarga[1] += energy[1];
    //    totalHarga[1] = totalHarga[1] * 3.6;
    //
    //    totalHarga[2] += energy[2];
    //    totalHarga[2] = totalHarga[2] * 3.6;
    totalHarga[0] = random(5000, 9999);
    totalHarga[1] = random(5000, 9999);
    totalHarga[2] = random(5000, 9999);
  }
}


//void serialSend() {
//  if ( Serial.available() > 1 ) {
//    String Read =  Serial.readString();
//    String _read = parseString(Read, "#", 0);
//    if (_read == "t") {
//      String __read = parseString(Read, "#", 1);
//      callback_key = String(__read);
//    }
//  }
//}
