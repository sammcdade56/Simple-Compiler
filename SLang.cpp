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
        instructions.push_back(split[0]);
        rest.push_back(split[1]);
    }
    miIndex = 0;
    siIndex = 0;
    dIndex = 99;
}


vector<string> SLang::splitIt(string command){
    vector<string> words;
    for(unsigned int i = 0; i<command.size();++i){
        if (command.at(i)==' '){
            words.push_back(command.substr(0,i));
            words.push_back(command.substr(i+1,-1));
            break;
        }
    }
    if(words.size() == 0){
        words.push_back(command);
        words.push_back("");
    }
    return words;
}
//increments the interpreter
//takes:nothing returns:0 when done or 1 to continue
int SLang::next(){
    int returnInt =0;
    if(instructions[siIndex] =="rem"){
        siIndex++;
    }
    else if(instructions[siIndex] =="input"){
        mLangI[miIndex] = 1000+dIndex;
        siIndex++;
        char var = rest[siIndex].at(0);
        variables.insert(pair<char,int>(var,dIndex));
    }
    else if(instructions[siIndex] =="end"){
        returnInt =1;
    }
    else if(instructions[siIndex] =="print"){
        if (variables.count(rest[siIndex].at(0))==1){
            mLangI[miIndex] = 1100+variables[rest[siIndex].at(0)];
            siIndex++;
        }
        else{
            cerr<<"can't print what doesn't exist"<<endl;
            returnInt = 1;
        }
    }
    else{
        cerr<<"You entered a bad command and now everything is messed up.  I can't help you now"<<endl;
        returnInt=1;
    }
    return returnInt;
}
std::vector<int> SLang::returnFinal(){
    vector<int> finalMLang;
    size_t i =0;
    while(mLangI[i]!=nullptr)
    {
        finalMLang.push_back(mLangI[i]);
        i++;
    }
    return finalMLang;
}
