String dataIn;
String dt[10];
int i;
boolean parsing=false;
 
void setup(){
    Serial.begin(9600);
    dataIn="";
}
 
void loop(){
//     if(Serial.available()>0){
//           char inChar = (char)Serial.read();
//           dataIn += inChar;
//           if (inChar == '\n') {parsing = true;}
//     }
//     if(parsing){
//           parsingData();
//           parsing=false;
//           dataIn="";
//     }

      //-- String getValue Once;
      String DataSatu, DataDua;
     if(Serial.available()>0){
        char inChar = (char)Serial.read();
        dataIn += inChar;
        if (inChar == '\n') {parsing = true;}
     }
     if(parsing){
      //      Serial.print(dataIn);
      DataSatu = getValue(dataIn, "#", 0);
      DataDua = getValue(dataIn, "#", 1);
      Serial.print("Data 1 : ");
      Serial.print(DataSatu);
      Serial.print("\n");
      Serial.print("Data 2 : ");
      Serial.print(DataDua);
      Serial.print("\n");
      parsing = false;
      dataIn = "";
      };
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

 
void parsingData(){
      int j=0;
      //kirim data yang telah diterima sebelumnya
      Serial.print("data masuk : ");
      Serial.print(dataIn);
      Serial.print("\n");
      //inisialisasi variabel, (reset isi variabel)
      dt[j]="";
      //proses parsing data
      for(i=1;i<dataIn.length();i++){
             //pengecekan tiap karakter dengan karakter (#) dan (,)
             if ((dataIn[i] == '#') || (dataIn[i] == ',')){
                   //increment variabel j, digunakan untuk merubah index array penampung
                   j++;
                  dt[j]=""; //inisialisasi variabel array dt[j]
             }
             else{
                  //proses tampung data saat pengecekan karakter selesai.
                  dt[j] = dt[j] + dataIn[i];
             }
      }
      Serial.print("data 1 : ");
      Serial.print(dt[0]);
      Serial.print("\n");
      Serial.print("data 2 : ");
      Serial.print(dt[1].toInt());
      Serial.print("\n");
      Serial.print("data 3 : ");
      Serial.print(dt[2].toInt());
      Serial.print("\n");
      Serial.print("data 4 : ");
      Serial.print(dt[3].toInt());
      Serial.print("\n");
      Serial.print("data 5 : ");
      Serial.print(dt[4].toInt());
      Serial.print("\n\n");
}
