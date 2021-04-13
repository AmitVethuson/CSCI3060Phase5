#ifndef DISABLE_H
#define DISABLE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include "login.h"
#include "account.h"
#include "miscFunctions.h"

using namespace std;

class disable {
    private:

        // Private Variables
        int transactionNumber;
        bool adminTransaction;
        account *selectedAccount;

        // Private Functions
        void saveLogs();
    
    public:
        disable();
        void setSession(login session);
        void setSelectedAccount(vector<string> lType, login session, string accountNum, string name);
        void disableAccount(vector<string> lType, login session);
};


#endif  