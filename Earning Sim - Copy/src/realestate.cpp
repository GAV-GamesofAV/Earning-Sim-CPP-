#include "..\include\realestate.h"
#include <iostream>
#include <vector>
#include <string>
#include "realestate.h"

#include "..\include\bank.h"

using namespace std;
using namespace REALESTATE;

// Property Class
void Property ::setProperty(string name, double price)
{
    propertyName = name;
    propertyPrice = price;
    isOwned = false;
}

void Property ::displayProperty()
{
    cout << propertyName << endl
         << "Price : " << endl
         << "Is Owned : " << isOwned << endl;
}

void Property ::buy(BANK::Bank &bank)
{
    if (!isOwned)
    {
        if (Wallet >= propertyPrice)
        {
            cout << endl
                 << "Do you wants to purchase this property?" << endl
                 << "Type 1 to buy : ";
            int ch;
            if (cin >> ch && ch == 1)
            {
                cout << "Select payment method :" << endl
                     << "1. Cash" << endl
                     << "2. Bank" << endl
                     << "Enter choice : ";
                int ch;
                if (cin >> ch && (ch == 1 || ch == 2))
                {
                    isOwned = true;
                    switch (ch)
                    {
                    case 1:
                        Wallet -= propertyPrice;
                        break;
                    case 2:
                        bank.withdraw(propertyPrice);
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    cout << "Invalid choice!\n\n";
                }
            }
            else
            {
                cin.clear();
                cin.ignore();
            }
        }
        else
        {
            cout << "Not enough budget!\n\n";
        }
    }
    else
    {
        cout << "\nYou already own this property!\n\n";
    }
}

void Property ::sell(BANK::Bank &bank)
{
    if (isOwned)
    {
        cout << "Select payment receiving method :" << endl
             << "1. Cash" << endl
             << "2. Bank : "
             << "ENter choice : ";
        int ch;
        if (cin >> ch && (ch == 1 || ch == 2))
        {
            isOwned = false;
            switch (ch)
            {
            case 1:
                Wallet += propertyPrice;
                break;
            case 2:
                bank.deposit(propertyPrice);
            default:
                break;
            }
            Wallet += propertyPrice;
        }
    }
    else
    {
        cout << "You Don't own this property!\n\n";
    }
}

// Real Estate Class
REALESTATE::RealEstate::RealEstate(vector<string> propertyNames, vector<double> propertyPrices)
{
    totalProperties = propertyNames.size();
    properties.resize(totalProperties);
    for (int i = 0; i < totalProperties; i++)
    {
        properties[i].setProperty(propertyNames.at(i), propertyPrices.at(i));
    }
}

void RealEstate ::viewAllProperties()
{
    for (int i = 0; i < totalProperties; i++)
    {
        cout << i << ". ";
        properties.at(i).displayProperty();
        cout << endl;
    }
}

void RealEstate ::Market(BANK::Bank &bank)
{
    int ch;
    bool loop = true; // COntrol loop
    if (properties.size() > 0)
    {
        while (loop)
        {
            viewAllProperties();
            cout << "Select a property : ";
            if (cin >> ch && ch > 0 && ch <= totalProperties)
            {
                int p;
                p = ch - 1;
                cout << "Select an option : " << endl
                     << "1. Buy" << endl
                     << "2. Sell" << endl
                     << "3. Back " << endl;
                if (cin >> ch)
                {
                    switch (p)
                    {
                    case 1:
                        properties.at(p).buy(bank);
                        break;
                    case 2:
                        properties.at(p).sell(bank);
                        break;
                    case 3:
                        loop = false;
                        break;
                    default:
                        cout << "Invalid Choice!\n\n";
                        break;
                    }
                }
                else
                {
                    cout << "pls enter valid choice!\n\n";
                }
            }
            else
            {
                cout << "\nInvalid Choice !\n\n";
                cin.clear();
                cin.ignore();
            }
        }
    }
    else
    {
        cout << "Error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    }
}