#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

typedef struct{
    int pocet;
    float koeficient[20];
}Tpolynom;
//Struktura pro polynom, 20 míst pro koeficienty 9a počet koeficientů

typedef struct{
    float a;
    float b;
}Tinterval;
//Intervaly ze kterých např. bisekce hledá výsledek, obsahuje bod A a bod B (oba int)

typedef struct{
    int pocet;
    Tinterval interval[20];
}TRadaIntervalu;
//Seznam všech intervalů pro daný příklad, obsahuje pole typu intervalů a pocet intervalů zapsaných do pole

float horner(Tpolynom polynom, float bod)
{
    float vysledek = polynom.koeficient[0];
    for(int i = 1; i<polynom.pocet; i++)
    {
        vysledek = (vysledek*bod)+polynom.koeficient[i];
    }
    return vysledek;
}
//Hornerovo schéma, vrací výsledek(float) polynomu(Tpolynom) v bodě(float)

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
//Oseka string, vytáhne z něho všechny čísla a udělá z něho normální int

int strVytahnoutCislaFloat(char string[])
{
    char cislo[100];
    int cisloI = 0;
    for(int i = 0;;i++)
    {
        if(string[i] == '\0')
            break;
        if(isdigit(string[i]) != 0 || string[i] == ',' || string[i] == '-')
        {
            cislo[cisloI] = string[i];
            cisloI++;
        }
    }
    cislo[cisloI] = '\0';
    return (float)atof(cislo);
}
////Oseka string, vytáhne z něho všechny čísla a udělá z něho normální float

float loadSoubor(char pathSoubor[], TRadaIntervalu * radaIinter, TRadaIntervalu * radaIextra, Tpolynom * polynom, Tpolynom * derivacePolynom)
{
    FILE * f = fopen(pathSoubor, "r");
    if(f == NULL)
        return false;
    char nadpis[100];
    char pom1[100];
    char pom2[100];
    float presnost;
    fscanf(f, "%s\n%s%f\n", nadpis, pom1, &presnost);
    fscanf(f, "%s", pom1);
    polynom->pocet = strVytahnoutCislaInt(pom1);
    for(int i = 0; i<polynom->pocet; i++)
    {
        fscanf(f, "%f,", &polynom->koeficient[i]);
    }
    fscanf(f, "%s", pom1);
    derivacePolynom->pocet = strVytahnoutCislaInt(pom1);
    for(int i = 0; i<derivacePolynom->pocet; i++)
    {
        fscanf(f, "%f,", &derivacePolynom->koeficient[i]);
    }
    fscanf(f, "%s", pom1);
    radaIinter->pocet = strVytahnoutCislaInt(pom1);
    for(int i = 0; i<radaIinter->pocet; i++)
    {
        fscanf(f, "%s%s", pom1, pom2);
        radaIinter->interval[i].a = strVytahnoutCislaFloat(pom1);
        radaIinter->interval[i].b = strVytahnoutCislaFloat(pom2);
    }
    fscanf(f, "%s", pom1);
    radaIextra->pocet = strVytahnoutCislaInt(pom1);
    for(int i = 0; i<radaIextra->pocet; i++)
    {
        fscanf(f, "%s%s", pom1, pom2);
        radaIextra->interval[i].a = strVytahnoutCislaFloat(pom1);
        radaIextra->interval[i].b = strVytahnoutCislaFloat(pom2);
    }
    return presnost;
}

float regulaFalsi(Tpolynom polynom, Tinterval interval, float epsilon)
{
    float a = interval.a;
    float b = interval.b;
    float fa = horner(polynom, a);
    float fb = horner(polynom, b);
    //printf("fa: %f, fb: %f\n", fa, fb);
    float c=0;
    float fc=0;
    if (fa * fb > 0)
    {
        return 0;
    }
    do
    {

        c=(a*fb - b*fa)/(fb-fa);
        fc=horner(polynom, c);
        //printf("fc: %f\n", fc);
        if(fc*fa<0)
        {
            b=c;
            fb=fc;
        }
        else
        {
            a=c;
            fa=fc;
        }

    } while (fabs(fc)>epsilon);
    return c;
}

int main()
{
    Tpolynom * polynom = malloc(sizeof(Tpolynom));
    Tpolynom * derPolynom = malloc(sizeof(Tpolynom));
    TRadaIntervalu * radaIinter = malloc(sizeof(TRadaIntervalu));
    TRadaIntervalu * radaIextra = malloc(sizeof(TRadaIntervalu));
    printf("Zadejte jmeno souboru, ze ktereho chcete vzit priklad:\n");
    char cesta[100];
    //scanf("%99s", cesta);
    float presnost = loadSoubor(/*cesta*/"input.txt", radaIinter, radaIextra, polynom, derPolynom);
    printf("\n%f", horner(*polynom, 3));
    printf("\n%f", regulaFalsi(*polynom, radaIinter->interval[0], presnost));
    return 0;
}