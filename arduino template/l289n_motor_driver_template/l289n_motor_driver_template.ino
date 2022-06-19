//menginclude libraries driver motor L298
#include <L298N.h> //Menyertakan library DRIVER MOTOR L298N
 
//inisialisasi pin yang digunakan
const int EN_A = 0;
const int IN_1 = 7;
const int IN_2 = 6;
const int IN_3 = 5;
const int IN_4 = 4;
const int EN_B = 1;
L298N driver(EN_A,IN_1,IN_2,IN_3,IN_4,EN_B);
 
int waktu_tunda = 1000; //waktu tunda
int kecepatan = 150; //kecepatan default tutorial ini (max kecepatan) 255
 
void setup(){}
 
void loop()
{
//Kedua motor bergerak CW sesuai dengan kecepatan 150, dalam waktu 1 detik
driver.forward(kecepatan,waktu_tunda);
driver.full_stop(waktu_tunda); //berhenti keduanya
 
//motor kanan saja yang bergerak
driver.turn_right(kecepatan,waktu_tunda);
driver.full_stop(waktu_tunda); //berhenti
 
//motor kiri saja yang bergerak
driver.turn_left(kecepatan,waktu_tunda);
driver.full_stop(waktu_tunda); //berhenti
 
//Kedua motor bergerak CCW sesuai dengan kecepatan 150, dalam waktu 1 detik
driver.backward(kecepatan,waktu_tunda);
driver.full_stop(waktu_tunda); //berhenti keduanya
}
