#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

class login{
	private:
		int sessionCounter;
		int dbPosition;
		string lType;
		string aName;
		string aPassword;
		string isCorrect;
		string aNumber;
	public:
		void setSessionCounter(int sessionCounter);
		void setDbPosition(int dbPosition);
		void setLoginType(string lType);
		void setANumber(string aNumber);
		void setAPassword(string aPassword);
		void setAName(string aName);

		int getSessionCounter();
		int getDbPosition();
		string getLoginType();
		string getANumber();
		string getAPassword();
		string getAName();
		

		int updateSessionCounter();
		void loginType(vector<string> lType,login session);
		void adminLogin(vector<string> lType,login session);
		void standardLogin(vector<string> lType,login session);
		bool standardVerification(login session);
		bool adminVerification(login session);


};

#endif  