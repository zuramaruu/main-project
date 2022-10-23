void ThinkSpeakInit() {
  ThingSpeak.begin(aclient);
  ThingSpeakb.begin(bclient);
  ThingSpeakc.begin(cclient);
}

void ThingSpeakHandler() {
  ThingSpeak.setField(1, voltage[0]);
  ThingSpeak.setField(2, current[0]);
  ThingSpeak.setField(3, power[0]);
  ThingSpeak.setField(4, energy[0]);

  ThingSpeakb.setField(1, voltage[1]);
  ThingSpeakb.setField(2, current[1]);
  ThingSpeakb.setField(3, power[1]);
  ThingSpeakb.setField(4, energy[1]);

  ThingSpeakc.setField(1, voltage[2]);
  ThingSpeakc.setField(2, current[2]);
  ThingSpeakc.setField(3, power[2]);
  ThingSpeakc.setField(4, energy[2]);

  ThingSpeak.setStatus(myStatus);
  ThingSpeakb.setStatus(BmyStatus);
  ThingSpeakc.setStatus(CmyStatus);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) Serial.println("Channel A update successful.");
  else Serial.println("Problem updating channel A. HTTP error code " + String(x));

  int y = ThingSpeakb.writeFields(BmyChannelNumber, BmyWriteAPIKey);
  if (y == 200) Serial.println("Channel B update successful.");
  else Serial.println("Problem updating channel B. HTTP error code " + String(y));

  int z = ThingSpeakc.writeFields(CmyChannelNumber, CmyWriteAPIKey);
  if (z == 200) Serial.println("Channel C update successful.");
  else Serial.println("Problem updating channel C. HTTP error code " + String(z));
}
