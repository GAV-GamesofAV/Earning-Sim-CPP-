#include "../include/document.h"

#include <iostream>
#include <fstream>
#include "document.h"
using namespace std;
using namespace Document;

adhaarCard ::adhaarCard()
{
   isDoc = false;
   loadData();
}
adhaarCard ::~adhaarCard()
{
   saveData();
}

void adhaarCard ::saveData()
{
   ofstream save("../data/document.data");
   if (save.is_open())
   {
      save << isDoc << endl;
      if (isDoc)
      {
         save << name << endl;
         save << adhaarNumber << endl;
      }
      save.close();
   }
}

void adhaarCard ::loadData()
{
   ifstream load("../data/document.data");
   if (load.is_open())
   {
      load >> isDoc;
      if (isDoc)
      {
         getline(load, name);
         load >> adhaarNumber;
      }
      load.close();
   }
}

void adhaarCard ::createDocument()
{
   int documentFee = 100;
   if (!isDoc)
   {
      cout << "Do you want to make your Adhaar card" << endl
           << "It is the most important document in the game!\n"
           << endl
           << "It will cost you $" << documentFee << endl
           << "Type 1 to confirm : ";
      int ch;
      if (cin >> ch && ch == 1)
      {
         cout << "What is your name : ";
         if (getline(cin, name))
         {
            isDoc = true;
            adhaarNumber = 101011;
            Wallet -= 100;
            cout << "\nCongrats! your adhaar card is generated!\n\n";
            cout << "Your adhaar number is " << adhaarNumber << endl
                 << endl;
         }
      }
   }
   else
   {
      cout << "Your adhaar number is : " << adhaarNumber << endl << endl;
   }
}
double Document::adhaarCard::getAdhaarNum()
{
   return adhaarNumber;
}