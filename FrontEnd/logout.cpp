#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "logout.h"
#include "login.h"
#include "account.h"

using namespace std;

void logout::accLogout(vector<string> lType,login session){
    //Checks to see if the next part of the script is equal to white space
    //If its true then itll recall loginType(This is so when a user needs to
    //relog they can easily do so)
    if (lType[session.getSessionCounter()+1] != "") {
        cout << "Logout Successful" << endl;
        session.loginType(lType,session);
        
    }
    else {//If there is nothing after the Login part in a Script the code ends
        cout << "Logout Successful " << endl;
        exit(0);
    }
}


void logout::save(login session) {
    fstream stream;
    stream.open("logoutLogs.etf", ios::out);
    if (!stream) { exit(1); }
    else {
        stream << "00_"<< session.getAName()<<"_"<< session.getANumber()<<"_" <<"00000000"<<"__"<<endl;
    }
    stream.close();
}