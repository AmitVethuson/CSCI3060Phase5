#ifndef ACCDELETE_H
#define ACCDELETE_H
#include <string>
#include <vector>
#include <cstdlib>
#include "login.h"
#include "account.h"


using namespace std;

class accDelete{
	private:
		int dbPosition;
		string aName;
		string loginType;
		string aNumber;

	public:
		void setDbPosition(int dbPosition);
		void setANumber(string aNumber);
		void setAName(string aName);
		int getDbPosition();
		string getANumber();
		string getAName();

		void save(login session);
		void deleteAccount(vector<string> lType,login session, accDelete delAcc);
		void saveLog();

};

#endif
