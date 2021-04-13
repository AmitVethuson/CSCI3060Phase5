#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <vector>

using namespace std;

class account {
    private:
        string accountName, type;
        string accountPassword;
        int accountNumber;
        float balance;
        string planType;
        string status;

    public:
        vector <string> accountArrays;
        account(string accountName,string accountPassword, int accountNumber, float balance, string type,string payType, string status);
        account();
        //account(int accountNumber,string accountPassword, float balance);
        void setAccountName(string accountName) { this->accountName = accountName; }
        void setAccountPassword(string accountPassword){ this->accountPassword = accountPassword;}
        void setAccountNumber(int accountNumber) { this->accountNumber = accountNumber; }
        void setBalance(float balance) { this->balance = balance; }
        void setAccountStatus(string status) { this->status = status; }
        void setType(string type) { this->type = type; }
        void setPlanType(string planType){this->planType = planType;}
        string getAccountName() { return this->accountName; }
        string getAccountPassword(){return this->accountPassword;}
        string getType() { return type; }
        string getPlanType(){return planType;}
        int getAccountNumber() { return this->accountNumber; }
        float getBalance() { return this->balance; }
        string getAccountStatus() { return this->status; }


};

extern vector<account> adminAccounts;
extern vector<account> standardAccounts;

#endif
