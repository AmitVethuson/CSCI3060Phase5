#include "paybill.h"
#include "account.h"
#include "login.h"
#include "miscFunctions.h"

using namespace std;

        
        void payBill::setAccountName(string AccountName){this->AccountName = AccountName;};
        //set The account Number
        void payBill:: setAccountNumber(int num){this->AccountNumber = num;};
        //set the loggin type
        void payBill::  setLogginType(string log){this->LoginType = log;};
        //set the Company that will get paid
        void payBill:: setCompany(string company){this->Company = company;};
        //set the amount that will be paid
        void payBill:: setAmount(float amount){this->Amount = amount;};
        //set the account balance
        void payBill:: setBalance(float bal){this->Balance = bal;};

        //get the account name
        string payBill::  getAccountName(){return this->AccountName;};
        //get the account number
        int payBill::getAccountNumber(){return this->AccountNumber;};
        //get the loggin type
        string payBill:: getLogginType(){return this->LoginType;};
        //get the company name that will get paid
        string payBill:: getCompany(){return this->Company;};
        //get the amount that will be paid
        float payBill:: getAmount(){return this->Amount;};
        //get the account balance
        float payBill:: getBalance(){return this->Balance;};



//save transaction 
void payBill::save() {
    fstream stream;
    stream.open("paybillLogs.etf", ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "03_" <<"_"<< getAccountName()<<"_"
               << getAccountNumber()<<"_" << getAmount()<<"_"<< getCompany()<< endl;
    }
    stream.close();
}



void payBill::paybill(vector<string> lType,login session){
    //temporary variables    
    string name;
    int num;
    string log;
    string company;
    float amount;
    int currentAccount;
    bool UserChecker =false;
    log = session.getLoginType();
    setLogginType(log);
    
    //check if logging is admin and ask for Account Name
    if(log=="Admin"){

    
    
    cout <<"Account Name: "<<endl; 
    name = lType[session.updateSessionCounter()];
    for(int i=0;i<adminAccounts.size();i++){
        if (name == adminAccounts[i].getAccountName()){
            currentAccount =i;
            UserChecker =true; 
         
        }
    }
    if(UserChecker ==false){
        cout <<"Error: Account Name not In DataBase"<<endl;
        tChooser(lType,session);
        }
    //cin >> name;
    //there will be a check if account name is in db
    if(UserChecker ==true){
    setAccountName(name);
       //ask for account Number
    cout <<"Account Number: "<<endl; 
    num =stoi(lType[session.updateSessionCounter()]);
    if(adminAccounts[currentAccount].getAccountNumber()!= num){tChooser(lType,session);}
   
    //cin >>num;
    //there will be a check if there is the account number in db
    setAccountNumber(num);

    // ask for Company To whom will be paid
    //if incorrect input exit
    cout <<"Select Company to which the bill is paid:"<<endl;
    cout <<"Type 'EC' for The Bright Light Electric Company" <<endl;
    cout <<"Type 'CQ' for Credit Card Company Q"<<endl;
    cout <<"Type 'FI' Fast Internet, Inc."<<endl; 
    company = lType[session.updateSessionCounter()];
   
    //cin >>company;
    if(company == "EC" || company == "CQ" || company == "FI"){

        setCompany(company);
        
        }else{
            cout <<"Error: Incorrect Company Name"<<endl;
            tChooser(lType,session);
        }


        cout <<"Amount: "<<endl; 
        amount =stof(lType[session.updateSessionCounter()]);
  
        //cin >>amount;
         //check account balance is greater than 0.00 after paying
         if((adminAccounts[currentAccount].getBalance()-amount)>=0.00){
            setAmount(amount);
          
        }else{
            cout<<"Error:Amount is more than Balance"<<endl;
            tChooser(lType,session);
        }
    }
       adminAccounts[currentAccount].setBalance(getBalance() - amount); 
    }
    
    
    
    
    else if (log =="Standard"){    
    //ask for account Number
    cout <<"Account Number: "<<endl; 
    

    num =stoi(lType[session.updateSessionCounter()]);
    for(int i=0;i<standardAccounts.size();i++){
        if (num == standardAccounts[i].getAccountNumber()){
            currentAccount =i;
            UserChecker =true; 
        }
    }
     
    if(UserChecker==false){
        cout <<"Error: Account Name not In DataBase"<<endl;
        tChooser(lType,session);
        }
    //cin >>num;
    //there will be a check if there is the account number in db
    setAccountNumber(num);
  

    // ask for Company To whom will be paid
    //if incorrect input exit
    cout <<"Select Company to which the bill is paid:"<<endl;
    cout <<"Type 'EC' for The Bright Light Electric Company" <<endl;
    cout <<"Type 'CQ' for Credit Card Company Q"<<endl;
    cout <<"Type 'FI' Fast Internet, Inc."<<endl; 

    company = lType[session.updateSessionCounter()];
 
    //cin >>company;
    if(company == "EC" || company == "CQ" || company == "FI"){
        
        setCompany(company);
      
        
        }else{
            cout <<"Error: Incorrect Company Name"<<endl;
            tChooser(lType,session);
        }

    
    //check if loggin is admin so payment can be greater than $2000.00
    
        //if payment is more than $2000.00 exit
        cout <<"Amount: "<<endl; 
        amount =stof(lType[session.updateSessionCounter()]);
        //cin >>amount;
        //account balance is greater than 0.00 after paying
        if(amount <=2000.00 && (standardAccounts[currentAccount].getBalance()-amount)>=0.00){
            setAmount(amount);
           
            

             }else{
                 if(amount >=2000.00){
                 cout<<"Error:Amount is More than $2000.00 limit"<<endl;
                 }else{
                     cout<<"Error:Amount is more than Balance"<<endl;
                 }
                tChooser(lType,session);; 
             }

         

    standardAccounts[currentAccount].setBalance(getBalance() - amount);
    }

    //Removes amount from balance
    

    cout <<"PayBill Succsessfull!"<<endl;
    //save transaction
    save();
    tChooser(lType,session);

    
};




