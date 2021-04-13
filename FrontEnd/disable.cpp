#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include "disable.h"
#include "login.h"
#include "account.h"
#include "miscFunctions.h"

using namespace std;

// Basic constructor for the disable class
disable::disable() {}

// This function determines what type of transaction the current session
// is, and updates the private class variable adminTransaction
void disable::setSession(login session) {

    if (session.getLoginType() == "Admin") {
        this->adminTransaction = true;
    }
    else {
        this->adminTransaction = false;
    }
}

// This function allows the admin user to set the account being disabled in a transaction
void disable::setSelectedAccount(vector<string> lType, login session, string accountNum, string name) {
    if (adminTransaction == true) {
        string holderName;
        int accountNumber;

        // If the current session is an admin transaction, the admin user is prompted to input a holder name
        // along with an account number while setting an account to disable.
        cout << "Please enter bank account holder's name:" << endl;
        holderName = name;

        // Seeing if the name exists in the standardAccount vector
        bool foundName = false;
        for (int i = 0; i < standardAccounts.size(); i++) {
            if (holderName == standardAccounts[i].getAccountName()) {
                foundName = true;
                cout << "Valid account holder" << endl;
            }
        }

        // If the name is not found, continue to the next transaction
        if (foundName == false) {
            cout << "Error: Account holder's name could not be found" << endl;
            tChooser(lType, session);
        }

        // If cancelled hasn't been called by the user, continue to enter the user's account number
        if (lType[session.getSessionCounter()] != "cancelDisable") {
            
            cout << "Please enter the account number:" << endl;
            accountNumber = stoi(accountNum);

            // Seeing if the account number exists in the standardAccount vector
            bool foundNum = false;
            for (int i = 0; i < standardAccounts.size(); i++) {
                if ((holderName == standardAccounts[i].getAccountName()) &&
                    (accountNumber == standardAccounts[i].getAccountNumber()) &&
                    foundName == true) {
                    foundNum = true;
                    this->selectedAccount = &standardAccounts[i];
                    cout << "Account number valid" << endl;
                }
            }

            // If the account number is not found, continue to the next transaction
            if (foundNum == false) {
                cout << "Error: Account number is not under the holder’s name" << endl;
                session.updateSessionCounter();
                tChooser(lType, session);
            }
        }
        else {
            cout << "Account disable cancelled" << endl;
            session.updateSessionCounter();
            tChooser(lType,session);
        }
    }
    else {
        cout << "Error: You can only disable an account in admin mode" << endl;
        tChooser(lType, session);
    }
}

// This function allows the user to conduct a disable transaction
void disable::disableAccount(vector<string> lType, login session) {

    cout << "Disable account selected" << endl;

    // Setting the variable adminTransaction to either Standard or Admin,
    // depending on the current session type
    setSession(session);

    // Setting the account that is sending money in the current transaction,
    // if the user hasn't cancelled the transaction
    if (lType[session.getSessionCounter()] != "cancelDisable") {
        string name = lType[session.updateSessionCounter()];
        string account = lType[session.getSessionCounter()];
        setSelectedAccount(lType, session, account, name);
        session.updateSessionCounter();
    }

    // Conducting the disable and updating the account's status, if the user hasn'tcancelled the transaction
    if (lType[session.getSessionCounter()] != "cancelDisable") {
        if (selectedAccount->getAccountNumber() != 0 && selectedAccount->getAccountStatus() == "A" && adminTransaction == true) {
            selectedAccount->setAccountStatus("D");
            cout << "Account successfully disabled" << endl;
            saveLogs();
        }
        else {
            cout << "Account could not be disabled" << endl;
        }
        
        tChooser(lType,session);
    }
    else {
        cout << "Account disable cancelled" << endl;
        session.updateSessionCounter();
        tChooser(lType,session);
    }
}

void disable::saveLogs() {
    fstream stream;
    stream.open("disableLogs.etf", ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "07_" << selectedAccount->getAccountName() << "_"
               << selectedAccount->getAccountNumber() << "_00000.00"
               << "__D" << endl;
    }
    stream.close();
}
