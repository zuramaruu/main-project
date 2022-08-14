#include <DHT.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);


#define DHTPIN A2 //PIN yang terhubung pada pinout DHT22
#define DHTPIN A3
#define DHTPIN A4
#define DHTTYPE DHT22 //

DHT dht(A2, DHTTYPE); //Konfigurari DHT22
DHT dht2(A3, DHTTYPE);
DHT dht3(A4, DHTTYPE);

int t; //Variabel Suhu
int h; //Variabel Kelembaban
int t2;
int h2;
int t3;
int h3;

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
  
  if (t < 30) {
    digitalWrite(2, HIGH);
  }
  else {
    digitalWrite(2, LOW);
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

}
