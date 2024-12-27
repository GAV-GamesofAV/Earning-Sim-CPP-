#include "../include/realestate.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "realestate.h"

using namespace std;
using namespace REALESTATE;

extern double Wallet;

// Property class
void Property::setProperty(string name, double price, bool own)
{
  propertyName = name;
  propertyPrice = price;
  owned = own;
}


void Property::changePrice(double price)
{
  propertyPrice = price;
}


bool Property::isOwned()
{
  return owned;
}

string Property::getPropertyName()
{
  return propertyName;
}

double Property::getPropertyPrice()
{
  return propertyPrice;
}

void Property::setOwned(bool o)
{
  owned = o;
}

void Property::showInfo()
{
  cout << "Name : " << propertyName
       << endl
       << "Price : " << propertyPrice
       << endl
       << "Purchased : ";
  if (owned)
  {
    cout << "Yes" << endl
         << endl;
  }
  else
  {
    cout << "No" << endl
         << endl;
  }
}

//Real Estate class

RealEstate::RealEstate()
{

  

  totalOwnedProperties = 0;
  // Getting property names and prices

  ifstream loadProperties("../data/properties.data");
  if (loadProperties.is_open())
  {
    loadProperties >> totalProperties; // Total Properti3s
    loadProperties >> totalOwnedProperties;

    vector<string> names;  // Vector to store loaded names
    vector<double> prices; // Vector to store loaded prices
    vector<int> owned;
    names.resize(totalProperties);
    prices.resize(totalProperties);
    owned.resize(totalProperties);

    for (int i = 0; i < totalProperties; i++)
    {
      loadProperties.ignore();
      getline(loadProperties, names.at(i));
      loadProperties >> prices.at(i);
      loadProperties >> owned.at(i);
    }
    loadProperties.close();
    // Setting values
    properties.resize(totalProperties);

    for (int i = 0; i < totalProperties; i++)
    {
      properties.at(i).setProperty(names.at(i), prices.at(i), owned.at(i));
      // Inclrease the value of total owned property var
      if (properties.at(i).isOwned())
      {
        totalOwnedProperties++;
      }
    }
  }
  else
  {
    cout << "Error opening file!\n\n";
  }
}

RealEstate::~RealEstate()
{
  saveData();
}

void RealEstate::displayAllProperties()
{
  for (int i = 0; i < properties.size(); i++)
  {
    cout << i + 1 << ". ";
    properties[i].showInfo();
  }
}

void RealEstate::buyProperty(int i)
{
  cout << "Do you want to purchase " << properties.at(i).getPropertyName()
       << " for $" << properties.at(i).getPropertyPrice() << endl
       << "Type 1 to confirm : ";
  int ch;
  if (cin >> ch && ch == 1)
  {
    if (Wallet >= properties.at(i).getPropertyPrice()) // Replace Wallet here
    {
      Wallet -= properties.at(i).getPropertyPrice();
      properties.at(i).setOwned(true);
      totalOwnedProperties++;
    }
    else
    {
      cout << "You don't have enough money!\n\n";
    }
  }
  else
  {
    cin.clear();
    cin.ignore();
  }
}

void RealEstate::sellProperty(int i)
{
  cout << i << endl;
  cout << "Do you really wants to sell " << properties.at(i).getPropertyName()
       << " for $" << properties.at(i).getPropertyPrice() << endl
       << "Enter 1 to confirm : ";
  int ch;
  if (cin >> ch && ch == 1)
  {
    Wallet += properties.at(i).getPropertyPrice();
    totalOwnedProperties--;
    properties.at(i).setOwned(false);
  }
}

void RealEstate::realEstate()
{
  // int ch;
  // cout << "Welcome, here you can buy or manage your properties!\n\n"
  //      << "Select an option :- " << endl
  //      << "1. Buy Property" << endl
  //      << "2. Manage your properties" << endl
  //      << "3. Back" << endl;
  // if (cin >> ch && ch <= 3)
  // {
  //   switch (ch)
  //   {
  //   case 1:
  //     break;
  //   case 2:
  //     break;
  //   case 3:
  //     break;
  //   default:
  //     break;
  //   }
  // }
  // else
  // {
  //   cout << "Please enter valid choice!\n\n";
  //   cin.clear();
  //   cin.ignore();
  // }

  int ch, i;
  while (1)
  {
    cout << "Balance : ₹" << Wallet << endl << endl;
    cout << "Select a property :-" << endl;
    displayAllProperties();
    cout << "Enter choice : ";
    if (cin >> ch && ch <= totalProperties)
    {
      i = ch - 1;
      // TErminating program
      if (ch == 0)
      {
        return;
      }
      if (!properties.at(i).isOwned())
      {
        buyProperty(i);
      }
      else
      {
        cout << "Select an option :- " << endl
             << "1. Sell" << endl
             << "2. Back" << endl
             << "Enter choice : ";
        if (cin >> ch && ch <= 3)
        {
          switch (ch)
          {
          case 1:
            sellProperty(i);
            break;
          case 2:
            break;
          default:
            exit(0);
            break;
          }
        }
        else
        {
          cout << "Invalid choice!\n\n";
        }
      }
    }
  }
}

void RealEstate::fluctuatePrice()
{
  srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
  int changePrice; //Decides whether to change price or not randomly

  float minPriceChange = -0.01; // -1%
  float maxPriceChange = 0.01; // +1%

  float priceChange;
  double newPrice;
    for(int i = 0; i < totalProperties; i++)
    {
      changePrice = rand() % 2; //Generates 0 or 1 
      if(changePrice == 1)
      {
        priceChange = minPriceChange + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (maxPriceChange - minPriceChange)));
        newPrice = properties[i].getPropertyPrice() + (properties[i].getPropertyPrice() * priceChange);
        properties.at(i).changePrice(newPrice);
      }
    }
}

void RealEstate::saveData()
{
  ofstream save("../data/properties.data");
  if (save.is_open())
  {
    save << totalProperties << endl;
    save << totalOwnedProperties << endl;
    for (int i = 0; i < totalProperties; i++)
    {
      save << properties.at(i).getPropertyName() << endl;
      save << properties.at(i).getPropertyPrice() << endl;
      save << properties.at(i).isOwned();
    }
  }
}

// Others