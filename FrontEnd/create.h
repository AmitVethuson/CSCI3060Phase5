#ifndef CREATE_H
#define CREATE_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class create {
    private:
        Account account;
        float balance;
        string aName, loginType;

        void saveLog():

    public:
        create(vector<string> lType,login session);
        void setAccountName(string aName, string loginType);
        bool setBalance(float balance);
        void createAccount();
}

extern vector<account> adminAccounts;
extern vector<account> standardAccounts;

#endif