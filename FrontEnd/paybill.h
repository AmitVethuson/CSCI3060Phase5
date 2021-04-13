#ifndef PAYBILL_H
#define PAYBILL_H


#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "account.h"
#include "login.h"
#include "miscFunctions.h"

using namespace std;

class payBill{
    private:
        string AccountName;
        int AccountNumber;
        string LoginType; 
        string Company;
        float Amount;
        // balance will be part of the Database therefor this is a temp variable 
        float Balance;

    public:
        //--setters--
        //set the account Name
        void setAccountName(string AccountName);
        //set The account Number
        void setAccountNumber(int num);
        //set the loggin type
        void setLogginType(string log);
        //set the Company that will get paid
        void setCompany(string company);
        //set the amount that will be paid
        void setAmount(float amount);
        //set the account balance
        void setBalance(float bal);

        //getters
        //get the account name
        string getAccountName();
        //get the account number
        int getAccountNumber();
        //get the loggin type
        string getLogginType();
        //get the company name that will get paid
        string getCompany();
        //get the amount that will be paid
        float getAmount();
        //get the account balance
        float getBalance();
        //functions
        void paybill(vector<string> lType,login session);
        void save();
};

#endif