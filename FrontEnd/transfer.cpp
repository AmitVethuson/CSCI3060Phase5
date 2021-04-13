#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include "transfer.h"
#include "login.h"
#include "account.h"
#include "miscFunctions.h"

using namespace std;

// Basic constructor for the transfer class
transfer::transfer() {}

// This function determines what type of transaction the current session
// is, and updates the private class variable adminTransaction
void transfer::setSession(login session) {

    if (session.getLoginType() == "Admin") {
        this->adminTransaction = true;
    }
    else {
        this->adminTransaction = false;
    }
}


// This function allows the user to set the account sending money in a transaction
void transfer::setAccountFrom(vector<string> lType, login session, string accountNum, string name) {
    int accountNumber;
    string holderName;

    // If the current session is an admin transaction, the admin user is prompted to input a holder name
    // along with an account number while setting an account thats sending money. If the current session
    // is a standard transaction, the standard user is only prompted to enter an account number while
    // setting an account thats sending money.
    if (name != "") {
        cout << "Please enter the account holder's name:" << endl;
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
            cout << "Error: Name not found" << endl;
            tChooser(lType, session);
        }

        cout << "Please enter the account number: " << endl;
        accountNumber = stoi(accountNum);

        // Seeing if the account number exists in the standardAccount vector under the holder's name
        bool foundNum = false;
        for (int i = 0; i < standardAccounts.size(); i++) {
            if ((holderName == standardAccounts[i].getAccountName()) &&
                (accountNumber == standardAccounts[i].getAccountNumber()) &&
                foundName == true) {
                foundNum = true;
                this->accountFrom = &standardAccounts[i];
                cout << "Account number valid" << endl;
            }
        }

        // If the account number is not found, continue to the next transaction
        if (foundNum == false) {
            cout << "Error: Account holder’s name does not match with account number" << endl;
            session.updateSessionCounter();
            tChooser(lType, session);
        }
    }
    else {
        cout << "Please enter the account number:" << endl;
        accountNumber = stoi(accountNum);

        // Seeing if the account exists in the standardAccount vector
        bool found = false;
        for (int i = 0; i < standardAccounts.size(); i++) {
            if (accountNumber == standardAccounts[i].getAccountNumber()) {
                found = true;
                this->accountFrom = &standardAccounts[i];
                cout << "Account number valid" << endl;
            }
        }

        // If the account number is not found, continue to the next transaction
        if (found == false) {
            cout << "Error: Account number invalid" << endl;
            tChooser(lType, session);
        }
    }
}

// This function allows the user to set the account receiving money in a transaction
void transfer::setAccountTo(vector<string> lType, login session, string accountNum) {

    int accountNumber;

    cout << "Please enter the account number:" << endl;
    accountNumber = stoi(accountNum);

    // Checking that the sending and receiving accounts are not the same
    if (accountNumber == accountFrom->getAccountNumber()) {
        cout << "Error: Transferring account and receiving account cannot be the same" << endl;
        tChooser(lType, session);
    }
    else {    
        // Seeing if the account exists in the standardAccount vector
        bool found = false;
        for (int i = 0; i < standardAccounts.size(); i++) {
            if (accountNumber == standardAccounts[i].getAccountNumber()) {
                found = true;
                this->accountTo = &standardAccounts[i];
                cout << "Account number valid" << endl;
            }
        }

        // If the account number is not found, continue to the next transaction
        if (found == false) {
            cout << "Error: Account number invalid" << endl;
            tChooser(lType, session);
        }
    }
}

// This function allows the user to set the amount to be transferred in a transaction
void transfer::setAmount(vector<string> lType, login session, string setAmount) {
    float amount;

    cout << "Please enter the amount to transfer: " << endl;
    amount = stof(setAmount);

    // Checking to see if the set amount to transfer is valid. If the amount is invalid,
    // continue to the next transaction
    if (adminTransaction == true  && amount > 0.00) {
        this->transferAmount = amount;
        cout << "Valid amount" << endl;
    }
    else if (adminTransaction == false && amount > 0.00 && amount < 1000.00) {
        this->transferAmount = amount;
        cout << "Valid amount" << endl;
    }
    else if (adminTransaction == false && amount > 1000.00) {
        cout << "Error: Selected transfer amount exceeds the $1000 session transfer limit" << endl;
        tChooser(lType, session);
    }
    else if (amount <= 0.00) {
        cout << "Error: Selected transfer amount must be greater than $0.00" << endl;
        tChooser(lType, session);
    }
    else {
        cout << "Error: Cannot transfer set amount" << endl;
        tChooser(lType, session);
    }
}

// This function allows the user to conduct a transfer transaction
void transfer::conductTransfer(vector<string> lType, login session) {

    cout << "Transfer selected" << endl;

    // Setting the variable adminTransaction to either Standard or Admin,
    // depending on the current session type
    setSession(session);
    
    // Setting the account that is sending money in the current transaction,
    // if the user hasn't cancelled the transaction
    if (lType[session.getSessionCounter()] != "cancelTransfer") {
        if (adminTransaction == true) {
            string name = lType[session.updateSessionCounter()];
            string account = lType[session.getSessionCounter()];
            setAccountFrom(lType, session, account, name);
            session.updateSessionCounter();
        }
        else if (adminTransaction == false){
            setAccountFrom(lType, session, lType[session.updateSessionCounter()], "");
        }
    }

    // Setting the account that is receiving money in the current transaction,
    // if the user hasn't cancelled the transaction
    if (lType[session.getSessionCounter()] != "cancelTransfer") {
        setAccountTo(lType, session, lType[session.updateSessionCounter()]);
    }

    // Setting the amount that is being transferred in the current transaction,
    // if the user hasn't cancelled the transaction
    if (lType[session.getSessionCounter()] != "cancelTransfer") {
        setAmount(lType, session, lType[session.updateSessionCounter()]);
    }

    // Conducting the transfer between the two accounts and updating their balances, if the user hasn't
    // cancelled the transaction and if the transation is between two valid accounts
    if (lType[session.getSessionCounter()] != "cancelTransfer") {
        if (accountTo->getAccountStatus() != "D" && accountFrom->getAccountStatus() != "D") {
            float accountFromBalance = accountFrom->getBalance();
            float accountToBalance = accountTo->getBalance();

            if ((accountFromBalance - transferAmount) >= 0.00 && (accountToBalance + transferAmount) >= 0.00) {
                accountFrom->setBalance(accountFromBalance - transferAmount);
                accountTo->setBalance(accountToBalance + transferAmount);
                cout << "Transfer successful" << endl;
                saveLogs();
            }
            else if ((accountFromBalance - transferAmount) < 0.00 && (accountToBalance + transferAmount) >= 0.00) {
                cout << "Error: Transferring account must have a balance of at least $0.00 after interaction" << endl;
            }
            else if ((accountFromBalance - transferAmount) >= 0.00 && (accountToBalance + transferAmount) < 0.00) {
                cout << "Error: Receiving account must have a balance of at least $0.00 after interaction" << endl;
            }
            else {
                cout << "Error: Transfer unsuccessful" << endl;
            }
        }
        else {
            cout << "Error: One or more of the selected accounts are disabled" << endl;
        }

        tChooser(lType,session);
    }
    else {
        cout << "Transfer cancelled" << endl;
        session.updateSessionCounter();
        tChooser(lType,session);
    }
}

void transfer::saveLogs() {
    fstream stream;
    stream.open("transferLogs.etf", ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "02_" << accountFrom->getAccountName() << "_"
               << accountFrom->getAccountNumber() << "_-" << transferAmount
               << "___"
               
               << endl

               << "02_" << accountTo->getAccountName() << "_"
               << accountTo->getAccountNumber() << "_+" << transferAmount
               << "___" << endl;
    }
    stream.close();
}
