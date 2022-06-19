#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <L298N.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define ONE_WIRE_BUS 2
#define ONE_WIRE_BUS2 3



//-- Sensor Suhu --//
OneWire oneWire(ONE_WIRE_BUS);
OneWire oneWire2(ONE_WIRE_BUS2);
DallasTemperature sensors(&oneWire);
DallasTemperature sensors2(&oneWire2);
DeviceAddress insideThermometer;
DeviceAddress insideThermometer2;
float temperature_1, temperature_2;

//-- PH sensor --//
float calibration_value = 21.34 + 4.0;
float ph_val1, ph_val2;
unsigned long int avgval;
unsigned long int avgval2;
int buffer_arr[10], temp;
int buffer_arr2[10], temp2;
int PhPin = A2;
int PhPin2 = A3;

//-- Salinity sensor with Fuzzy Logic --//
float salinitasSatu, salinitasDua;
float uRendahSalSatu, uSedangSalSatu, uTinggiSalSatu;
float uRendahSalDua, uSedangSalDua, uTinggiSalDua;

int AnalogInPin = A0, AnalogInPin2 = A1;

float minr[9];
float Rule[9];

float redup = 1;
float normal = 128;
float terang = 255;

//-- L289N --//
int IN_1 = 4;
int IN_2 = 5;

int processTime[3] = {0, 0, 0};

unsigned char salinitasRendah1(){
    if (salinitasSatu <= 200.46){ uRendahSalSatu =1;}
    else if (salinitasSatu >= 200.46 && salinitasSatu <= 300.69){ uRendahSalSatu= (300.69 - salinitasSatu) / (300.69 - 200.46);}
    else if (salinitasSatu >= 300.69){ uRendahSalSatu =0;}
    return uRendahSalSatu;
}
unsigned char salinitasSedang1(){
    if (salinitasSatu <= 200.46){ uSedangSalSatu =0;}
    else if (salinitasSatu >= 200.46 && salinitasSatu <= 300.69){ uSedangSalSatu= (salinitasSatu - 200.46) / (300.69 - 200.46);}
    else if (salinitasSatu >= 300.69 && salinitasSatu <= 510.5){ uSedangSalSatu= (510.5 - salinitasSatu) / (510.5 - 300.69);}
    else if (salinitasSatu >= 510.5){ uSedangSalSatu =0;}
    return uSedangSalSatu;
}
unsigned char salinitasTinggi1() {
    if (salinitasSatu <= 300.69) { uTinggiSalSatu = 0; }
    else if (salinitasSatu >= 300.69 && salinitasSatu <= 510.5) { uTinggiSalSatu = (salinitasSatu - 300.69) / (510.5 - 300.69); }
    else if (salinitasSatu >= 510.5) { uTinggiSalSatu = 1; }
    return uTinggiSalSatu;
}

unsigned char salinitasRendah2(){
    if (salinitasDua <= 200.46){ uRendahSalDua =1;}
    else if (salinitasDua >= 200.46 && salinitasDua <= 300.69){ uRendahSalDua= (300.69 - salinitasDua) / (300.69 - 200.46);}
    else if (salinitasDua >= 300.69){ uRendahSalDua =0;}
    return uRendahSalDua;
}
unsigned char salinitasSedang2(){
    if (salinitasDua <= 200.46){ uSedangSalDua =0;}
    else if (salinitasDua >= 200.46 && salinitasDua <= 300.69){ uSedangSalDua= (salinitasDua - 200.46) / (300.69 - 200.46);}
    else if (salinitasDua >= 300.69 && salinitasDua <= 510.5){ uSedangSalDua= (510.5 - salinitasDua) / (510.5 - 300.69);}
    else if (salinitasDua >= 510.5){ uSedangSalDua =0;}
    return uSedangSalDua;
}
unsigned char salinitasTinggi2() {
    if (salinitasDua <= 300.69) { uTinggiSalDua = 0; }
    else if (salinitasDua >= 300.69 && salinitasDua <= 510.5) { uTinggiSalDua = (salinitasDua - 300.69) / (510.5 - 300.69); }
    else if (salinitasDua >= 510.5) { uTinggiSalDua = 1; }
    return uTinggiSalDua;
}

void fuzzifikasi(){
    salinitasRendah1();
    salinitasSedang1();
    salinitasTinggi1();
    salinitasRendah2();
    salinitasSedang2();
    salinitasTinggi2();
}

float Min(float a, float b){
    if (a < b){
        return a;
    }
    else if (b < a){
        return b;
    }
    else{
        return a;
    }
}
void rule()
{
    fuzzifikasi();

    minr[1] = Min(uRendahSalSatu, uRendahSalDua);
    Rule[1] = redup;
    minr[2] = Min(uRendahSalSatu, uSedangSalDua);
    Rule[2] = normal;
    minr[3] = Min(uRendahSalSatu, uTinggiSalDua);
    Rule[3] = terang;
    minr[4] = Min(uSedangSalSatu, uRendahSalDua);
    Rule[4] = redup;
    minr[5] = Min(uSedangSalSatu, uSedangSalDua);
    Rule[5] = normal;
    minr[6] = Min(uSedangSalSatu, uTinggiSalDua);
    Rule[6] = terang;
    minr[7] = Min(uTinggiSalSatu, uRendahSalDua);
    Rule[7] = redup;
    minr[8] = Min(uTinggiSalSatu, uSedangSalDua);
    Rule[8] = normal;
    minr[9] = Min(uTinggiSalSatu, uTinggiSalDua);
    Rule[9] = terang;
}

float A, B;
float defuzzyfikasi()
{
    rule();
    A = 0;
    B = 0;

    for (int i = 1; i <= 9; i++)
    {
        // printf("Rule ke %d = %f\n", i, Rule[i]);
        // printf("Min ke %d = %f\n", i, minr[i]);
        A += Rule[i] * minr[i];
        B += minr[i];
    }
    // printf("Hasil A : %f\n", A);
    // printf("Hasil B : %f\n", B);
    return A / B;
}
float getPh(int SensorPin, float cal_value, unsigned long int avg_value, int temp_value, int buffer_arrFun[]){
    for(int i=0;i<10;i++){
        buffer_arrFun[i]=analogRead(SensorPin);
        delay(30);
    }
    for(int i=0;i<9;i++)
    {
        for(int j=i+1;j<10;j++)
        {
            if(buffer_arrFun[i]>buffer_arrFun[j])
            {
                temp_value=buffer_arrFun[i];
                buffer_arrFun[i]=buffer_arrFun[j];
                buffer_arrFun[j]=temp_value;
            }
        }
    }
    avg_value=0;
    for(int i=2;i<8;i++)
        avg_value+=buffer_arrFun[i];
    float volt=(float)avg_value*5.0/1024/6;
    float ph_act = -5.70 * volt + cal_value;
    return ph_act;
}
float getSalinity(int SensorPin){
    float Sal= analogRead(SensorPin);
    return Sal;
}
float getDallasTemperature(DallasTemperature _Sensors, DeviceAddress _deviceAddress){
    _Sensors.requestTemperatures();
    float tempC = _Sensors.getTempC(_deviceAddress);
    return tempC;
}

void setup() {
    Serial.begin(9600);
    sensors.begin();
    sensors2.begin();
    sensors.setResolution(insideThermometer, 9);
    sensors2.setResolution(insideThermometer2, 9);
//    printAddress(insideThermometer);
//    printAddress(insideThermometer2);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);

    lcd.init();
    lcd.backlight();
}
void loop() {
    temperature_1 = getDallasTemperature(sensors, insideThermometer);
    temperature_2 = getDallasTemperature(sensors2, insideThermometer2);

    salinitasSatu = getSalinity(AnalogInPin);
    salinitasDua = getSalinity(AnalogInPin2);

    ph_val1 = getPh(PhPin, calibration_value, avgval, temp, buffer_arr);
    ph_val2 = getPh(PhPin2, calibration_value, avgval2, temp2, buffer_arr2);

    if (millis() - processTime[0] >= 2000){
        processTime[0] = millis();
        Serial.print("Temp 1 = ");
        Serial.print(temperature_1);
        Serial.print("             Temp 2 = ");
        Serial.print(temperature_2);
        Serial.println();
        Serial.print("Salinity 1 = ");
        Serial.print(salinitasSatu);
        Serial.print("          Salinity 2 = ");
        Serial.print(salinitasDua);
        Serial.print("           Fuzzy      = ");
        Serial.print(defuzzyfikasi());
        Serial.println();
        Serial.print("Ph Value 1 = ");
        Serial.print(ph_val1);
        Serial.print("           Ph Value 2 = ");
        Serial.print(ph_val2);
        Serial.println();
//        digitalWrite(IN_1, defuzzyfikasi());
    }
    if (millis() - processTime[1] >= 2000){
        processTime[1] = millis();
        lcd.setCursor (5, 0);
        lcd.setCursor (3, 2);
        //-- LCD PRINT --//
    }
    delay(500);
}
