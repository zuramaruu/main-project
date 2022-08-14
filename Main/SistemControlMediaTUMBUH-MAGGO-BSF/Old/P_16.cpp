#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <LoRa.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define LORA_SS 53 // define pin nss rst dio0
#define LORA_RST 11
#define LORA_DIO0 9

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

DHT dht(2, DHTTYPE); //-- Konfigurari DHT22
DHT dht2(3, DHTTYPE);
DHT dht3(4, DHTTYPE);
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
int SensorPin = A4;
int SensorPin2 = A5;
int SensorPin3 = A6;
int moisSensorVal, moisSensorVal2, moisSensorVal3;
float moisSensorVolt, moisSensorVolt2, moisSensorVolt3;
float kfSensorVolts = 0.0048828125;
long moisSensorValPercent = 0.0;
long moisSensorValPercent2 = 0.0;
long moisSensorValPercent3 = 0.0;

int waktu_sebelumnya = 0;
int waktu_sebelumnya2 = 0;
int waktu_sebelumnya3 = 0;

void setup() {
    Serial.begin(9600);
    //  pinMode(2, OUTPUT);
    pinMode(LORA_SS, OUTPUT);
    digitalWrite(LORA_SS, HIGH);

    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
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
void loop() {
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
    //    moisSensorVolt = getMoistureSensorVolts(SensorPin, kfSensorVolts);
    //    moisSensorVolt2 = getMoistureSensorVolts(SensorPin2, kfSensorVolts);
    //    moisSensorVolt3 = getMoistureSensorVolts(SensorPin3, kfSensorVolts);

    moisSensorValPercent = map(moisSensorVal, 0, 1023, 0, 100);
    moisSensorValPercent2 = map(moisSensorVal2, 0, 1023, 0, 100);
    moisSensorValPercent3 = map(moisSensorVal3, 0, 1023, 0, 100);

    //-- LORA SEND --// delay 1s
    if (waktu_sekarang - waktu_sebelumnya >= 1000) {
        waktu_sebelumnya = waktu_sekarang;
        //        LoRa.beginPacket();
        String allString = String(temperature_1) + "#" +
                           String(temperature_2) + "#" +
                           String(temperature_3) + "#" +
                           String(hum_1) + "#" +
                           String(hum_2) + "#" +
                           String(hum_3) + "#" +
                           String(ph_val1) + "#" +
                           String(ph_val2) + "#" +
                           String(ph_val3) + "#" +
                           String(moisSensorVal) + "#" +
                           String(moisSensorVal2) + "#" +
                           String(moisSensorVal3) + "#";
        //        LoRa.print(allString);
        //        LoRa.endPacket();
    }

    //-- Serial.print --// delay 2s
    if (waktu_sekarang2 - waktu_sebelumnya2 >= 2000) {
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
        Serial.print(moisSensorVal);
        Serial.print("        Mois 2 = ");
        Serial.print(moisSensorVal2);
        Serial.print("        Mois 3 = ");
        Serial.print(moisSensorVal3);
        Serial.println();
    }

    //-- LCD PRINT --// delay 2,5s
    if (waktu_sekarang3 - waktu_sebelumnya3 >= 2500) {
        waktu_sebelumnya3 = waktu_sekarang3;
        lcd.setCursor (5, 0);
        lcd.setCursor (3, 2);
    }

    lamp(temperature_1, 34, relay_lamp1);
    lamp(temperature_2, 34, relay_lamp2);
    lamp(temperature_3, 34, relay_lamp3);

    kipas(temperature_1, 34, relay_kipas1);
    kipas(temperature_2, 34, relay_kipas2);
    kipas(temperature_3, 34, relay_kipas3);

    waterPump(moisSensorValPercent, 50, relay_wp1);
    waterPump(moisSensorValPercent2, 50, relay_wp2);
    waterPump(moisSensorValPercent3, 50, relay_wp3);

    delay(500);
}
void relaySet() {
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
int getMoistureSensorVal(int SensorPinVal) {
    int SensorValue = analogRead(SensorPinVal);
    return SensorValue;
}
float getMoistureSensorVolts(int SensorPinVal, float kfSensorVolt) {
    float SensorVolts = analogRead(SensorPinVal) * kfSensorVolt;
    return SensorVolts;
}
float getPh(int SensorPin, float cal_value, unsigned long int avg_value, int temp_value, int buffer_arrFun[]) {
    for (int i = 0; i < 10; i++) {
        buffer_arrFun[i] = analogRead(SensorPin);
        delay(30);
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            if (buffer_arrFun[i] > buffer_arrFun[j])
            {
                temp_value = buffer_arrFun[i];
                buffer_arrFun[i] = buffer_arrFun[j];
                buffer_arrFun[j] = temp_value;
            }
        }
    }
    avg_value = 0;
    for (int i = 2; i < 8; i++)
        avg_value += buffer_arrFun[i];
    float volt = (float)avg_value * 5.0 / 1024 / 6;
    float ph_act = -5.70 * volt + cal_value;
    return ph_act;
}
int getDhtTemperatureHumidity(DHT dht_pin) {
    int t = dht_pin.readTemperature();
    int h = dht_pin.readHumidity();
    return t, h;
}
long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void led(int temperature, int value) {
    if (temperature < value) {
        digitalWrite(2, HIGH);
    } else if (temperature > value) {
        digitalWrite(2, LOW);
    }
}
void lamp(int temperature, int value, int pin) {
    if (temperature < value) {
        digitalWrite(pin, HIGH);
    } else if (temperature > value) {
        digitalWrite(pin, LOW);
    }
}
void kipas(int temperature, int value, int pin) {
    if (temperature < value) {
        digitalWrite(pin, LOW);
    } else if (temperature > value) {
        digitalWrite(pin, HIGH);
    }
}
void waterPump(int soilMoisturePercent, int valuePercent, int pin) {
    if (soilMoisturePercent < valuePercent) {
        digitalWrite(pin, HIGH);
    } else if (soilMoisturePercent > valuePercent) {
        digitalWrite(pin, LOW);
    }
}
