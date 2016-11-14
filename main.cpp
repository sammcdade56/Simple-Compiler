#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "SLang.h"

using namespace std;

int main()
{
    vector<string> simple;
    /*simple.push_back("10 rem this");
    simple.push_back("20 input x");
    simple.push_back("30 input y");
    simple.push_back("40 let x = x + y");
    simple.push_back("50 print x");
    simple.push_back("60 end");*/

    ifstream fileVar;
    fileVar.open("simple.txt", ifstream::in);
    if (!fileVar.is_open()){
        cout << " Cannot open file!" << endl;
    }
    string line;
    while(getline(fileVar,line)){
        simple.push_back(line);
        cout<<line<<endl;
    }

    SLang s(simple);
    int repeatNum = 0;
    while(repeatNum==0){
        repeatNum = s.next();
    }
    s.secondRun();
    vector<string> machine= s.returnFinal();
    for(unsigned int i = 0; i<machine.size();++i){
        cout<<machine[i]<<endl;
    }
    cout<<"data:"<<endl;
    vector<string> data = s.returnData();
    for(unsigned int i = 0; i<data.size();++i){
        cout<<data[i]<<endl;
    }
    return 0;
}
