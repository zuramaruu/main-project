String parseStr(String data, char separator[], int index)
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

void SerialParseIn() {
  if (millis() - sysTmr >= 10) {

    if (Serial.available() > 1) {
      String read[3];
      read[0] = Serial.readString();
      read[1] = parseStr(read[0], "#", 0);
      if (read[1] == "photo") {
        read[2] = parseStr(read[0], "#", 1);
        if (read[2].toInt() == 1) new_image = true;
      }
    }

    sysTmr = millis();
  }
}
