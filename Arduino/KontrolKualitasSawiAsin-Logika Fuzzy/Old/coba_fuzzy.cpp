#include <iostream>
using namespace std;

float suhu, kelembapan, salinitas1;
float uRendahKel, uSedangKel, uTinggiKel;
float uRendahSal1, uSedangSal1, uTinggiSal1;
float uDingin, uHangat, uPanas;

float minr[27];
float Rule[27];

float suhuNyaDingin = 0, suhuNyaHangat = 0.5, suhuNyaPanas = 1;

unsigned char suhuDingin(){
    if (suhu <= 30){ uDingin =1;}
    else if (suhu >=30 && suhu <=45){ uDingin= (45 - suhu) / 15;}
    else if (suhu >= 45){ uDingin =0;}
    return uDingin;
}
unsigned char suhuHangat(){
    if (suhu <= 30){ uHangat =0;}
    else if (suhu >=30 && suhu <=45){ uHangat= (suhu - 30) / 15;}
    else if (suhu >=45 && suhu <=60){ uHangat= (60 - suhu) / 15;}
    else if (suhu >= 60){ uHangat =0;}
    return uHangat;
}
unsigned char suhuPanas (){
    if (suhu <=45 ){ uPanas =0;}
    else if (suhu >=45 && suhu <=60){ uPanas= (suhu - 45) / 15;}
    else if (suhu >= 60){ uPanas =1;}
    return uPanas;
}

unsigned char kelembapanRendah(){
    if (kelembapan <= 30){ uRendahKel =1;}
    else if (kelembapan >=30 && kelembapan <=45){ uRendahKel= (45 - kelembapan) / 15;}
    else if (kelembapan >= 45){ uRendahKel =0;}
    return uRendahKel;
}
unsigned char kelembapanSedang(){
    if (kelembapan <= 30){ uSedangKel =0;}
    else if (kelembapan >=30 && kelembapan <=45){ uSedangKel= (kelembapan - 30) / 15;}
    else if (kelembapan >=45 && kelembapan <=60){ uSedangKel= (60 - kelembapan) / 15;}
    else if (kelembapan >= 60){ uSedangKel =0;}
    return uSedangKel;
}
unsigned char kelembapanTinggi(){
    if (kelembapan <=45 ){ uTinggiKel =0;}
    else if (kelembapan >=45 && kelembapan <=60){ uTinggiKel= (kelembapan - 45) / 15;}
    else if (kelembapan >= 60){ uTinggiKel =1;}
    return uTinggiKel;
}

unsigned char salinitasRendah(){
    if (salinitas1 <= 30){ uRendahSal1 =1;}
    else if (salinitas1 >= 30 && salinitas1 <= 45){ uRendahSal1= (45 - salinitas1) / 15;}
    else if (salinitas1 >= 45){ uRendahSal1 =0;}
    return uRendahSal1;
}
unsigned char salinitasSedang(){
    if (salinitas1 <= 30){ uSedangSal1 =0;}
    else if (salinitas1 >= 30 && salinitas1 <= 45){ uSedangSal1= (salinitas1 - 30) / 15;}
    else if (salinitas1 >= 45 && salinitas1 <= 60){ uSedangSal1= (60 - salinitas1) / 15;}
    else if (salinitas1 >= 60){ uSedangSal1 =0;}
    return uSedangSal1;
}
unsigned char salinitasTinggi(){
    if (salinitas1 <= 45 ){ uTinggiSal1 =0;}
    else if (salinitas1 >= 45 && salinitas1 <= 60){ uTinggiSal1= (salinitas1 - 45) / 15;}
    else if (salinitas1 >= 60){ uTinggiSal1 =1;}
    return uTinggiSal1;
}

float Min(float a, float b, float c){
    if (a < b && a < c){
        return a;
    } else if (b < a && b < c){
        return b;
    } else if (c < a && c < b){
        return c;
    } else{
        return 0;
    }}

void inferensi(){
    if (uDingin >= 0.5 && uHangat <= 0.5 && uPanas < 1){
        suhuNyaDingin = 1;
        suhuNyaHangat = 0;
        suhuNyaPanas  = 0;
    } else if (uDingin <= 0.5 && uHangat >= 0.5 && uPanas < 1){
        suhuNyaDingin = 0;
        suhuNyaHangat = 1;
        suhuNyaPanas  = 0;
    } else if (uDingin < 0 && uHangat <= 0.5 && uPanas >= 0.5){
        suhuNyaDingin = 0;
        suhuNyaHangat = 0;
        suhuNyaPanas  = 1;
    } else {
         0;
    }
}

void fuzzifikasi(){
    suhuDingin();
    suhuHangat();
    suhuPanas();
    kelembapanRendah();
    kelembapanSedang();
    kelembapanTinggi();
    salinitasRendah();
    salinitasSedang();
    salinitasTinggi();
}

void rule(){
    fuzzifikasi();
}

void defuzzifikasi(){
    if (suhuNyaDingin == 1){
        cout << "Suhunya uDingin";
    } else if (suhuNyaHangat == 1){
        cout << "Suhunya uHangat";
    } else if (suhuNyaPanas == 1){
        cout << "Suhunya uPanas";
    }
}

int main(){
    suhu = 1;
    cout << "uDingin : " << uDingin << "\t" << "uHangat : " << uHangat << "\t" << "uPanas : " << "\t" << uPanas << endl;
//    while (1){cout << "uDingin : " << uDingin << "\t" << "uHangat : " << uHangat << "\t" << "uPanas : " << "\t" << uPanas << endl;}
    inferensi();
    defuzzifikasi();
    return 0;
}

//void loop(){
//
//}