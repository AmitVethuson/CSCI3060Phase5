#include <iostream>
#include <string>
#include <cstdlib>

#include "account.h"
#include "deposit.h"
#include "login.h"
#include "miscFunctions.h"

using namespace std;

deposit::deposit(vector<account> lType, login session) {
    //if admin type = adminAccounts else stdAccounts
    string loginType;

    if (session.getLoginType() == "Admin") loginType = "Admin";
    else loginType = "Standard";

    setAccountName(lType[session.getSessionCounter()], lType, loginType);
    setAccountNumber(lType[session.getSessionCounter()],lType);
    setAmount(lType[session.getSessionCounter()]);
    makeDeposit();
    saveLog();
}

void deposit::makeDeposit() {
    float current = transactionAccount.getBalance(); 
    transactionAccount.setBalance(current - amount);
}

/*
 * query DB for account names matching aName returning to *aName
 * cannot include for as of now there is no DB
 */
bool deposit::setAccountName(string aName, vector<account> type, string loginType) {
    for(int i=0; i<type.size(); i++) {
        if (aName == type[i].getAccountName()) {
            this->aName = aName; 
            this->loginType = loginType;
            cout << "Valid, enter Account Number" << endl;
            return true;
    }
    cout << "Invalid" << endl;
    return false; 
}

bool deposit::setAccountNumber(int aNumber, vector<account> type) {
    for(int i=0; i<type.size(); i++) {
        if (aName == type[i].getAccountNumber()) {
            this->aNumber = aNumber;
            cout << "Valid, enter amount" << endl;
            return true;
        }
    }
    cout << "Invalid" << endl;
    return false;
}

void deposit::setAmount(float amount) {
    this->amount = amount;
    cout << "Valid" << endl;
}

void deposit::saveLog() {
    fstream stream;
    stream.open("depositLogs.etf", ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "04_" << loginType << transactionAccount.getAccountName() 
               << transactionAccount.getAccountNumber() << amount << endl;
    }
    close(file);
}