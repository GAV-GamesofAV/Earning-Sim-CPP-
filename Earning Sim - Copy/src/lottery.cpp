#include "../include/lottery.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "lottery.h"
using namespace std;
using namespace Lottery;

void Lottery::lottery()
{

    int ch;
    double winAmount = 100000;
    int ticketPrice = 500;
    cout << "Welcome to Number Guesser Club!\n"
         << endl
         << "Here you have to guess a number between 1 and 100." << endl
         << "You will be given 5 chances to guess" << endl
         << "Winning price is $" << winAmount << endl
         << " 1 Ticket cost $" << ticketPrice << endl
         << endl
         << "Wants to play (Type 1 to play) : ";
    if (cin >> ch && ch == 1)
    {
        if (Wallet >= ticketPrice)
        {
            Wallet -= ticketPrice;
            srand(static_cast<unsigned>(time(0)));
            int max = 100;
            int min = 1;
            int Number = rand() % (max - min + 1) + min;

            int guess = 0;
            int num;
            bool won = false;
            do
            {
                cout << "Enter a number between 1 and 100 : ";
                if (cin >> num && num <= 100 && num > 0)
                {
                    guess++;
                    if (num == Number)
                    {
                        cout << "You guessed it in " << guess << " times " << endl
                             << "You won $" << winAmount << endl
                             << endl;
                        Wallet += winAmount;
                        won = true;
                    }
                    else if (num > Number)
                    {
                        cout << "\nToo High!\n\n";
                    }
                    else
                    {
                        cout << "\nToo Low!\n\n";
                    }
                }
                else
                {
                    cout << "\nEnter valid number!\n\n";
                    cin.clear();
                    cin.ignore();
                }
            } while (guess < 5 && !won);
            if (!won)
            {
                cout << "\nYou lose!\n\n";
            }
        }
        else
        {
            cout << "\nNot Enough Balance!\n\n";
        }
    }
    else
    {
        cin.clear();
        cin.ignore();
    }
}
