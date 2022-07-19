#include <stdio.h>
#include <math.h>

float nadi, suhu;
//float A, B;

float udingin[] = {0, 0, 25};
float unormal[] = {20, 27, 36};
float upanas[] = {35, 50, 50};

float ulambat[] = {0, 0, 60};
float usedang[] = {50, 70, 101};
float ucepat[] = {100, 120, 120};

float sakit = 0;
float ks = 0.5;
float sehat = 1;

float minr[10];
float Rule[10];

float fudingin()
{
    if (suhu < udingin[1])
    {
        return 1;
    }
    else if (suhu >= udingin[1] && suhu <= udingin[2])
    {
        return (udingin[2] - suhu) / (udingin[2] - udingin[1]);
    }
    else if (suhu > udingin[2])
    {
        return 0;
    }
}

float funormal()
{
    if (suhu < unormal[0])
    {
        return 0;
    }
    else if (suhu >= unormal[0] && suhu <= unormal[1])
    {
        return (suhu - unormal[0]) / (unormal[1] - unormal[0]);
    }
    else if (suhu >= unormal[1] && suhu <= unormal[2])
    {
        return (unormal[2] - suhu) / (unormal[2] - unormal[1]);
    }
    else if (suhu > unormal[2])
    {
        return 0;
    }
}

float fupanas()
{
    if (suhu < upanas[0])
    {
        return 0;
    }
    else if (suhu >= upanas[0] && suhu <= upanas[1])
    {
        return (suhu - upanas[0]) / (upanas[1] - upanas[0]);
    }
    else if (suhu > upanas[1])
    {
        return 1;
    }
}

float fulambat()
{
    if (nadi < ulambat[1])
    {
        return 1;
    }
    else if (nadi >= ulambat[1] && nadi <= ulambat[2])
    {
        return (ulambat[2] - nadi) / (ulambat[2] - ulambat[1]);
    }
    else if (nadi > ulambat[2])
    {
        return 0;
    }
}

float fusedang()
{
    if (nadi < usedang[0])
    {
        return 0;
    }
    else if (nadi >= usedang[0] && nadi <= usedang[1])
    {
        return (nadi - usedang[0]) / (usedang[1] - usedang[0]);
    }
    else if (nadi >= usedang[1] && nadi <= usedang[2])
    {
        return (usedang[2] - nadi) / (usedang[2] - usedang[1]);
    }
    else if (nadi > usedang[2])
    {
        return 0;
    }
}

float fucepat()
{
    if (nadi <= ucepat[0])
    {
        return 0;
    }
    else if (nadi > ucepat[0] && nadi < ucepat[1])
    {
        return (nadi - ucepat[0]) / (ucepat[1] - ucepat[0]);
    }
    else if (nadi >= ucepat[1])
    {
        return 1;
    }
}


float Min(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    else if (b < a)
    {
        return b;
    }
    else
    {
        return a;
    }
}

void rule()
{
    // if suhu dingin and nadi lambat then kurang sehat
    minr[1] = Min(fudingin(), fulambat());
    Rule[1] = ks;
    // if suhu dingin and nadi sedang then kurang sehat
    minr[2] = Min(fudingin(), fusedang());
    Rule[2] = ks;
    // if suhu dingin and nadi cepat then sakit
    minr[3] = Min(fudingin(), fucepat());
    Rule[3] = sakit;
    // if suhu normal and nadi lambat then kurang sehat
    minr[4] = Min(funormal(), fulambat());
    Rule[4] = ks;
    // if suhu normal and nadi sedang then sehat
    minr[5] = Min(funormal(), fusedang());
    Rule[5] = sehat;
    // if suhu normal and nadi cepat then kurang sehat
    minr[6] = Min(funormal(), fucepat());
    Rule[6] = ks;
    // if suhu panas and nadi lambat then kurangg sehat
    minr[7] = Min(fupanas(), fulambat());
    Rule[7] = ks;
    // if suhu panas and nadi sedang then kurang sehat
    minr[8] = Min(fupanas(), fusedang());
    Rule[8] = ks;
    // if suhu panas and nadi cepat then kurang sehat
    minr[9] = Min(fupanas(), fucepat());
    Rule[9] = ks;
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

int main()
{
    printf("Masukan Suhu Badan : ");
    scanf("%f", &suhu);
    printf("Masukan Denyut : ");
    scanf("%f", &nadi);

    printf("Keanggotaan udingin : %f\n", fudingin());
    printf("Keanggotaan unormal : %f\n", funormal());
    printf("Keanggotaan upanas : %f\n", fupanas());

    printf("Keanggotaan ulambat : %f\n", fulambat());
    printf("Keanggotaan usedang : %f\n", fusedang());
    printf("Keanggotaan ucepat : %f\n", fucepat());

    printf("Hasil Deff : %f\n", defuzzyfikasi());

    return 0;
}