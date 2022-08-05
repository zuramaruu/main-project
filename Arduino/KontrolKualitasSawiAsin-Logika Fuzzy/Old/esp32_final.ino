#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "BINTANG_HOME";
const char WIFI_PASSWORD[] = "bintangku";

String HOST_NAME = "http://192.168.1.10/"; // change to your PC's IP address
String PATH_NAME   = "/post_data.php";

//-- Parse String --//
String dataIn;
boolean parsing=false;
String temperatureSatu, temperatureDua, phValueSatu, phValueDua, fuzzySalinity;

void setup() {
  Serial.begin(9600); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // -- Data Masuk -- //
    dataIn="";
}

void loop() {
//  int randomValue = random(9999);
//  int randomHour = random(0,23);
//  int randomMinute = random(0,59);
//  int randomDay = random(1,31);
//  int randomMonth = random(1,12);

//    String queryString = String("?data=A&date=")+
//                         String(randomDay)+
//                         String("%2F")+
//                         String(randomMonth)+
//                         String("%2F2022&time=")+
//                         String(randomHour)+
//                         String(".")+
//                         String(randomMinute)+
//                         String("&value=")+
//                         String(randomValue);

    if(Serial.available()>0){
        char inChar = (char)Serial.read();
        dataIn += inChar;
        if (inChar == '\n') {parsing = true;}
    }
    if(parsing){
        temperatureSatu = getValue(dataIn, "#", 0);
        temperatureDua = getValue(dataIn, "#", 1);
        phValueSatu = getValue(dataIn, "#", 2);
        phValueDua = getValue(dataIn, "#", 3);
        fuzzySalinity = getValue(dataIn, "#", 4);

        //-- Empty the Serial --//
        parsing = false;
        dataIn = "";
    }
  String queryString = String("?data=A&date=")+
          String(temperatureSatu)+
          String("%2F")+
          String(temperatureDua)+
          String("%2F2022&time=")+
          String(phValueSatu)+
          String(".")+
          String(phValueDua)+
          String("&value=")+
          String(fuzzySalinity);

  HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME + queryString); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
//  delay(5000); //-- Optional
}
String getValue(String data, char separator[], int index){
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
