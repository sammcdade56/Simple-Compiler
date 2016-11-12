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
    instructions.push_back("nomore");
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
        parts.push_back(command.substr(firstSpace+1,command.size()-firstSpace));
        parts.push_back("");
    }
    else{
        parts.push_back(command.substr(firstSpace+1,secondSpace-firstSpace-1));
        parts.push_back(command.substr(secondSpace+1,command.size()-secondSpace-1));
    }
    return parts;
}
//increments the interpreter
//takes:nothing returns:0 when done or 1 to continue
int SLang::next(){
    int returnInt =0;
    if(instructions[siIndex]=="nomore"){
        returnInt = 1;
    }
    else if(instructions[siIndex] =="rem"){
        miIndex--;
    }
    else if(instructions[siIndex] =="input"){
        returnInt =input();
    }
    else if(instructions[siIndex] =="end"){
        returnInt =endIt();
    }
    else if(instructions[siIndex] =="print"){
        returnInt =print();
    }
    else if(instructions[siIndex] =="goto"){
        returnInt =gotoIt(4000,stoi(deets[siIndex]));
        lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
    }
    else if(instructions[siIndex] =="if"){
        returnInt = ifIt();
    }
    else{
        cerr<<"You entered a bad command and now everything is messed up.  I can't help you now"<<endl;
        returnInt=1;
    }
    siIndex++;
    miIndex++;
    return returnInt;
}

int SLang::input(){
    mLangI[miIndex] = 1000+dIndex;
    lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
    char var = deets[siIndex].at(0);
    variables.insert(pair<char,int>(var,dIndex));
    dIndex--;
    return 0;
}
int SLang::endIt(){
    mLangI[miIndex]=4300;
    lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
    return 0;
}
int SLang::print(){
    if (variables.count(deets[siIndex].at(0))==1){
        mLangI[miIndex] = 1100+variables[deets[siIndex].at(0)];
        lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
        return 0;
    }
    else{
        cerr<<"can't print what doesn't exist"<<endl;
        return 1;
    }
}
int SLang::gotoIt(int branchInstr,int goLine){
    if ( lineComp.find(goLine) == lineComp.end() ) {
        mLangI[miIndex] = branchInstr;
        reCheck.insert(pair<int,int>(siIndex,miIndex));
    }
    else{
        mLangI[miIndex] = branchInstr + lineComp[goLine];
    }
    return 0;
}
int SLang::ifIt(){
    int firstV = variables[deets[siIndex].at(0)];
    char op = deets[siIndex].at(2);
    int j;
    for(unsigned int i = 4; i<deets[siIndex].size();i++){
        if(deets[siIndex].substr(i,4)=="goto"){
            j=i;
            break;
        }
    }
    int gotoLine = stoi(deets[siIndex].substr(j+5,deets[siIndex].size()-j-5));
    string notSolved = deets[siIndex].substr(4,j-5);
    //use solver here yay!
    int secondV;//solver will find this!
    lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
    if(notSolved.size()==1){
        secondV = variables[notSolved.at(0)];
    }
    if (op == '='){
        mLangI[miIndex] = 2000 + firstV;
        miIndex ++;
        mLangI[miIndex] = 3100 + secondV;
        miIndex ++;
        gotoIt(4200,gotoLine);
    }
    else if (op == '<'){
        mLangI[miIndex] = 2000 + firstV;
        miIndex ++;
        mLangI[miIndex] = 3100 + secondV;
        miIndex ++;
        gotoIt(4100,gotoLine);
    }
    else if (op == '>'){
        mLangI[miIndex] = 2000 + secondV;
        miIndex ++;
        mLangI[miIndex] = 3100 + firstV;
        miIndex ++;
        gotoIt(4100,gotoLine);
    }
    return 0;
}


void SLang::secondRun(){
    typedef map<int,int>::iterator it_type;
    for(it_type iterator = reCheck.begin(); iterator != reCheck.end(); iterator++) {
        if (instructions[iterator->first] == "goto"){
            int goLine = stoi(deets[iterator->first]);
            mLangI[iterator->second] += lineComp[goLine];
        }
        if (instructions[iterator->first] == "if"){
            string instr = deets[iterator->first];
            int j;
            for(unsigned int i = 4; i<instr.size();i++){
                if(instr.substr(i,4)=="goto"){
                j=i;
                break;
                }
            }
            int goLine = stoi(instr.substr(j+5,instr.size()-j-5));
            mLangI[iterator->second] += lineComp[goLine];
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
