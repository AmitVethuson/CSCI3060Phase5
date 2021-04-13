#ifndef TRANSFER_H
#define TRANSFER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include "login.h"
#include "account.h"
#include "miscFunctions.h"

using namespace std;

class transfer {
    private:
        // Private Variables
        int transactionNumber;
        account *accountFrom;
        account *accountTo;
        bool adminTransaction;
        float transferAmount;

        // Private Functions
        void saveLogs();

    public:
        transfer();
        void setSession(login session);
        void setAccountFrom(vector<string> lType, login session, string accountNum, string name);
        void setAccountTo(vector<string> lType, login session, string accountNum);
        void setAmount(vector<string> lType, login session, string setAmount);
        void conductTransfer(vector<string> lType, login session);
};


#endif  