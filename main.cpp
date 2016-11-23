#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "SLang.h"

using namespace std;

int main()
{
    //This is the vector that will contain the simple code to get complied
    vector<string> simple;
<<<<<<< HEAD
   
=======
>>>>>>> 389d439a77315890f9c39d752ebcbd5d34babfcf
    //This is the file that contains the simple code that needs to get complied
    ifstream fileVar;
    fileVar.open("simple.txt", ifstream::in);

    //This is a check to ensure that the file works
    if (!fileVar.is_open()){
        cout << " Cannot open file!" << endl;
    }

    //This is a loop that takes the code from the file and puts it into the simple vector
    string line;
    while(getline(fileVar,line)){
        simple.push_back(line);
    }


    SLang s(simple);

    //S.next() returns either 0 or 1.
    int repeatNum = 0;
    while(repeatNum==0){
        repeatNum = s.next();
    }

    s.secondRun();

    array<int, 100> tim = s.returnAll();
    ofstream ofs ("sml.txt", std::ofstream::out);
    for(int i = 0; i < tim.size(); i = i + 1){
        ofs << to_string(tim[i]) + "\n";
    }
    ofs.close();
    return 0;
}
