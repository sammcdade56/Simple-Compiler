#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

int main()
{
    string fileName;
    cout<<"Enter the name of your file (without the extension)"<<endl;
    cin>>fileName;
    ifstream fileVar(fileName+".txt", ios::in);
    if (! fileVar ){
        cerr<<"File does not exist"<<endl;
    }


    return 0;
}
