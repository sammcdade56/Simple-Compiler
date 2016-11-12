#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <math.h>
#include "SLang.h"
#include<typeinfo>

using namespace std;
//creates machine language interpreter
//takes: vector of commands returns: nothing
SLang::SLang(vector<string> commands){
    for(unsigned int i = 0; i<commands.size();++i){
        vector<string> split = splitIt(commands[i]);
        lineNums.push_back(stoi(split[0]));
        instructions.push_back(split[1]);
        deets.push_back(split[2]);
    }
    miIndex = 0;
    siIndex = 0;
    dIndex = 99;
}


vector<string> SLang::splitIt(string command){
    vector<string> parts;//first part linenum second part instruction third part values
    int firstSpace = 0;
    int secondSpace = 0;
    for(unsigned int i = 0; i<command.size();i++){
        if ((command.at(i)==' ')&&(firstSpace==0)){
            firstSpace = i;
        }
        else if (command.at(i)==' '){
            secondSpace = i;
            break;
        }
    }
    parts.push_back(command.substr(0,firstSpace));
    if(secondSpace == 0){
        parts.push_back(command.substr(firstSpace+1,-1));
        parts.push_back("");
    }
    else{
        parts.push_back(command.substr(firstSpace+1,secondSpace-3));
        parts.push_back(command.substr(secondSpace+1,-1));
    }
    cout<<parts[0]<<parts[1]<<parts[2]<<endl;
    return parts;
}
//increments the interpreter
//takes:nothing returns:0 when done or 1 to continue
int SLang::next(){
    int returnInt =0;

    if(instructions[siIndex]==""){
        returnInt = 1;
    }
    else if(instructions[siIndex] =="rem"){
        siIndex++;
    }
    else if(instructions[siIndex] =="input"){
        mLangI[miIndex] = 1000+dIndex;
        lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
        char var = deets[siIndex].at(0);
        variables.insert(pair<char,int>(var,dIndex));
        siIndex++;
        miIndex++;
        dIndex--;
    }
    else if(instructions[siIndex] =="end"){
        mLangI[miIndex]=4300;
        lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
        siIndex++;
        miIndex++;
    }
    else if(instructions[siIndex] =="print"){
        if (variables.count(deets[siIndex].at(0))==1){
            mLangI[miIndex] = 1100+variables[deets[siIndex].at(0)];
            siIndex++;
            miIndex++;
        }
        else{
            cerr<<"can't print what doesn't exist"<<endl;
            returnInt = 1;
        }
    }
    else if(instructions[siIndex] =="goto"){
        int goLine = stoi(deets[siIndex]);
        if ( lineComp.find(goLine) == lineComp.end() ) {
            mLangI[miIndex] = 4000;
            reCheck.push_back(siIndex);
        }
        else{
            mLangI[miIndex] = 4000 + lineComp[goLine];
        }
        lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
        siIndex++;
        miIndex++;

    }
    else if(instructions[siIndex] =="if"){

    }
    else{
        cerr<<"You entered a bad command and now everything is messed up.  I can't help you now"<<endl;
        returnInt=1;
    }
    return returnInt;
}

void SLang::secondRun(){
    for(unsigned int i = 0; i<reCheck.size();++i){
        if (instructions[reCheck[i]] == "goto"){
            int goLine = stoi(deets[reCheck[i]]);
            int originalLine = lineNums[reCheck[i]];
            mLangI[lineComp[originalLine]] = 4000 + lineComp[goLine];
        }
    }
}
std::vector<int> SLang::returnFinal(){
    vector<int> finalMLang;
    size_t i =0;
    while(mLangI[i]!=0)
    {
       finalMLang.push_back(mLangI[i]);
       i++;
    }
    return finalMLang;
}
