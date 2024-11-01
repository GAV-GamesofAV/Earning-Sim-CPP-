#ifndef INVESTMENT_H
#define INVESTMENT_H

#include "document.h"
#include "bank.h"
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

#define MAXSTOCKS 5
class Bank;

namespace Investment
{


    class StockMarket;
    class Stock;
    class DematAccount
    {
    private:
        friend void saveData(DematAccount, StockMarket &);
        friend void loadData(DematAccount &, StockMarket &);

        bool isAC;
        string name;
        double ID;
        string password;
        double adhaarNumber;

    protected:
        double Balance;

    public:
        DematAccount();

        void deposit(double amount);
        void withdraw(double amount);
        void withdraw(BANK::Bank &bank);
        void deposit(BANK::Bank &bank);
        void dematAC(Document::adhaarCard adhaar, BANK::Bank &bank);
        void createAC(Document::adhaarCard adhaar, BANK::Bank &bank);

        bool isac();
        double getID();
        string getPassword();
        double getBalance();

        Stock getStockData();
    };

    class Stock
    {
    private:
        friend void fluctuatePrice(StockMarket &);
        friend void saveData(DematAccount, StockMarket &);
        friend void loadData(DematAccount &, StockMarket &);
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
        string getStockName();
    };

    class StockMarket : public DematAccount
    {
    private:
    friend void fluctuatePrice(StockMarket &);
    friend void saveData(DematAccount, StockMarket&);
    friend void loadData(DematAccount &, StockMarket &);
        int totalStock;
        vector<Stock> stock;

        void showAllStock();
        void buy(int i, DematAccount &demat);
        void sell(int i, DematAccount &demat);

    public:
        StockMarket(vector<string> stockNames, vector<int> stockPrices);
        void stockMarket(DematAccount &demat);
    };

    void InvestingAPP(DematAccount &demat, StockMarket &stockMarket, Document::adhaarCard &adhaar, BANK::Bank &bank);

    void fluctuatePrice(StockMarket &stockmarket);

    void saveData(DematAccount ac, StockMarket &stockmarket);
    void loadData(DematAccount &ac, StockMarket &stockmarket);
};

#endif