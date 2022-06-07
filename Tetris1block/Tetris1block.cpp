#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <thread>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

using namespace std;

#include "modules.h"
Table t = { 1 };
short centerX;
short centerY;
short gameMode = 1; // 1 - Still goin
                    // 2 - Lose
                    // 3 - Win
int lines = 0;
short waiting = 1000;

#include "functions.h"

int main()
{
    srand(time(0));
    cout << left << boolalpha;

    bool stay = true;
    while (stay) {
        system("cls");
        cout << "\t\tTETRIS\n";
        cout << "\t1) Play\n";
        cout << "\t2) Controls\n";
        cout << "\t0) Exit\n";

        short secim = _getch();

        switch (secim)
        {
        case 49:
            stay = false;
            system("cls");
            break;
        case 50:
            system("cls");
            cout << "\t\tCONTROLS\n";
            cout << "Up arrow\t|\tRotate\n";
            cout << "Left arrow\t|\tMove left\n";
            cout << "Right arrow\t|\tMove right\n";
            cout << "Down arrow\t|\tMove down\n";
            cout << "\nPress something to return back...";
            secim = _getch();
            system("cls");
        case 48:
            system("cls");
            cout << "\n\tThx for using my program...\n";
            exit(0);
        }
    }

    thread th(goDown);
    thread thh(screen);

    srand(time(nullptr));
    cout << left << boolalpha;

    fillTable();

    setCursor(false);

    movements();

    th.join();
    thh.join();

}