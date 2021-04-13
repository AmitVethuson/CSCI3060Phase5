#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

vector<string> readFile(string file) {
    std::vector<string> vec;
    string line;
    ifstream fin(file);

    if (!fin) cout << "Can not read file: " << file << endl;
    if (fin.is_open()) {
        while (getline(fin,line)) vec.push_back(line); 
    }
    return vec;
}

vector<string> readFile2(string file) {
    std::vector<string> vec;
    string line;
    ifstream fin(file);

    if (!fin) cout << "Can not read file: " << file << endl;
    if (fin.is_open()) {
        while (getline(fin,line)) vec.push_back(line.substr(0,line.size()-1)); 
    }
    return vec;
}

void compareFiles(string expected, string test) {
    std::vector<string> expVec = readFile2(expected);
    std::vector<string> testVec = readFile(test);
    std::vector<bool> ans;

    for (int i=0; i<testVec.size(); i++) {
        if (expVec[i] == testVec[i]) ans.push_back(true);
        else ans.push_back(false);
    }
    
    
    for (int i=0; i<ans.size(); i++) {
        if(ans[i]==true){
        cout <<"True" <<endl;
        }else{
        cout <<"False" <<endl;
        }
    
    }
}

int main(int argc, char *argv[]) { 
    compareFiles(argv[1],argv[2]); 
    }