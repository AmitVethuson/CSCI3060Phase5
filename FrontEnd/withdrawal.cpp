#include "withdrawal.h"
#include "account.h"
#include "login.h"
#include "miscFunctions.h"

using namespace std;


withdrawal::withdrawal() {
    string loginType;

    if (session.getLoginType() == "Admin") loginType = "Admin";
    else loginType = "Standard";

    setAccountName(lType[session.getSessionCounter()], type, loginType);
    setAccountNumber(lType[session.getSessionCounter()],type);
    setAmount(lType[session.getSessionCounter()]);
    makeWithdrawal();
    saveLog();
}

void withdrawal::makeWithdrawal() {
    float current = transactionAccount.getBalance(); 
    transactionAccount.setBalance(current + amount);
}

/*
 * query DB for account names matching aName returning to *aName
 * cannot include for as of now there is no DB
 */
bool withdrawal::setAccountName(string aName, vector<account> type, string loginType) {
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

bool withdrawal::setAccountNumber(int aNumber, vector<account> type) {
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

void withdrawal::setAmount(float amount) {
    this->amount = amount;
    cout << "Valid" << endl;
}

void withdrawal::saveLog() {
    fstream stream;
    stream.open("withdrawalLogs.etf", ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "01_" << loginType << transactionAccount.getAccountName() 
               << transactionAccount.getAccountNumber() << amount << endl;
    }
    close(file);
}