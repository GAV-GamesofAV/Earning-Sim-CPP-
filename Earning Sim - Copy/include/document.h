#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

using namespace std;

extern double Wallet;

namespace Document
{
    class adhaarCard
    {
        private :
            bool isDoc; 
            string name;
            double adhaarNumber;
            double mobileNumber;
            
        public : 
            void saveData();
            void loadData();
            adhaarCard();
            ~adhaarCard();
            void createDocument();
            double getAdhaarNum();
    };
} 

#endif