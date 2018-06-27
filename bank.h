#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;


class Klient
{
    string nazwisko;
    string haslo;
    float majatek;

public:
    Klient(string nazwisko = "Nazwisko", string haslo = "Haslo", float majatek = 0)
    {
        this-> nazwisko = nazwisko;
        this-> haslo = haslo;
        this-> majatek = majatek;
    }

    void dane_klienta();
    void wyswietl_dane();
    void przelew();
    void zmiana_hasla();
    void historia();
    void zmiana_majatku();
    void logowanie(bool &zalogowany); // musi byc w klasie aby od razu przypisac nazwisko haslo
};

void konta();
void layout();
string wprowadzanie_string();
int wprowadzanie_int();
void powrot();
void menu(bool &zalogowany, Klient);
