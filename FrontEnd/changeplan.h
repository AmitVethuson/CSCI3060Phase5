#ifndef CHANGEPLAN_H
#define CHANGEPLAN_H
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "changeplan.h"
#include "account.h"
#include "login.h"
#include "miscFunctions.h"
using namespace std;


class changePlan{
    private:
        string AccountHolderName;
        int AccountNumber;
        string paymentType;
        string LoginType;
        bool adminTransaction;

    public:

        //getter and setter of account name
        void setAccountName(string AccountName);

        string getAccountName();

        //getter and setter of account number
        void setAccountNumber(int num);

        int getAccountNumber();

        //getter and setter of paymentType
        void setpaymentType(string paytype);

        string getpaymentType();

        //getter and setter of logginType
        void setLogginType(string log);

        string getLogginType();

        //getter and setter of adminTransaction Checker
        void setadminTransaction(bool checker);

        bool getadminTransaction();

        //changeplan function
        void ChangePaymentType(vector<string> lType,login session);
        //save Transaction function
        void save();


};




#endif