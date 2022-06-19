#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN A2 //-- PIN yang terhubung pada pinout DHT22
#define DHTPIN A3
#define DHTPIN A4
#define DHTTYPE DHT22

DHT dht(A2, DHTTYPE); //-- Konfigurari DHT22
DHT dht2(A3, DHTTYPE);
DHT dht3(A4, DHTTYPE);
int t, h, t2, h2, t3, h3; //-- dht22

//-- PH sensor --//
float calibration_value = 21.34 + 4.0;
float calibration_value2 = 21.34 + 4.0;
float calibration_value3 = 21.34 + 4.0;
int phval = 0;
int phval2 = 0;
int phval3 = 0;
unsigned long int avgval;
unsigned long int avgval2;
unsigned long int avgval3;
int buffer_arr[10], temp;
int buffer_arr2[10], temp2;
int buffer_arr3[10], temp3;

//-- MOSTURE SENSOR --//
int SensorPin = A5;
int SensorPin2 = A5;
int SensorPin3 = A5;
float kfSensorVolts = 0.0048828125;


void setup(){
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    dht.begin(); //-- Memulai koneksi antara Arduino dengan DHT22
    dht2.begin();
    dht3.begin();
}
void loop(){
    t = dht.readTemperature();   //-- Membaca data suhu
    t2 = dht2.readTemperature(); //-- Membaca data suhu
    t3 = dht3.readTemperature(); //-- Membaca data suhu
    h = dht.readHumidity();      //-- Membaca data kelembaban
    h2 = dht2.readHumidity();    //-- Membaca data kelembaban
    h3 = dht3.readHumidity();    //-- Membaca data kelembaban

    led(t, 34);
    led(t2, 34);
    led(t3, 34);

    tampilkanSuhuKelembapan(1, t, h);   //-- DHT1
    tampilkanSuhuKelembapan(2, t2, h2); //-- DHT2
    tampilkanSuhuKelembapan(3, t3, h3); //-- DHT3
    Serial.println();

    tampilkanPh(1, calibration_value, phval, avgval, temp, buffer_arr);
    tampilkanPh(2, calibration_value2, phval2, avgval2, temp2, buffer_arr2);
    tampilkanPh(3, calibration_value3, phval3, avgval3, temp3, buffer_arr3);
    Serial.println();

    tampilkanKelembapan(1, SensorPin, kfSensorVolts);
    tampilkanKelembapan(2, SensorPin2, kfSensorVolts);
    tampilkanKelembapan(3, SensorPin3, kfSensorVolts);
    Serial.println();
    delay(2000);
}

void tampilkanKelembapan(int num, int SensorPinVal, float kfSensorVolt){
    int SensorValue = analogRead(SensorPinVal);
    float SensorVolts = analogRead(SensorPinVal) * kfSensorVolt;
    Serial.print("Sensor Value ");
    Serial.print(num);
    Serial.print(" = ");
    Serial.print(SensorValue);
    Serial.println();
    Serial.print("Sensor Volt ");
    Serial.print(num);
    Serial.print(" = ");
    Serial.print(SensorVolts);
    Serial.print(" V ");
    Serial.println();
}

void phSet(){
    for(int i=0;i<10;i++){
        buffer_arr[i]=analogRead(A0);
    }
    for (int i = 0; i < 10; i++){
        buffer_arr2[i] = analogRead(A0);
    }
    for (int i = 0; i < 10; i++){
        buffer_arr3[i] = analogRead(A0);
    }
}

void tampilkanPh(int num, float cal_value, int ph_value, unsigned long int avg_value, int temp_value, int buffer_arrFun[]){
    phSet();
    for(int i=0;i<9;i++)
    {
        for(int j=i+1;j<10;j++)
        {
            if(buffer_arrFun[i]>buffer_arrFun[j])
            {
                temp=buffer_arrFun[i];
                buffer_arrFun[i]=buffer_arrFun[j];
                buffer_arrFun[j]=temp;
            }
        }
    }
    avgval=0;
    for(int i=2;i<8;i++)
        avgval+=buffer_arrFun[i];
    float volt=(float)avgval*5.0/1024/6;
    float ph_act = -5.70 * volt + calibration_value;
    Serial.print("pH Val ");
    Serial.print(num);
    Serial.print(" = ");
    Serial.print(ph_act);
    Serial.println();
}
void tampilkanSuhuKelembapan(int number, int temperature, int humidity){
    Serial.print("Suhu ");
    Serial.print(number);
    Serial.print(" = ");
    Serial.print(temperature);
    Serial.print("*C");
    Serial.println();
    Serial.print("Kelembapan ");
    Serial.print(number);
    Serial.print(" = ");
    Serial.print(humidity);
    Serial.println("H");

}

void led(int temperature, int value){
    if (temperature < value){
        digitalWrite(2, HIGH);
    } else if (temperature > value){
        digitalWrite(2, LOW);
    }
}
