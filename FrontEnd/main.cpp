#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "account.h"
#include "login.h"
#include <sstream>
#include <cstring>

using namespace std;

// Global variables that keep track of all the bank accounts
vector<account> adminAccounts;
vector<account> standardAccounts;

// vector<string> loginType(std::vector<string> lType){
//     cout << "Select Session Type: Admin or Standard"<< endl;
//     cout<< lType[0];
//     if(lType[0] == "Admin"){
//         //setLoginType(lType);
//         // adminLogin(userInput);
//         cout << "Admin" << endl;
//     }else if(lType[0] == "Standard"){
//         //setLoginType(lType);
//         // standardLogin(userInput);
//     }else{
//         exit(0);
//     }
//     return lType;
// };



// A function that reads information from a file and saves it in a string vector
vector<string> readFile(string file) {
    std::vector<string> vec;
    string line;
    ifstream fin(file);
    if (!fin) cout << "Can not read file: " << file << endl;
    if (fin.is_open()) {
        while (getline(fin,line)) vec.push_back(line.substr(0,line.size()-1)); 
    }

    return vec;
}

int main(int argc, char *argv[]) { 
    //We need to create an input to take in the command line e.g bank-atm loginAccount1.txt transactionLoginAccount.Atf...
    // compareFiles("base.txt", "second.txt");
    
    // A string vector that contains the current script's commands
    std::vector<string> testVec = readFile(argv[1]);

    // A string vector that contains all the current bank account information from the
    // bank account file: bankAccounts.txt
    std::vector<string> testAccounts = readFile(argv[2]);

    // Looping through all the accounts in the testAccounts vector and converting them to
    // account objects. They are then pushed to external global account vectors so every
    // class has access to the accounts
    for (int i = 0; i < testAccounts.size(); i++) {
        
        // Using stringstream to parse each line by the commas and save the account information
        // in a string vector named accountInfoVec
        std::istringstream parseAccountInfo(testAccounts[i]);
        std::string token;
        std::vector<string> accountInfoVec;
        while(getline(parseAccountInfo, token, ',')) {
            accountInfoVec.push_back(token);
        }
        
        // Creating a new account based on the parsed information from accountInfoVec
        account newAccount(accountInfoVec[0], accountInfoVec[1],
                           stoi(accountInfoVec[2]), stof(accountInfoVec[3]),
                           accountInfoVec[4], accountInfoVec[5],accountInfoVec[6]);

        // Determining whether the new account should be in the adminAccounts account
        // vector or the standardAccounts account vector
        if (newAccount.getType() == "Admin") {
            adminAccounts.push_back(newAccount);
        }
        else {
            standardAccounts.push_back(newAccount);
        }

    }

    // Creating a new session when the program starts
    login session;
    session.setSessionCounter(0);

    session.loginType(testVec,session);



    return 0;
}