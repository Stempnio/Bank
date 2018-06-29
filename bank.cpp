#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "bank.h"
#include <fstream>


using namespace std;

void powrot()
{

    cout << "Aby powrocic nacisnij [1]" << endl;

    char powrot;

    do
    {
        powrot = getch();
        switch(powrot)
            {
            case 49: cout << ' '; // po prostu nic sie nie dzieje i powraca do menu
                break;
            }
    }while(powrot != 49);
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
    //int konto;
    string nazw;
    int srodki;
    cout << "Twoj stan konta to: " << majatek << " PLN" << endl;
    //cout << "Numer konta: ";  // obecnie brak
    //wprowadzanie_int(konto);
    cout << "Nazwisko odbiorcy: ";
    wprowadzanie_string(nazw);

    if(nazw == nazwisko)
    {
        cout << "Nie mozna przelac srodkow na wlasne konto, transakcja anulowana" << endl;
        Sleep(2000);
        return;
    }

    string konto_przelewane = nazw + ".txt";

    ifstream konto_przelew(konto_przelewane.c_str(), ios::in); // jedynie odczyt poprzedniego stanu konta aby zastapic go nowymi (zmieniona ilosc pieniedzy)
    if(konto_przelew.good() == false)
    {
        cout << "Brak konta w bazie danych, transakcja anulowana" << endl;
        Sleep(2000);
        return;
    }

        string linia;
        int numer_linii = 1;
        string login;
        string hasl;
        int pieniadze;

        while(getline(konto_przelew, linia)) // nalezu pobrac aby pozniej zapisac ze zmienionymi pieniazkami
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

    konto_przelew.close();


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
    //cout << "Numer konta: " << konto << endl;
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

        fstream konto_przelew2(konto_przelewane.c_str(), ios::out); // zapisywanie majatku konta na ktory byl zrobiony przelew

        pieniadze = pieniadze + srodki;
        konto_przelew2 << login << endl;
        konto_przelew2 << hasl << endl;
        konto_przelew2 << pieniadze << endl;
        konto_przelew2.close();
        }

   if(potwierdzenie == 'n')
        cout << "Transakcja anulowana";

   Sleep(1500);
}

void Klient::dane_klienta()
{


    string nazwa_pliku = nazwisko + ".txt";
    string login;
    string hasl;
    float pieniadze;

    string linia;
    int numer_linii = 1;

ifstream plik(nazwa_pliku.c_str(), ios::in);
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

    layout();

    char wybor;


    cout << "[1] Przelew srodkow" << endl;
    cout << "[2] Dane konta" << endl;
    cout << "[3] Zmiana hasla" << endl;
    cout << "[0] Wylogowanie" << endl;

    wybor = getch();

    switch(wybor)
    {
        case 49: k.przelew();
                 break;
        case 50: k.wyswietl_dane();
                 break;
        case 51: k.zmiana_hasla();
                 break;
        case 48: zalogowany = false;
                 break;
    }
}
void Klient::logowanie(bool &zalogowany) // zwraca nazwisko czyli login
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
                {
                ladowanie();
                zalogowany = true;
                }
            else
                {
                cout << "Niepoprawny login i/lub haslo" << endl;
                Sleep(1500);
                }

        }

    nazwisko = poprawny_login;
    haslo = poprawne_haslo;

}
void Klient::wyswietl_dane()
{
    layout();

    cout << "Nazwisko:  " << nazwisko << endl;
    cout << "Haslo:  " << haslo << endl;
    cout << "Dostepne srodki:  " << majatek << endl;

    powrot();
}

void Klient::zmiana_hasla()
{
    string nazwa_pliku = nazwisko + ".txt";

    ifstream konto_odczyt(nazwa_pliku.c_str(), ios::in);
    if(konto_odczyt.good() == false)
    {
        cout << "Blad krytyczny, brak konta w bazie" << endl;
        exit(0);
    }

        string linia;
        int numer_linii = 1;
        string login;
        string hasl;
        int pieniadze;

        while(getline(konto_odczyt, linia)) // nalezu pobrac aby pozniej zapisac ze zmienionymi srodkami
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

    konto_odczyt.close();

    layout();
    string password;
    cout << "Podaj nowe haslo: ";
    cin >> password;

    layout();

    cout << "Nowe haslo: " << password << endl << "Zachowac zmiany? (y/n)" <<endl;
    char wybor;

    wybor = getch();
    bool end_loop = false;
    do
    {
        switch(wybor)
        {
        case 121:
                  {
                  haslo = password;
                  fstream konto_zapis(nazwa_pliku.c_str(), ios::out); // zapisywanie majatku konta na ktory byl zrobiony przelew
                  konto_zapis << login << endl;
                  konto_zapis << haslo << endl;
                  konto_zapis << pieniadze << endl;
                  konto_zapis.close();
                  end_loop = true;
                  }
            break;
        case 110: end_loop = true;
            break;
        default: cout << "Wybierz y lub n" << endl;
        }
    }while(end_loop == false);


}

void ladowanie()
{

    layout();
    cout << "       Trwa ladowanie" << endl;
    char b = 219;
    cout  << "     ";
    for(int i = 0; i < 9; i++)
    {
        cout << b << ' ';
        Sleep(80);
    }
}

void ekran_powitalny(Klient k)
{
    layout();
    cout << "Witaj w systemie bankowosci internetowej." << endl;
    cout << "[1] Logowanie" << endl;
    cout << "[2] Rejestracja" << endl;
    char wybor;
    bool end_loop = false;
    do
    {
        wybor = getch();

        switch(wybor)
        {
        case 49: end_loop = true;
                 break;
        case 50: {
                 k.rejestracja();
                 end_loop = true;
                 break;
                 }
        default: cout << "Wybierz 1 lub 2" << endl;
        }
    }while(end_loop == false);
}

void Klient::rejestracja()
{
    layout();
    string login;
    string password;

        cout << "Podaj nazwisko: ";
        wprowadzanie_string(login);
        cout << "Podaj haslo: ";
        wprowadzanie_string(password);

        layout();

        cout << "Dane nowego konta:" << endl;
        cout << "Nazwisko: " << login << endl;
        cout << "Haslo: " << password << endl;
        cout << "Utworzyc konto? (y/n)" << endl;

    int poczatkowe_srodki = 10;
    char yn;

    yn = getch();
    bool end_loop = false;
    do
    {
        switch(yn)
        {
        case 121: {
                string nazwa_pliku = login + ".txt";
                ifstream sprawdzenie(nazwa_pliku.c_str());
                    if(sprawdzenie.good()) // gdy pliku nie bedzie utworzone zostanie nowe konto ( by nie nadpisac juz istniejacego)
                        {
                        cout << "Konto o podanej nazwie istnieje w bazie danych, tworzenie konta przerwane. Nacisnij dowolny przycisk aby kontynuowac" << endl;
                        getch();
                        end_loop = true;
                        }
                     else if(sprawdzenie.good() == false)
                     {

                    fstream nowe_konto(nazwa_pliku.c_str(), ios::out);

                    nowe_konto << login << endl;
                    nowe_konto << password << endl;
                    nowe_konto << poczatkowe_srodki << endl;

                    nowe_konto.close();

                    cout << "Konto zostalo utworzone, konto zostalo zasilone srodkami: 10 PLN, jako bonus przy zakladaniu konta" << endl;
                    cout << "Teraz mozesz sie zalogowac, nacisnij dowolny przycisk aby kontynuowac" << endl;
                    getch();
                    end_loop = true;
                     }
                  }
            break;
        case 110: {
                cout << "Tworzenie konta anulowane, nacisnij dowolny przycisk aby kontynuowac" << endl;
                getch();
                end_loop = true;
                  }
            break;
        default: cout << "Wybierz y lub n" << endl;
        }
    }while(end_loop == false);


}

