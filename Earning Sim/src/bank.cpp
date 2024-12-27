#include "../include/bank.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "bank.h"

using namespace std;
using namespace BANK;

void setMaxLoan(double &maxloan)
{
    if (level == 1)
    {
        maxloan = 10000;
    }
    else if (level == 2)
    {
        maxloan = 50000;
    }
    else if (level == 3)
    {
        maxloan = 100000;
    }
    else if (level == 4)
    {
        maxloan = 1000000;
    }
    else
    {
        maxloan = 10000000;
    }
}
void setInterest(float &i)
{
    srand(static_cast<unsigned>(time(0)));
    float min = 0.08;
    float max = 0.12;
    i = min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (max - min));
}

void Bank ::saveData()
{
    ofstream save("../data/bankdata.data");
    if (save.is_open())
    {
        save << isAC << endl;
        if (isAC)
        {
            save << name << endl;
            save << age << endl;
            save << acNum << endl;
            save << acPin << endl;
            save << Balance << endl;
            save << isLoan << endl;
            if (isLoan)
            {
                save << loanAmount;
            }
        }
        save.close();
    }
    else
    {
        cout << "Error saving data!\n";
    }
}
void Bank ::loadData()
{
    ifstream load("../data/bankdata.data");
    if (load.is_open())
    {
        load >> isAC;
        if (isAC)
        {
            load.ignore();
            getline(load, name);
            load >> age;
            load >> acNum;
            load >> acPin;
            load >> Balance;
            load >> isLoan;
            if (isLoan)
            {
                load >> loanAmount;
            }
        }
        load.close();
    }
}

int BANK::Bank::getACnum()
{
    return acNum;
}
int BANK::Bank::getACpin()
{
    return acPin;
}
Bank ::Bank()
{
    Balance = 0;
    isAC = false;
    isLoan = false;
    loadData();
}
Bank ::~Bank()
{
    saveData();
}

void Bank ::createAC()
{
    if (!isAC)
    {
        bool loop = true; // Control loop
        double initialBalance;
        do
        {
            cin.ignore();
            cout << "\nCreate your account!" << endl
                 << "Enter your name : ";
            getline(cin, name);
            cout << "Enter your age : ";
            if (cin >> age)
            {
                acNum = 1111;
                cout << "\nYour A/C number is " << acNum << endl
                     << "create a 4-digit pin : ";
                if (cin >> acPin && acPin >= 1000 && acPin <= 9999)
                {
                    cout << "Enter initial balance : ";
                    if (cin >> initialBalance && initialBalance <= Wallet)
                    {
                        Balance = initialBalance;
                        Wallet -= initialBalance;
                        isAC = true;
                        cout << "\nAccount created!\n\n";
                    }
                    else
                    {
                        cout << "\nEither not enough money or invalid value!\n\n";
                        cin.clear();
                        cin.ignore();
                    }
                }
                else
                {
                    cout << "\nEnter valid pin!\n\n";
                    cin.clear();
                    cin.ignore();
                }
            }
            else
            {
                cout << "\nInvalid age!\n\n";
                cin.clear();
                cin.ignore();
            }
        } while (!isAC);
    }
}

void Bank ::deposit()
{
    int num;
    cout << "Enter your A/C number : ";
    if (cin >> num && num == acNum)
    {
        cout << "\nBalance : " << Balance << endl
             << "Enter amount to deposit : ";
        double amount;
        if (cin >> amount && amount <= Wallet)
        {
            Wallet -= amount;
            Balance += amount;
            cout << "\n$" << amount << " deposited successfully!\n\n";
        }
        else
        {
            cout << "\nEither not enough money or invalid value!\n\n";
            cin.clear();
            cin.ignore();
        }
    }
    else
    {
        cout << "\nAccount not found!\n\n";
    }
}

void Bank ::withdraw()
{
    int num, pin;
    cout << "Enter your A/C number : ";
    if (cin >> num && num == acNum)
    {
        cout << "Enter your pin : ";
        if (cin >> pin && pin == acPin)
        {
            cout << "Balance : " << Balance << endl
                 << "Enter amount to withdraw : ";
            double amount;
            if (cin >> amount && amount <= Balance)
            {
                Wallet += amount;
                Balance -= amount;
                cout << "\n$" << amount << " withdrawed successfully!\n\n";
            }
            else
            {
                cout << "Either not enough balance or invalid value!\n\n";
                cin.clear();
                cin.ignore();
            }
        }
        else
        {
            cout << "\nIncorrect pin!\n\n";
        }
    }
    else
    {
        cout << "\nAccount not found\n\n";
    }
}

void Bank ::loan()
{
    double amount;
    setMaxLoan(maxLoan);
    if (!isLoan)
    {
        setInterest(loanInterest);
        cout << "Welcome!\nHere you can get loan according to your level!" << endl
             << "But there are some conditions!" << endl
             << endl
             << "There must not be an existing loan!" << endl
             << endl
             << "Also you have to pay an interest of 8%-12%. Interest changes by time but only when there is no existing loan" << endl
             << endl;
        cout << "Your current lvl is " << level << endl
             << "You can get a loan of maximum $" << maxLoan << endl
             << endl
             << "Current interest rate is " << loanInterest * 100 << "%" << endl
             << "Enter loan amount (0 or other character if you don't want loan): ";
        if (cin >> amount && amount > 0)
        {
            if (amount <= maxLoan)
            {
                Balance += amount;
                loanAmount = amount + (amount * loanInterest);
                isLoan = true;
                cout << "\n$" << amount << " added to your bank account!\n\n";
            }
            else
            {
                cout << "You can't get a loan of $" << amount << endl
                     << endl;
            }
        }
    }
    else
    {
        cout << "You have an existing loan!\nRepay it first" << endl
             << endl
             << "Remaining payment : $" << loanAmount << endl
             << "Enter amount to pay : ";
        if (cin >> amount && amount > 0 && amount <= loanAmount)
        {
            Wallet -= amount;
            loanAmount -= amount;
            if (loanAmount <= 0)
            {
                isLoan = false;
            }
        }
        else
        {
            cout << "\nInvalid value!\n\n";
        }
    }
}

void Bank ::bank()
{
    int ch;
    if (!isAC)
    {
        createAC();
    }
    bool loop = true; // Variable to control loop
    while (loop)
    {
        cout << "\nSelect an option :-" << endl
             << "1. Balance Inquiry" << endl
             << "2. Deposit" << endl
             << "3. Withdraw" << endl
             << "4. Loan" << endl
             << "5. Back" << endl
             << "Enter choice : ";
        if (cin >> ch && ch <= 5)
        {
            switch (ch)
            {
            case 1:
                cout << "\nA/C number : " << acNum << endl
                     << "A/C pin : " << acPin << endl
                     << "\nBalance : $" << Balance << endl 
                     << endl;
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                loan();
                break;
            case 5:
                loop = false;
                return;
                break;
            }
        }
        else
        {
            cout << "\nEnter valid choice!\n\n";
            cin.clear();
            cin.ignore();
        }
    }
}

void Bank ::deposit(double amount)
{
    if (amount > 0)
    {
        Balance += amount;
    }
    else
    {
        cout << "Invalid amount!\n\n";
    }
}
void Bank ::withdraw(double amount)
{
    if (amount > 0 && amount <= Balance)
    {
        Balance -= amount;
    }
    else
    {
        cout << "Invalid amount or not enough balance!\n\n";
    }
}