#ifndef REALESTATE_H
#define REALESTATE_H

#include <string>
#include <vector>

#include "bank.h"

extern double Wallet;

using namespace std;

namespace REALESTATE
{
    class Property
    {
        private : 
            string propertyName;
            double propertyPrice;
            bool isOwned;
        public : 
            void setProperty(string name, double price);
            void displayProperty();

            void buy(BANK::Bank &bank);
            void sell(BANK::Bank &bank);
    };
    
    class RealEstate
    {
        private : 
            int totalProperties;
            vector<Property> properties;
        public : 
            RealEstate(vector<string> propertyNames, vector<double> propertyPrices);
            void viewAllProperties();
            void Market(BANK::Bank &bank);
    };
};

#endif