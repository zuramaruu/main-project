String dataIn;
float DataSatu, DataDua, DataTiga, DataEmpat, DataLima;
boolean parsing=false;

void setup(){
    Serial.begin(9600);
    dataIn="";
}

void loop(){
    if(Serial.available()>0){
        char inChar = (char)Serial.read();
        dataIn += inChar;
        if (inChar == '\n') {parsing = true;}
    }
    if(parsing){
        String dtTmpSatu, dtTmpDua, dtTmpTiga, dtTmpEmpat, dtTmpLima;
        dtTmpSatu = getValue(dataIn, "#", 0);
        dtTmpDua = getValue(dataIn, "#", 1);
        dtTmpTiga = getValue(dataIn, "#", 2);
        dtTmpEmpat = getValue(dataIn, "#", 3);
        dtTmpLima = getValue(dataIn, "#", 4);
        DataSatu = dtTmpSatu.toFloat();
        DataDua = dtTmpDua.toFloat();
        DataTiga = dtTmpTiga.toFloat();
        DataEmpat = dtTmpEmpat.toFloat();
        DataLima = dtTmpLima.toFloat();
        parsing = false;
        dataIn = "";
    };
    Serial.print("Data Satu : ");
    Serial.print(DataSatu);
    Serial.println();
    Serial.print("Data Dua : ");
    Serial.print(DataDua);
    Serial.println();
    Serial.print("Data Tiga : ");
    Serial.print(DataTiga);
    Serial.println();
    delay(1);
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