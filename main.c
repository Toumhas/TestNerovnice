#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

typedef struct{
    int pocet;
    float koeficient[20];
}Tpolynom;
//Struktura pro polynom, 20 míst pro koeficienty a počet koeficientů

typedef struct{
    float a;
    float b;
}Tinterval;
//Intervaly ze kterých např. bisekce hledá výsledek

typedef struct{
    int pocet;
    Tinterval interval[20];
}TRadaIntervalu;
//Seznam všech intervalů pro daný příklad

float horner(Tpolynom * polynom, float bod)
{
    float vysledek = polynom->koeficient[0];
    for(int i = 1; i<polynom->pocet; i++)
    {
        vysledek = (vysledek*bod)+polynom->koeficient[i];
    }
    return vysledek;
}
//Hornerovo schéma, vraci výsledek polynomu v bodě

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
    for(int i = 0; i<polynom->pocet; i++)
    {
        fscanf(f, "%f,", &polynom->koeficient[i]);
    }
    fscanf(f, "%s", pom);
    polynom->pocet = strVytahnoutCislaInt(pom);
    for(int i = 0; i<polynom->pocet; i++)
    {
        fscanf(f, "%f,", &polynom->koeficient[i]);
    }
}

int main()
{
    Tpolynom * polynom = malloc(sizeof(Tpolynom));
    TRadaIntervalu * radaI = malloc(sizeof(TRadaIntervalu));
    printf("Zadejte jmeno souboru, ze ktereho chcete vzit priklad:\n");
    char cesta[100];
    scanf("%99s", cesta);
    float presnost = loadSoubor(cesta, radaI, polynom);
    printf("\n%f", horner(polynom, 3));
    return 0;
}