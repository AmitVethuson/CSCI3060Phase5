#include "changeplan.h"
#include "account.h"
#include "login.h"
#include "miscFunctions.h"

using namespace std;

//getter and setter of account name
        void changePlan:: setAccountName(string AccountName){this->AccountHolderName = AccountName;}

        string changePlan:: getAccountName(){return this->AccountHolderName;}

        //getter and setter of account number
        void changePlan:: setAccountNumber(int num){this->AccountNumber = num;}

        int changePlan:: getAccountNumber(){return this->AccountNumber;}

        //getter and setter of paymentType
        void changePlan:: setpaymentType(string paytype){this->paymentType = paytype;}

        string changePlan:: getpaymentType(){return this->paymentType;}

        //getter and setter of logginType
        void changePlan:: setLogginType(string log){this->LoginType = log;}

        string changePlan:: getLogginType(){return this->LoginType;}

        //getter and setter of adminTransaction Checker
        void changePlan:: setadminTransaction(bool checker){this->adminTransaction = checker;}

        bool changePlan:: getadminTransaction(){return this->adminTransaction;}






void changePlan::ChangePaymentType(vector<string> lType,login session){
    //temporary variables
    string name;
    int num;
    string paytype;
    string log;
    bool Adminchecker;
    int currentAccount;
    bool ValidUser=false;
    bool ValidInput =false;

    //get the login type
    log = session.getLoginType();
    setLogginType(log);
    //cin >>log;
    //check if admin
    if(log == "Admin"){
        Adminchecker = true;
    }else{
        Adminchecker = false;
    }
    
    //set loggin type
    setadminTransaction(Adminchecker);

    //check if admin and continue
    if(getadminTransaction() == true){
          
        cout <<"Account Name: "<<endl;
        name = lType[session.updateSessionCounter()];
       
        //cin >>name;
        //check if name is in DB
        for (int i=0;i<adminAccounts.size();i++){
            if(name == adminAccounts[i].getAccountName()){
                currentAccount= i;
                ValidUser =true;
            }
        }

        if(ValidUser==false){
            cout << "Error: Account Name Not in DataBase"<<endl;
            tChooser(lType,session);
            }
        //there will be a check to see if account name is in db
        setAccountName(name);
    

    //ask for account Number
        cout <<"Account Number: "<<endl; 
        num =stoi(lType[session.updateSessionCounter()]);
     
        //cin >>num;
        //check if account Number is in DB
        if(num != adminAccounts[currentAccount].getAccountNumber()){tChooser(lType,session);}
     //here there will be a check to see if the account number is in the db   
        setAccountNumber(num);

        //ask for change payment plan
        cout<<"Change payment Plan: "<<endl;
        cout<<"Type 'SP' for Student Payment Plan"<<endl;
        cout<<"Type 'NP' for Non-Student Payment Plan"<<endl;
        //cin >>paytype;
        paytype = lType[session.updateSessionCounter()];
      
        //check if correct inputs
        if(paytype=="SP" || paytype=="NP"){
            ValidInput = true;
        }
        if(ValidInput==false){
            cout<< "Error: Incorrect payment plan"<<endl;
            tChooser(lType,session);
            }
        setpaymentType(paytype);
        adminAccounts[currentAccount].setPlanType(getpaymentType());
        

        cout <<"Transaction Succsessful!"<<endl;



        // save transaction
        save();
        tChooser(lType,session);

    //ic not admin exit 
    }else{
        cout <<"Error: User lacks permissions to access this function"<<endl;
        tChooser(lType,session);
    }
    
    
}

//save transaction 
void changePlan::save() {
    fstream stream;
    stream.open("changeplanLogs.etf", ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "08_"  << getAccountName() <<"_"
               << getAccountNumber()<<"_" << "00000000"<<"_"<< getpaymentType()<< endl;
    }
    stream.close();
    
}


