#include <iostream>
#include <fstream>
#include <vector>

#include "../include/bank.h"
#include "../include/lottery.h"
#include "../include/document.h"
#include "../include/investment.h"
#include "../include/realestate.h"

using namespace std;

Document ::adhaarCard adhaar;
BANK::Bank bank;

double Wallet = 1000;
int level = 1;

void saveData();
void loadData();

int main()
{
    // Setting values of Stocks
    vector<string> stockNames = {"Coca Cola", "Amazon", "Rockstar", "Google", "Tata"};
    vector<int> stockPrices = {450, 1300, 760, 1230, 670};

    cout << stockNames.size();
    // Setting values of RealEstateProperties
    vector<string> propertyNames = {"Blue Haven", "Willow Creek Villas", "Sunnyvale Residences", "Maplewood Homes", "Crystal Heights", "Grand Horizon", "Skyline Residences"};
    vector<double> propertyPrices = {460000, 780000, 1300000, 1850000, 2900000, 5600000, 13400000};

    // Objects
    Investment::DematAccount DematAC;
    Investment::StockMarket stockmarket(stockNames, stockPrices);

    REALESTATE::RealEstate realEstate(propertyNames, propertyPrices);

    // Vars
    int ch;
    // Loading Data (Some classes automatically loads their data)
    loadData();
    Investment::loadData(DematAC, stockmarket);
    while (1)
    {

        cout << "Wallet : $" << Wallet << endl
             << "1. Bank" << endl
             << "2. Documents" << endl
             << "3. Lottery" << endl
             << "4. Investment" << endl
             << "5. Real Estate" << endl
             << "6. Learn" << endl
             << "7. Job" << endl
             << "8. About" << endl
             << "9. Exit" << endl
             << "Enter choice : ";
        if (cin >> ch && ch <= 9)
        {
            Investment ::fluctuatePrice(stockmarket); // Trading price changer
            switch (ch)
            {
            case 1:
                bank.bank();
                break;
            case 2:
                adhaar.createDocument();
                break;
            case 3:
                Lottery::lottery();
                break;
            case 4:
                Investment::InvestingAPP(DematAC, stockmarket, adhaar, bank);
                break;
            case 5:
                realEstate.Market(bank);
       break;
            case 9:
                saveData();
                Investment::saveData(DematAC, stockmarket);
                return 0;
                break;
            default:
                break;
            }
        }
        else
        {
            cout << "\nInvalid choice!\n\n";
            cin.clear();
            cin.ignore();
        }
        Investment::fluctuatePrice(stockmarket);
    }
}

void saveData()
{
    ofstream save("../data/main.data");
    if (save.is_open())
    {
        save << Wallet << endl;
        save << level << endl;
        save.close();
    }
    else
    {
        cout << "Error Saving!\n";
    }
}

void loadData()
{
    ifstream load("../data/main.data");
    if (load.is_open())
    {
        load >> Wallet;
        load >> level;
        load.close();
    }
    else
    {
        cout << "error loading";
    }
}