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
    fclose(f);
    return presnost;
}
//Vetsina z toho bude od Martase poskytnuta, jenom to musite poskladat. Sorry not sorry. Tady mate jak by to vypadalo kdybyste si to delali sami

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
//Vysvetlovat tyhle algoritmy nebudu, vpodstate jsou vsechny tri stejny a meni se v nich jen kousek, kdyztak Martasova presentation

float bisekce(Tpolynom polynom, Tinterval interval, float epsilon)
{
    float a = interval.a;
    float b = interval.b;
    float fa = horner(polynom, a);
    float fb = horner(polynom, b);
    float c=0;
    float fc=0;
    if (fa * fb > 0)
    {
        return 0;
    }
    do
    {

        c=(a+b)/2;
        fc=horner(polynom, c);
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

float secny(Tpolynom polynom, Tinterval interval, float epsilon)
{
    float a = interval.a;
    float b = interval.b;
    float fa = horner(polynom, a);
    float fb = horner(polynom, b);
    float c=0;
    float fc=0;
    if (fa * fb > 0)
    {
        return 0;
    }
    c=(a*fb - b*fa)/(fb-fa);
    fc=horner(polynom, c);
    int i = 0;
    while (i<1000 && fabs(fc)>epsilon)
    {
        i++;
        a=b;
        fa=fb;
        b=c;
        fb=fc;
        c=(a*fb - b*fa)/(fb-fa);
        fc=horner(polynom, c);
    }
    return c;
}

float newtonVzorec(float xPred, Tpolynom polynom, Tpolynom polynomDerivace) {
    float xNov = xPred - (horner(polynom, xPred) / horner(polynomDerivace, xPred));
    return xNov;
}
//Pomocna funkce se vzorcem pro newtonovu metodu

float newton(float x, Tpolynom polynom, Tpolynom polynomDerivace, float epsilon) {
    int iterationOut = 1000;
    while (fabsf(horner(polynom, x)) > epsilon) {
        if (iterationOut < 0) {
            return 0;
        }

        x = newtonVzorec(x, polynom, polynomDerivace);
        iterationOut--;
    }

    return x;
}
//Omlouvam se ale zatim newtonovu metodu nechapu, dopisu az mi to nejaky chytry soudruh vysvetli

bool zapsatDoSouboru(char path[], Tpolynom polynom, Tpolynom derPolynom, TRadaIntervalu radaI)
{

}
//Jeste nemam ale vpodstate jen doplneni funkci co jsou ted v mainu a zapsani do souboru

int main()
{
    Tpolynom * polynom = malloc(sizeof(Tpolynom));
    Tpolynom * derPolynom = malloc(sizeof(Tpolynom));
    TRadaIntervalu * radaIinter = malloc(sizeof(TRadaIntervalu));
    TRadaIntervalu * radaIextra = malloc(sizeof(TRadaIntervalu));
    printf("Zadejte jmeno souboru, ze ktereho chcete vzit priklad:\n");
    char path[100];
    scanf("%99s", path);
    float presnost = loadSoubor(path, radaIinter, radaIextra, polynom, derPolynom);
    printf("\n%0.3f", regulaFalsi(*polynom, radaIinter->interval[0], presnost));
    printf("\n%0.3f", bisekce(*polynom, radaIinter->interval[0], presnost));
    printf("\n%0.3f", secny(*polynom, radaIinter->interval[0], presnost));
    printf("\n%0.3f", newton(radaIinter->interval[0].a, *polynom, *derPolynom, presnost));
    zapsatDoSouboru(path, *polynom, *derPolynom, *radaIinter);
    free(polynom);
    free(derPolynom);
    free(radaIinter);
    free(radaIextra);
    return 0;
}
//Alokace na testu zarizena martasem a zkouska funkci zhora, ktera bude ve funkci zapsatDoSouboru