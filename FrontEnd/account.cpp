#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "account.h"
using namespace std;

account::account(string accountName,string accountPassword, int accountNumber,  float balance, string type, string planType ,string status) {
    this->accountName = accountName;
    this->accountPassword = accountPassword;
    this->accountNumber = accountNumber;
    this->balance = balance;
    this->type = type;
    this->planType= planType;
    this->status = status;
}
account::account() {}

/*
account::account(int accountNumber,string accountPassword, float balance) {
    this->accountNumber = accountNumber;
    this->accountPassword = accountPassword;
    this->balance = balance;
    this->type = "Admin";
}
*/


