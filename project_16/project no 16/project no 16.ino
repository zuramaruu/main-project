#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Dht 3, Ph 3, Soil Moisture 3 *** 3


#define DHTPIN A2 //PIN yang terhubung pada pinout DHT22
#define DHTPIN A3
#define DHTPIN A4
#define DHTTYPE DHT22 //

DHT dht(A2, DHTTYPE); //Konfigurari DHT22
DHT dht2(A3, DHTTYPE);
DHT dht3(A4, DHTTYPE);

int t, h, t2, h2, t3, h3; //dht22

int SensorPin = A5; // soil moisture

//ph sensor 1
float calibration_value = 21.34 + 4.0;
float calibration_value2 = 21.34;
float calibration_value3 = 21.34;
int phval = 0;
int phval2 = 0;
int phval3 = 0;
unsigned long int avgval;
unsigned long int avgval2;
unsigned long int avgval3;
int buffer_arr[10], temp;
int buffer_arr2[10], temp2;
int buffer_arr3[10], temp3;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  dht.begin(); //Memulai koneksi antara Arduino dengan DHT22
  dht2.begin();
  dht3.begin();
  lcd.init();                      // initialize the lcd
  lcd.backlight();
}
void loop()
{
  t = dht.readTemperature(); //Membaca data suhu
  h = dht.readHumidity(); //Membaca data kelembaban
  t2 = dht2.readTemperature(); //Membaca data suhu
  h2 = dht2.readHumidity(); //Membaca data kelembaban
  t3 = dht3.readTemperature(); //Membaca data suhu
  h3 = dht3.readHumidity(); //Membaca data kelembaban
  delay(2000);

  //soil moisture
  int SensorValue = analogRead(SensorPin);
  float SensorVolts = analogRead(SensorPin) * 0.0048828125;
  Serial.print("Volt Soil Moisture: ");
//  Serial.print(SensorValue);
  Serial.print(SensorVolts);
  Serial.print("V");
  Serial.println();
  delay(2000);

  //led
  if (t < 34) {
    digitalWrite(2, HIGH);
  }
  else if (t > 34) {
    digitalWrite (2, LOW);
  }

  if (t2 < 34) {
    digitalWrite(3, HIGH);
  }
  else if (t2 > 34) {
    digitalWrite (3, LOW);
  }

  if (t3 < 34) {
    digitalWrite(4, HIGH);
  }
  else if (t3 > 34) {
    digitalWrite (4, LOW);
  }

  lcd.setCursor (5, 0);
  lcd.print("Suhu = ");
  lcd.print(t);
  lcd.print("*C");
  Serial.print("Suhu 1 = ");
  Serial.print(t);
  Serial.print("*C");
  Serial.println();
  lcd.setCursor (3, 2);
  lcd.print("Kelembapan = ");
  lcd.print(h);
  lcd.print("H");
  Serial.print("Kelembapan 1 = ");
  Serial.print(h);
  Serial.println("H");
  Serial.println();


  //DHT2
  Serial.print("Suhu 2= ");
  Serial.print(t2);
  Serial.print("*C");
  Serial.println();
  Serial.print("Kelembapan 2 = ");
  Serial.print(h2);
  Serial.println("H");
  Serial.println();

  //DHT3
  Serial.print("Suhu 3= ");
  Serial.print(t3);
  Serial.print("*C");
  Serial.println();
  Serial.print("Kelembapan 3 = ");
  Serial.print(h3);
  Serial.println("H");
  Serial.println();
  Serial.println();
  Serial.println();

  //  ph sensor 1
  for (int i = 0; i < 10; i++){
    buffer_arr[i] = analogRead(A0);
    delay(30);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 5.0 / 1024 / 6;
  float ph_act = -5.70 * volt + calibration_value;
  lcd.setCursor(0, 0);
  lcd.print("pH Val:");
  Serial.print("pH Val:");
  Serial.println();
  Serial.print(ph_act);
  Serial.println();
  lcd.setCursor(8, 0);
  lcd.print(ph_act);
  delay(100);

  //  ph sensor 2
  for (int i = 0; i < 10; i++)
  {
    buffer_arr2[i] = analogRead(A1);
    delay(30);
  }
  //
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr2[i] > buffer_arr2[j])
      {
        temp2 = buffer_arr2[i];
        buffer_arr2[i] = buffer_arr2[j];
        buffer_arr2[j] = temp2;
      }
    }
  }
  avgval2 = 0;
  for (int i = 2; i < 8; i++)
    avgval2 += buffer_arr2[i];
  float volt2 = (float)avgval2 * 5.0 / 1024 / 6;
  float ph_act2 = -5.70 * volt + calibration_value2;
  lcd.setCursor(0, 0);
  lcd.print("pH2 Val:");
  Serial.print("pH2 Val:");
  Serial.println();
  Serial.print(ph_act2);
  Serial.println();
  lcd.setCursor(8, 0);
  lcd.print(ph_act2);
  delay(100);

  //  ph sensor 3
  for (int i = 0; i < 10; i++)
  {
    buffer_arr3[i] = analogRead(A1);
    delay(30);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr3[i] > buffer_arr3[j])
      {
        temp2 = buffer_arr3[i];
        buffer_arr3[i] = buffer_arr3[j];
        buffer_arr3[j] = temp3;
      }
    }
  }
  avgval3 = 0;
  for (int i = 2; i < 8; i++)
    avgval3 += buffer_arr3[i];
  float volt3 = (float)avgval3 * 5.0 / 1024 / 6;
  float ph_act3 = -5.70 * volt + calibration_value3;
  lcd.setCursor(0, 0);
  lcd.print("pH3 Val:");
  Serial.print("pH3 Val:");
  Serial.println();
  Serial.print(ph_act3);
  Serial.println();
  lcd.setCursor(8, 0);
  lcd.print(ph_act3);
  delay(100);
}
