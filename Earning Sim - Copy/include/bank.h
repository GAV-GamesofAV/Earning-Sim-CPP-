#ifndef BANK_H
#define BANK_H

#include <string>
using namespace std;

extern double Wallet;
extern int level;

namespace BANK
{
    class Bank
    {
    private:
        bool isAC;
        string name;
        int age;
        int acNum;
        int acPin;
        double Balance;

        bool isLoan;
        double loanAmount;
        double maxLoan;
        float loanInterest;

        void createAC();
        void deposit();
        void withdraw();
        void loan();

        void saveData();
        void loadData();

    public:
        void deposit(double amount);
        void withdraw(double amount);
        int getACnum();
        int getACpin();
        Bank();
        ~Bank();
        void bank(); // Main banking system
    };

}

#endif