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

void serialSend() {
  if ( Serial.available() > 1 ) {
    String Read =  Serial.readString(); //t#33#1.80#3.30
    read1 = parseString(Read, "#", 0);
    if (read1 == "p1") { // suhu
      read2 = parseString(Read, "#", 1);
      callback_ph_satu = read2.toFloat();
      //      Firebase.setIntAsync(fbdo, "/temperature", callback_temp);
    }
    else if (read1 == "p2") {
      read2 = parseString(Read, "#", 1);
      callback_ph_dua = read2.toFloat();
    }
    else if (read1 == "p3") {
      read2 = parseString(Read, "#", 1);
      callback_ph_tiga = read2.toFloat();
      //      Firebase.setIntAsync(fbdo, "/kelembapan", callback_hum);
    }
//    else if (read1 == "a") {
//      read2 = parseString(Read, "#", 1);
//      callback_arusAki = read2.toFloat();
//      //      Firebase.setFloatAsync(fbdo, "/arusAki", callback_arusAki);
//    }
//    else if (read1 == "d") {
//      read2 = parseString(Read, "#", 1);
//      callback_dayaAki = read2.toInt();
//      //      Firebase.setIntAsync(fbdo, "/dayaAki", callback_dayaAki);
//    }
//    else if (read1 == "x") {
//      read2 = parseString(Read, "#", 1);
//      callback_solar = read2.toInt();
//      //      Firebase.setIntAsync(fbdo, "/teganganSolarcell", callback_solar);
//    }
  }
}
