#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <iostream>
#include <string>
#include <cstdlib>

#include "account.h"

using namespace std;

class withdrawal {
    private: 
        Account transactionAccount;
        string loginType, aName;
        int aNumber;
        float amount;

        void saveLog();
    
    public:
        withdrawal();
        void makeWithdrawal();
        bool setAccountName(string aName, vector<account> type, string loginType);
        bool setAccountNumber(int aNumber, vector<account> type);
        void setAmount(float amount);
};

extern vector<account> adminAccounts;
extern vector<account> standardAccounts;

#endif