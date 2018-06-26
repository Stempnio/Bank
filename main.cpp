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
        Klient *k = new Klient;
        k->logowanie(zalogowany);
        while(zalogowany == true)
        {
            k->dane_klienta();
            menu(zalogowany, *k);
        }
        delete k;
    }
}

