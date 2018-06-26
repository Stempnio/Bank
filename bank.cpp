#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "bank.h"
#include <fstream>


using namespace std;


void powrot() // niezrobione
{
    cout << "Aby powrocic nacisnij [1]" << endl;
}
void layout()
{
    system("cls");
    char b = 219;

    for(int i=0; i<10; i++)
        cout << b;

    cout << " Bank RPZKO ";

    for(int i=0; i<10; i++)
        cout << b;

    cout << endl << endl;
}
int wprowadzanie_int(int &data)
{
    cin >> data;
    if(!cin.good())
    {
        do
        {
            cout << "Dane wprowadzone niepoprawnie! Podaj ponownie" << endl;
            cin.clear();
            cin.sync();
            cin >> data;
        }while(!cin.good());
    }

    return data;
}
string wprowadzanie_string(string &data)
{
    cin >> data;
    if(!cin.good())
    {
        do
        {
            cout << "Dane wprowadzone niepoprawnie! Podaj ponownie" << endl;
            cin.clear();
            cin.sync();
            cin >> data;
        }while(!cin.good());
    }

    return data;
}
void Klient::zmiana_majatku()
{
    string nazwa_pliku = nazwisko + ".txt";
    fstream plik(nazwa_pliku.c_str(), ios::out);

    plik << nazwisko << endl;
    plik << haslo << endl;
    plik << majatek << endl;
    plik.close();
}
void Klient::przelew()
{
    layout();
    char potwierdzenie;
    int konto;
    string nazw;
    int srodki;
    cout << "Twoj stan konta to: " << majatek << " PLN" << endl;
    cout << "Numer konta: ";
    wprowadzanie_int(konto);
    cout << "Nazwisko odbiorcy: ";
    wprowadzanie_string(nazw);
    cout << "Kwota przelewu: ";
    wprowadzanie_int(srodki);
    if(srodki > majatek)
    {
        do
        {
        cout << "Niewystarczajace srodki na koncie, podaj ponownie: ";
        cin.clear();
        cin.sync();
        wprowadzanie_int(srodki);
        }while(srodki > majatek);
    }

    Sleep(1000);

    layout();

    cout << "Potwierdz przelew" << endl;
    cout << "Nazwisko odbiorcy: " << nazw << endl;
    cout << "Numer konta: " << konto << endl;
    cout << "Kwota przelewu: " << srodki << " PLN" << endl;
    cout << "Ilosc srodkow na koncie po transakcji: " << majatek-srodki << " PLN" << endl;

    cout << endl << "Wykonac opercje? (y/n)" << endl;

    bool end_l = false;

    do      // wykonuje sie poki uzytkownik nie poda y lub n
    {
        potwierdzenie = getch();

        switch(potwierdzenie)
        {
        case 121: end_l = true;
        case 110: end_l = true;
            break;
        default: cout << "Podaj y lub n";
        }
    }while(end_l == false);

    Sleep(300);

    layout();
    if(potwierdzenie == 'y')
        {
        cout << "Transakcja wykonana pomyslnie" << endl;
        majatek = majatek - srodki;
        zmiana_majatku();
        }

   if(potwierdzenie == 'n')
        cout << "Transakcja anulowana";

   Sleep(1500);
}

void Klient::dane_klienta()
{
    string login;
    string hasl;
    float pieniadze;

    string linia;
    int numer_linii = 1;

ifstream plik("kowalski.txt", ios::in);
        if(plik.good() == false)
        {
            cout << "Blad krytyczny przy otwarciu pliku!" << endl;
            exit(0);
        }
        else
        {
            while(getline(plik, linia))
                {
                    switch(numer_linii)
                    {
                    case 1: login = linia;
                        break;
                    case 2: hasl = linia;
                        break;
                    case 3: pieniadze = atoi(linia.c_str());
                        break;
                    }
                numer_linii++;
                }
        }

        plik.close();

        nazwisko = login;
        haslo = hasl;
        majatek = pieniadze;
}
void menu(bool &zalogowany, Klient k)
{
    //ifstream plik()
    layout();

    char wybor;


    cout << "[1] Przelew srodkow" << endl;
    cout << "[2] //Przelew srodkow" << endl;
    cout << "[3] //rzelew srodkow" << endl;
    cout << "[0] Wylogowanie" << endl;

    wybor = getch();

    switch(wybor)
    {
        case 49: k.przelew();
                 break;
        case 48: zalogowany = false;
                 break;
    }
}

void logowanie(bool &zalogowany) // zwraca nazwisko czyli login
{

    layout();
    zalogowany = false;
    string poprawny_login; // dane wczytywane z pliku txt
    string poprawne_haslo;
    string podany_login;
    string podane_haslo;

    cout << "Podaj login: ";
    wprowadzanie_string(podany_login);
    cout << "Podaj haslo: ";
    wprowadzanie_string(podane_haslo);

    string nazwa_pliku = podany_login + ".txt";
    string linia;
    int numer_linii = 1; // potrzebne do getline

    ifstream plik(nazwa_pliku.c_str(), ios::in);
        if(plik.good() == false)
        {
            cout << "Niepoprawny login i/lub haslo" << endl;
            Sleep(1500);
            //
        }
        else
        {
            while(getline(plik, linia))
            {
                switch(numer_linii)
                {
                case 1: poprawny_login = linia;
                    break;
                case 2: poprawne_haslo = linia;
                    break;
                }
            numer_linii++;
            }


            plik.close();

            if(podany_login == poprawny_login && podane_haslo == poprawne_haslo)
                zalogowany = true;
            else
                {
                cout << "Niepoprawny login i/lub haslo" << endl;
                Sleep(1500);
                }

        }


}


