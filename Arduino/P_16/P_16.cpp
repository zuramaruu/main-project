#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <LoRa.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define DHTPIN A2 //-- PIN yang terhubung pada pinout DHT22
#define DHTPIN2 A3
#define DHTPIN3 A4

#define DHTTYPE DHT22

#define relay_lamp1 23 //-- Konfigurasi Pin Relay
#define relay_lamp2 25
#define relay_lamp3 27
#define relay_wp1 29
#define relay_wp2 31
#define relay_wp3 33
#define relay_kipas1 35
#define relay_kipas2 37
#define relay_kipas3 39

DHT dht(A2, DHTTYPE); //-- Konfigurari DHT22
DHT dht2(A3, DHTTYPE);
DHT dht3(A4, DHTTYPE);
int temperature_1, hum_1, temperature_2, hum_2, temperature_3, hum_3; //-- dht22

//-- PH sensor --//
float calibration_value = 21.34 + 4.0;
unsigned long int avgval, avgval2, avgval3;
int buffer_arr[10], temp;
int buffer_arr2[10], temp2;
int buffer_arr3[10], temp3;
int PhPin = A1;
int PhPin2 = A2;
int PhPin3 = A3;
float ph_val1, ph_val2, ph_val3;

//-- MOSTURE SENSOR --//
int SensorPin = A5;
int SensorPin2 = A5;
int SensorPin3 = A5;
int moisSensorVal, moisSensorVal2, moisSensorVal3;
float moisSensorVolt, moisSensorVolt2, moisSensorVolt3;
float kfSensorVolts = 0.0048828125;

int waktu_sebelumnya = 0;
int waktu_sebelumnya2 = 0;
int waktu_sebelumnya3 = 0;

void setup(){
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    dht.begin(); //-- Memulai koneksi antara Arduino dengan DHT22
    dht2.begin();
    dht3.begin();

    lcd.init();
    lcd.backlight();

//    while (!Serial);
//    Serial.println("LoRa Sender");
//    if (!LoRa.begin(915E6)) {
//        Serial.println("Starting LoRa failed!");
//        while (1);
//    }

}
void loop(){
    unsigned long waktu_sekarang = millis();
    unsigned long waktu_sekarang2 = millis();
    unsigned long waktu_sekarang3 = millis();

    relaySet(); // -- Mengatur pin Relay

    temperature_1, hum_1 = getDhtTemperatureHumidity(dht);
    temperature_2, hum_2 = getDhtTemperatureHumidity(dht2);
    temperature_3, hum_2 = getDhtTemperatureHumidity(dht3);
    led(temperature_1, 34);
    led(temperature_2, 34);
    led(temperature_3, 34);

    ph_val1 = getPh(PhPin, calibration_value, avgval, temp, buffer_arr);
    ph_val2 = getPh(PhPin2, calibration_value, avgval2, temp2, buffer_arr2);
    ph_val3 = getPh(PhPin3, calibration_value, avgval3, temp3, buffer_arr3);

    moisSensorVal = getMoistureSensorVal(SensorPin);
    moisSensorVal2 = getMoistureSensorVal(SensorPin2);
    moisSensorVal3 = getMoistureSensorVal(SensorPin3);
    moisSensorVolt = getMoistureSensorVolts(SensorPin, kfSensorVolts);
    moisSensorVolt2 = getMoistureSensorVolts(SensorPin2, kfSensorVolts);
    moisSensorVolt3 = getMoistureSensorVolts(SensorPin3, kfSensorVolts);

    //-- LORA SEND --// delay 1s
    if(waktu_sekarang - waktu_sebelumnya >= 1000) {
        waktu_sebelumnya = waktu_sekarang;
//        LoRa.beginPacket();
//        LoRa.print(String(temperature_1));
//        LoRa.print("#");
//        LoRa.print(String(temperature_2));
//        LoRa.print("#");
//        LoRa.print(String(temperature_3));
//        LoRa.print("#");
//        LoRa.print(String(hum_1));
//        LoRa.print("#");
//        LoRa.print(String(hum_2));
//        LoRa.print("#");
//        LoRa.print(String(hum_3));
//        LoRa.print("#");
//        LoRa.print(String(ph_val1));
//        LoRa.print("#");
//        LoRa.print(String(ph_val2));
//        LoRa.print("#");
//        LoRa.print(String(ph_val3));
//        LoRa.print("#");
//        LoRa.print(String(moisSensorVolt));
//        LoRa.print("#");
//        LoRa.print(String(moisSensorVolt2));
//        LoRa.print("#");
//        LoRa.print(String(moisSensorVolt3));
//        LoRa.print("#");
//        LoRa.endPacket();
    }

    //-- Serial.print --// delay 2s
    if(waktu_sekarang2 - waktu_sebelumnya2 >= 2000) {
        waktu_sebelumnya2 = waktu_sekarang2;
        Serial.print("Temp 1 = ");
        Serial.print(temperature_1);
        Serial.print("           Temp 2 = ");
        Serial.print(temperature_2);
        Serial.print("           Temp 3 = ");
        Serial.print(temperature_3);
        Serial.println();
        Serial.print("Hum  1 = ");
        Serial.print(hum_1);
        Serial.print("           Hum  2 = ");
        Serial.print(hum_2);
        Serial.print("           Hum  3 = ");
        Serial.print(hum_3);
        Serial.println();
        Serial.print("Ph   1 = ");
        Serial.print(ph_val1);
        Serial.print("       Ph   2 = ");
        Serial.print(ph_val2);
        Serial.print("       Ph   3 = ");
        Serial.print(ph_val3);
        Serial.println();
        Serial.print("Mois 1 = ");
        Serial.print(moisSensorVolt);
        Serial.print("        Mois 2 = ");
        Serial.print(moisSensorVolt2);
        Serial.print("        Mois 3 = ");
        Serial.print(moisSensorVolt3);
        Serial.println();
    }

    //-- LCD PRINT --// delay 2,5s
    if(waktu_sekarang3 - waktu_sebelumnya3 >= 2500) {
        waktu_sebelumnya3 = waktu_sekarang3;
        lcd.setCursor (5, 0);
        lcd.setCursor (3, 2);
    }
    delay(500);
}
void relaySet(){
    pinMode(relay_lamp1, OUTPUT);
    pinMode(relay_lamp2, OUTPUT);
    pinMode(relay_lamp3, OUTPUT);
    pinMode(relay_wp1, OUTPUT);
    pinMode(relay_wp2, OUTPUT);
    pinMode(relay_wp3, OUTPUT);
    pinMode(relay_kipas1, OUTPUT);
    pinMode(relay_kipas2, OUTPUT);
    pinMode(relay_kipas3, OUTPUT);
}
int getMoistureSensorVal(int SensorPinVal){
    int SensorValue = analogRead(SensorPinVal);
    return SensorValue;
}
float getMoistureSensorVolts(int SensorPinVal, float kfSensorVolt){
    float SensorVolts = analogRead(SensorPinVal) * kfSensorVolt;
    return SensorVolts;
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
int getDhtTemperatureHumidity(DHT dht_pin){
    int t = dht_pin.readTemperature();
    int h = dht_pin.readHumidity();
    return t, h;
}
void led(int temperature, int value){
    if (temperature < value){
        digitalWrite(2, HIGH);
    } else if (temperature > value){
        digitalWrite(2, LOW);
    }
}