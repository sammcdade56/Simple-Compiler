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

    ifstream fileVar;
    fileVar.open("simple.txt", ifstream::in);
    if (!fileVar.is_open()){
        cout << " Cannot open file!" << endl;
    }
    string line;
    while(getline(fileVar,line)){
        simple.push_back(line);
    }

    SLang s(simple);
    int repeatNum = 0;
    while(repeatNum==0){
        repeatNum = s.next();
    }
    s.secondRun();
    array<int, 100> tim = s.returnAll();
    ofstream ofs ("test.txt", std::ofstream::out);
    for(int i = 0; i < tim.size(); i = i + 1){
        ofs << to_string(tim[i]) + "\n";
    }
    ofs.close();
    return 0;
}
