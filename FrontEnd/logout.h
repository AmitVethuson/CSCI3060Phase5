#ifndef LOGOUT_H
#define LOGOUT_H

#include <vector>
#include "login.h"

using namespace std;

class logout{
public:
	void accLogout(vector<string> lType,login session);
    void save(login session);
	

};
#endif