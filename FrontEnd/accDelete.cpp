#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "login.h"
#include "account.h"
#include "accDelete.h"
#include "miscFunctions.h"
#include "accDelete.h"


using namespace std; 

//Setters function for multiple variables
void accDelete::setDbPosition(int dbPosition){
	 this->dbPosition = dbPosition;
}

void accDelete::setANumber(string aNumber){

	this->aNumber = aNumber;
};

void accDelete::setAName(string aName){
	this->aName = aName;
};

//Getter functions for multiple variables
int accDelete::getDbPosition(){
	return this->dbPosition;
}


string accDelete::getANumber(){
	return this->aNumber;
};

string accDelete::getAName(){
	return this->aName;
};



void accDelete::deleteAccount(vector<string> lType,login session, accDelete delAcc){
	string aName;
	string aNumber;
	//Checks to see ifthe session is an admin session
	if(session.getLoginType() == "Admin"){
		//It will take in the user input and store the inputs 
		cout << "Enter Account Holders Name"<< endl;
		aName = lType[session.updateSessionCounter()];
		delAcc.setAName(aName);
		cout << "Enter Account Number" << endl;
		aNumber =lType[session.updateSessionCounter()];
		delAcc.setANumber(aNumber);
		bool verify = false;
		//Runs through the account db to check if an account exists, if true it sets verify to true
		for(int i =0; i<standardAccounts.size();i++){
			if(stoi(delAcc.getANumber())==standardAccounts[i].getAccountNumber()){

				delAcc.setDbPosition(i);
				verify = true;

			}			


		}
		//If verify is true then itll allow the account to be deleted if its false then the acc
		//was wrong or never existed
		if(verify==true){
			int temp = delAcc.getDbPosition();
			if(delAcc.getAName()==standardAccounts[temp].getAccountName()){
				cout<<"Verification Successful"<<endl;
				standardAccounts.erase(standardAccounts.begin()+temp);
				cout<<"Account Successfully Deleted"<<endl;
			}else{
				cout<<"Error: Account holder name does not match"<<endl;
			}
		}else{
			cout <<"Error: Account does not exist"<<endl;
		}
		save(session);
		tChooser(lType,session);

	}else {
		exit(0);
	}
};


void accDelete::save(login session) {
    fstream stream;
    stream.open("deleteLogs.etf", ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "06_"<< session.getAName()<<"_"<< session.getANumber()<<"_" <<"00000000"<<"__"<<endl;
    }
    stream.close();
}