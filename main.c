#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

typedef struct{
    int pocet;
    float koeficient[20];
}Tpolynom;

typedef struct{
    float a;
    float b;
}Tinterval;

typedef struct{
    int pocet;
    Tinterval interval[20];
}TRadaIntervalu;

float horner(Tpolynom * polynom, float bod)
{
    float vysledek = polynom->koeficient[0];
    for(int i = 1; i<polynom->pocet; i++)
    {
        vysledek = (vysledek*bod)+polynom->koeficient[i];
    }
    return vysledek;
}

int strVytahnoutCislaInt(char string[])
{
    char cislo[100];
    int cisloI = 0;
    for(int i = 0;;i++)
    {
        if(string[i] == '\0')
            break;
        if(isdigit(string[i]) != 0)
        {
            cislo[cisloI] = string[i];
            cisloI++;
        }
    }
    cislo[cisloI] = '\0';
    return atoi(cislo);
}

float loadSoubor(char pathSoubor[], TRadaIntervalu * radaI, Tpolynom * polynom)
{
    FILE * f = fopen(pathSoubor, "r");
    if(f == NULL)
        return false;
    int pocet = 0;
    char nadpis[100];
    char pom[100];
    float presnost;
    fscanf(f, "%s\n%s%f\n", nadpis, pom, &presnost);
    fscanf(f, "%s", pom);
    polynom->pocet = strVytahnoutCislaInt(pom);
    printf("%d\n", polynom->pocet);
    for(int i = 0; i<polynom->pocet; i++)
    {
        fscanf(f, "%f,", &polynom->koeficient[i]);
    }
    printf("%f", polynom->koeficient[3]);
}

int main()
{
    Tpolynom * polynom = malloc(sizeof(Tpolynom));
    TRadaIntervalu * radaI = malloc(sizeof(TRadaIntervalu));
    float presnost = loadSoubor("input.txt", radaI, polynom);
    printf("\n%f", horner(polynom, 3));
    return 0;
}