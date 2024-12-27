#include "../include/investment.h"
#include "../include/bank.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "investment.h"

using namespace std;
using namespace Investment;
// Demat class
DematAccount ::DematAccount()
{
    isAC = false;
    Balance = 0;
}

void Investment::DematAccount::withdraw(BANK::Bank &bank)
{
    double amount;
    cout << "Enter amount to withdraw : ";
    if (cin >> amount && amount <= Balance)
    {
        bank.deposit(amount);
        Balance -= amount;
    }
}

void Investment::DematAccount::deposit(BANK::Bank &bank)
{
    cout << "Enter amount to deposit : ";
    double amount;
    if (cin >> amount && amount > 0)
    {
        bank.withdraw(amount);
        Balance += amount;
    }
    else
    {
        cout << "Invalid amount!\n\n";
    }
}

void DematAccount ::createAC(Document::adhaarCard adhaar, BANK::Bank &bank)
{
    if (!isAC)
    {
        double adhaarnum;
        int dematFee = 300;
        cout << "Hii, Welcome to GAV Broker" << endl
             << "Here you can open your demat account" << endl
             << "It will help you in various things like Stock Market trading and Index Trading etc" << endl
             << "It will cost you $" << dematFee << "to open your demat account" << endl
             << endl
             << "Type 1 to confirm : ";
        int ch;
        if (cin >> ch && ch == 1)
        {
            cin.ignore();
            cout << "What is your name : ";
            getline(cin, name);
            cout << "Enter your adhaar card number : ";
            if (cin >> adhaarnum && adhaarnum == adhaar.getAdhaarNum())
            {
                adhaarNumber = adhaarnum;
                ID = 11111;
                cout << "Your ID is " << ID << endl
                     << "Create your password : ";
                if (cin >> password)
                {
                    cout << "Enter your bank account details :-" << endl
                         << "Enter your A/C number : ";
                    int eACnum;
                    int eACpin;
                    if (cin >> eACnum && eACnum == bank.getACnum())
                    {
                        cout << "Enter your pin : ";
                        if (cin >> eACpin && eACpin == bank.getACpin())
                        {
                            isAC = true;
                            bank.withdraw(dematFee);
                            cout << "Your account is now created!" << endl
                                 << endl;
                        }
                        else
                        {
                            cout << "Incorrect pin!" << endl;
                            cin.clear();
                            cin.ignore();
                        }
                    }
                    else
                    {
                        cout << "Account not found!\n\n";
                        cin.clear();
                        cin.ignore();
                    }
                }
                else
                {
                    cout << "Enter Valid Password!\n\n";
                    cin.clear();
                    cin.ignore();
                }
            }
            else
            {
                cout << "\nAdhaar card not found!\n\n";
                cin.clear();
                cin.ignore();
            }
        }
        else
        {
            cin.clear();
            cin.ignore();
        }
    }
}

void Investment::DematAccount::dematAC(Document::adhaarCard adhaar, BANK::Bank &bank)
{
    int ch;
    int eID;
    string ePass;
    if (!isAC)
    {
        createAC(adhaar, bank);
    }
    if (isAC)
    {
        while (1)
        {
            cout << "Select an option :-" << endl
                 << "1. Balance Inquiry" << endl
                 << "2. Deposit" << endl
                 << "3. Withdraw" << endl
                 << "4. Back " << endl
                 << "Enter choice : ";
            if (cin >> ch && ch <= 4)
            {
                switch (ch)
                {
                case 1:
                    cout << endl
                         << "Balance : &" << Balance << endl
                         << endl;
                    break;
                case 2:
                    deposit(bank);
                    break;
                case 3:
                    deposit(bank);
                    break;
                case 4:
                    return;
                    break;
                default:
                    break;
                }
            }
            else
            {
                cout << "Invalid choice!\n\n";
                cin.clear();
                cin.ignore();
            }
        }
    }
}

void DematAccount ::withdraw(double amount)
{
    Balance -= amount;
}

void DematAccount ::deposit(double amount)
{
    Balance += amount;
}

double DematAccount::getBalance()
{
    return Balance;
}

bool Investment::DematAccount::isac()
{
    return isAC;
}
double DematAccount::getID()
{
    return ID;
}
string DematAccount::getPassword()
{
    return password;
}

// Stock Class
void Stock ::setStock(string n, int p)
{
    stockName = n;
    price = p;
    quantity = 0;
}

int Stock ::getPrice()
{
    return price;
}

void Investment::Stock::buy(int q)
{
    quantity += q;
}

void Stock ::sell(int q)
{
    quantity -= q;
}

void Stock ::showStock()
{
    cout << stockName << endl
         << "Price : " << price << endl
         << "Quantity : " << quantity << endl
         << endl;
}

int Stock ::getQuantity()
{
    return quantity;
}

string Stock ::getStockName()
{
    return stockName;
}
// Stock Market class
Investment::StockMarket::StockMarket(vector<string> stockNames, vector<int> stockPrices)
{
    totalStock = stockNames.size();
    stock.resize(totalStock); //What the hell
    for(int i = 0; i < totalStock; i++)
    {
        stock.at(i).setStock(stockNames.at(i), stockPrices.at(i));
    }
}

void Investment::StockMarket::showAllStock()
{
    for (int i = 0; i < totalStock; i++)
    {
        cout << i + 1 << ". ";
        stock[i].showStock();
    }
}

void Investment::StockMarket::buy(int i, DematAccount &demat)
{
    int q;
    stock[i].showStock();
    cout << "Enter quantity : ";
    if (cin >> q && (q * stock[i].getPrice()) <= demat.getBalance())
    {
        
        double bill = q * stock[i].getPrice();
        demat.withdraw(bill);
        stock[i].buy(q);
    }
    else
    {
        cout << "\nEither not enough balance or invalid quantity!\n\n";
        cin.clear();
        cin.ignore();
    }
}

void Investment::StockMarket::sell(int i, DematAccount &demat)
{
    int q;
    cout << "Enter quantity : ";
    if (cin >> q && q <= stock[i].getQuantity())
    {
        double bill = q * stock[i].getPrice();
        demat.deposit(bill);
        stock[i].sell(q);
    }
    else
    {
        cout << "Invalid amount or not enough quantity!\n\n";
        cin.clear();
        cin.ignore();
    }
}

void Investment::StockMarket::stockMarket(DematAccount &demat)
{
    int i, ch;
    while (1)
    {
        cout << "Select a stock :-" << endl;
        showAllStock();
        cout << "Enter choice (Type 0 to return): ";
        if (cin >> i && i <= totalStock && i != 0)
        {
            i--;
            cout << "Select an option : " << endl
                 << "1.Buy" << endl
                 << "2. Sell" << endl
                 << "3. Back" << endl;
            if (cin >> ch && ch <= 3)
            {
                switch (ch)
                {
                case 1:
                    buy(i, demat);
                    break;
                case 2:
                    sell(i, demat);
                    break;
                default:
                    return;
                    break;
                }
            }
            else
            {
                cout << "Invalid Choice!\n\n";
            }
        }
        else if (i == 0)
        {
            return;
        }
        else
        {
            cout << "Invaldi choice!\n\n";
        }
    }
}

// Others

void Investment::saveData(DematAccount ac, StockMarket &stockmarket)
{
    ofstream save("../data/investment.data");
    if (save.is_open())
    {
        // Demat Account
        save << ac.isAC << endl;
        if (ac.isAC)
        {
            save << ac.name << endl;
            save << ac.ID << endl;
            save << ac.password << endl;
            save << ac.adhaarNumber << endl;
            save << ac.Balance << endl;
            // Stocks
            save << stockmarket.totalStock << endl;
            for (int i = 0; i < stockmarket.totalStock; i++)
            {
                save << stockmarket.stock[i].stockName << endl;
                save << stockmarket.stock[i].price << endl;
                save << stockmarket.stock[i].quantity << endl;
            }
        }
        save.close();
    }
    else
    {
        cout << "\nError saving data!\n\n";
    }
}

void Investment::loadData(DematAccount &ac, StockMarket &stockmarket)
{
    ifstream load("../data/investment.data");
    if (load.is_open())
    {
        load >> ac.isAC;
        if (ac.isAC)
        {
            load.ignore();
            getline(load, ac.name);
            load >> ac.ID;
            load.ignore();
            getline(load, ac.password);
            load >> ac.adhaarNumber;
            load >> ac.Balance;
            // Stock
            load >> stockmarket.totalStock;
            stockmarket.stock.resize(stockmarket.totalStock);
            for (int i = 0; i < stockmarket.totalStock; i++)
            {
                load.ignore();
                getline(load, stockmarket.stock.at(i).stockName);
                load >> stockmarket.stock.at(i).price;
                load >> stockmarket.stock.at(i).quantity;
            }
        }
        load.close();
    }
    else
    {
        cout << "error loading data" << endl;
    }
}

void Investment::InvestingAPP(DematAccount &demat, StockMarket &stockMarket, Document::adhaarCard &adhaar, BANK::Bank &bank)
{
    int ch;
    if (!demat.isac())
    {
        cout << "First create your demat account!\n\n";
        demat.createAC(adhaar, bank);
    }
    if (demat.isac())
    {
        double eID;
        string ePass;
        cout << "Enter your ID : ";
        if (cin >> eID && eID == demat.getID())
        {
            cout << "Enter your password : ";
            if (cin >> ePass && ePass == demat.getPassword())
            {
                while (1)
                {
                    fluctuatePrice(stockMarket);
                    cout << "Select an option :-" << endl
                         << "1. Demat Account" << endl
                         << "2. Stock Trading" << endl
                         << "3. Back" << endl
                         << "Enter choice : ";
                    if (cin >> ch && ch <= 3)
                    {
                        switch (ch)
                        {
                        case 1:
                            demat.dematAC(adhaar, bank);
                            break;
                        case 2:
                            stockMarket.stockMarket(demat);
                            break;
                        default:
                            return;
                            break;
                        }
                    }
                    else
                    {
                        cout << "\nInvalid CHoice!\n\n";
                        cin.clear();
                        cin.ignore();
                    }
                }
            }
            else
            {
                cout << "Invalid password!\n\n";
                cin.clear();
                cin.ignore();
            }
        }
        else
        {
            cout << "\nInvalid Password!\n\n";
            cin.clear();
            cin.ignore();
        }
    }
}

void Investment :: fluctuatePrice(StockMarket &stockmarket)
{
    float min = -0.9;
    float max = 1.0;
    srand(static_cast<unsigned>(time(0)));
    for(int i = 0; i < stockmarket.totalStock; i++)
    {
        stockmarket.stock[i].price += stockmarket.stock.at(i).price * (min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (max - min)));    
    }
}