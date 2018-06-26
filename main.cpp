#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "bank.h"
#include <fstream>

using namespace std;



int main()
{
    bool zalogowany;
    while(1)
    {
        zalogowany = false;
        logowanie(zalogowany);
        Klient *k = new Klient;

        while(zalogowany == true)
        {
            k->dane_klienta();
            menu(zalogowany, *k);
        }
        delete k;
    }
}

