#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "SLang.h"

using namespace std;

int main()
{
    string fileName;
    vector<string> simple;
    simple.push_back("rem this");
    simple.push_back("input x");
    simple.push_back("print x");
    simple.push_back("end");

    SLang s(simple);
    int repeatNum = 0;
    while(repeatNum==0){
        repeatNum = s.next();
    }

    return 0;
}
