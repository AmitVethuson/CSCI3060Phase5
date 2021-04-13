#include "create.h"
#include "account.h"
#include "login.h"
#include "miscFunctions.h"

using namespace std;

void create::setAccountName(string aName, string loginType) {
    this->aName = aName;
    this->loginType = loginType;
}

bool create::setBalance(float balance) {
    if (balance < 10000) {
        cout << "Invalid" << endl;
        return false;
    }
    this->balance = balance;
    return true;
}

void create::createAccount(vector<string> lType, login session) {
    int newID = rand() % 100000000;
    /* 
     * This is where a scan through the DB to check for 
     * a matching accountID would take place
     */
    bool uniqueID = false;
    while (!uniqueID) {
        for(int i=0; i<adminAccounts.size(); i++){
            if (name == adminAccounts[i].getAccountNumber()) uniqueID = false; 
        }
        uniqueID = true;
    }

    account = new Account(aName, newID, balance);
    //Add account to DB
}

create::create(vector<string> lType,login session) {
    string log = session.getLoginType();
    if (log != "Admin") {
        cout << "Invalid" << endl;
        return;
    }
    setAccountName(lType[session.getSessionCounter()]);
    setBalance(lType[session.getSessionCounter()]);
    createAccount(lType, session);
    saveLog();
}

void create::saveLog() {
    fstream stream;
    stream.open("createLogs.etf", ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "05_" << loginType << account.getAccountName() 
               << account.getAccountNumber() << balance << endl;
    }
    close(file);
}