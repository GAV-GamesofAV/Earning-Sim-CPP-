#ifndef INVESTMENT_H
#define INVESTMENT_H

#include "document.h"
#include "bank.h"
#include <string>
#include <vector>
using namespace std;

class Bank;

namespace Investment
{

    class DematAccount
    {
    private:
        friend void saveData(DematAccount);
        friend void loadData(DematAccount&);

        bool isAC;
        string name;
        double ID;
        string password;
        double adhaarNumber;
    protected : 

        double Balance;

        void deposit(double amount);
        void withdraw(double amount);
    public:
        DematAccount();
        void withdraw(BANK::Bank &bank);
        void deposit(BANK::Bank &bank);
        void dematAC(Document::adhaarCard adhaar, BANK::Bank &bank);
        void createAC(Document::adhaarCard adhaar, BANK::Bank &bank);


        bool isac();
        double getID();
        string getPassword();
        double getBalance();
    };

    class Stock
    {
    private:
        string stockName;
        int price;
        int quantity; // Quantity of stocks owned by user

    public:
        void setStock(string n, int p);
        void showStock();
        void buy(int q);
        void sell(int q);
        int getPrice();
        int getQuantity();
    };

    class StockMarket : public DematAccount
    {
    private:
        int totalStock;
        vector<Stock> stock;

        void showAllStock();
        void buy(int i);
        void sell(int i);

    public:
        StockMarket(string names[5], int prices[5]);
        void stockMarket();
    };

    void InvestingAPP(DematAccount& demat, StockMarket& stockMarket, Document::adhaarCard& adhaar, BANK::Bank& bank);

    void saveData(DematAccount ac);
    void loadData(DematAccount &ac);
}

#endif