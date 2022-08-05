//
// Created by Iwan on 23/05/2022.
//
#include <iostream>
using namespace std;

float salinitasSatu, salinitasDua;
float uRendahSalSatu, uSedangSalSatu, uTinggiSalSatu;
float uRendahSalDua, uSedangSalDua, uTinggiSalDua;

float minr[9];
float Rule[9];

float redup = 0;
float normal = 0.5;
float terang = 1;

unsigned char salinitasRendah1(){
    if (salinitasSatu <= 20.46){ uRendahSalSatu =1;}
    else if (salinitasSatu >= 20.46 && salinitasSatu <= 30.69){ uRendahSalSatu= (30.69 - salinitasSatu) / (30.69 - 20.46);}
    else if (salinitasSatu >= 30.69){ uRendahSalSatu =0;}
    return uRendahSalSatu;
}
unsigned char salinitasSedang1(){
    if (salinitasSatu <= 20.46){ uSedangSalSatu =0;}
    else if (salinitasSatu >= 20.46 && salinitasSatu <= 30.69){ uSedangSalSatu= (salinitasSatu - 20.46) / (30.69 - 20.46);}
    else if (salinitasSatu >= 30.69 && salinitasSatu <= 51.5){ uSedangSalSatu= (51.5 - salinitasSatu) / (51.5 - 30.69);}
    else if (salinitasSatu >= 51.5){ uSedangSalSatu =0;}
    return uSedangSalSatu;
}
unsigned char salinitasTinggi1() {
    if (salinitasSatu <= 30.69) { uTinggiSalSatu = 0; }
    else if (salinitasSatu >= 30.69 && salinitasSatu <= 51.5) { uTinggiSalSatu = (salinitasSatu - 30.69) / (51.5 - 30.69); }
    else if (salinitasSatu >= 51.5) { uTinggiSalSatu = 1; }
    return uTinggiSalSatu;
}

unsigned char salinitasRendah2(){
    if (salinitasDua <= 20.46){ uRendahSalDua =1;}
    else if (salinitasDua >= 20.46 && salinitasDua <= 30.69){ uRendahSalDua= (30.69 - salinitasDua) / (30.69 - 20.46);}
    else if (salinitasDua >= 30.69){ uRendahSalDua =0;}
    return uRendahSalDua;
}
unsigned char salinitasSedang2(){
    if (salinitasDua <= 20.46){ uSedangSalDua =0;}
    else if (salinitasDua >= 20.46 && salinitasDua <= 30.69){ uSedangSalDua= (salinitasDua - 20.46) / (30.69 - 20.46);}
    else if (salinitasDua >= 30.69 && salinitasDua <= 51.5){ uSedangSalDua= (51.5 - salinitasDua) / (51.5 - 30.69);}
    else if (salinitasDua >= 51.5){ uSedangSalDua =0;}
    return uSedangSalDua;
}
unsigned char salinitasTinggi2() {
    if (salinitasDua <= 30.69) { uTinggiSalDua = 0; }
    else if (salinitasDua >= 30.69 && salinitasDua <= 51.5) { uTinggiSalDua = (salinitasDua - 30.69) / (51.5 - 30.69); }
    else if (salinitasDua >= 51.5) { uTinggiSalDua = 1; }
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
int main(){
    salinitasSatu = 30.89;
    salinitasDua = 21.99;
    cout << "Sinar UV : " << defuzzyfikasi();
}
