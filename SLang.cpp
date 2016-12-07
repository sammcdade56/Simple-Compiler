#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <math.h>
#include <stack>
#include <queue>
#include <locale>
#include <typeinfo>
#include <algorithm>
#include "SLang.h"


using namespace std;
//creates machine language interpreter
//takes: vector of commands returns: nothing
SLang::SLang(vector<string> commands){
    vector<int>::iterator it;
    for(unsigned int i = 0; i<commands.size();++i){
        //This tries to split the commands into the line Number, instructions, and deets
	//Fails if there is no numeric line number
		vector<string> split = splitIt(commands[i]);
        	if(isDigit(split[0])){
			//This checks to make sure the line number is no a repeat
			it = find (lineNums.begin(), lineNums.end(), stoi(split[0]));
			if (it == lineNums.end()){
				lineNums.push_back(stoi(split[0]));
			}
			else{
				cerr << "You have a duplicate Line Number at line " << i + 1 << endl;
			}
		}
		else{
			cerr << "Your line number isn't correct at line " << i + 1 << endl;
			exit(0);
		}
        	instructions.push_back(split[1]);
        	deets.push_back(split[2]);
    }
    for(unsigned int i = 0; i < mLangI.size(); i++){
        mLangI[i] = 0;
    }
    instructions.push_back("nomore");
    miIndex = 0;
    siIndex = 0;
    dIndex = 99;
}

//Takes a string called command as an arugment
//Splits this string into the base parts. Then, it removes any white space found
//Returns an string vector called parts that holds all none white space parts of the string command
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
	try{
        	returnInt = gotoIt(4000,stoi(deets[siIndex]));
        	lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
	}
    	catch(exception& e){
		cerr<< "You are trying to goto nothing" << endl;
		exit(0);
	}
    }
    else if(instructions[siIndex] =="if"){
        returnInt = ifIt();
    }
    else if(instructions[siIndex] =="let"){
        returnInt = let();
    }
    else{
        cerr<<"You entered a bad command and now everything is messed up.  I can't help you now"<<endl;
        returnInt=1;
    }
    siIndex++;
    miIndex++;
    return returnInt;
}
//Generates the sml version of the code for the input commnad
//Returns an int equal to zero
int SLang::input(){
    if(isDigit(string(1,deets[siIndex][0]))){
	cerr << "You tried to assign a number as variable" << endl;
	exit(0);
    }
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
//This method generates the machine langague code for the print command in the simple language
//It fails if there is nothing to print or a literal is trying to be printed
int SLang::print(){
	if(deets[siIndex].length() ==0){
		cerr << "You do not have anything after your print line" << endl;
		exit(0);

	}
	if(!isDigit(deets[siIndex])){
		if(variables.count(deets[siIndex].at(0))==0){
			variables.insert(pair<char,int>(var,dIndex));
			dIndex--;		
		}
		mLangI[miIndex] = 1100+variables[deets[siIndex].at(0)];
        	lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
        	return 0;
	}
	else{
		cerr << "You are trying to print a literal" << endl;
		exit(0);
	}
}
//Generates the sml code for the goto command
//Returns a zero int
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
//Generates the sml code for the if command
//Returns a zero int if it is fine
//Reutrns a one int if it is not fine
int SLang::ifIt(){
    int firstV = variables[deets[siIndex].at(0)];
    int len;
    if(deets[siIndex].at(3)==' '){
        len = 1;
    }
    else{
        len = 2;
    }
    string op = deets[siIndex].substr(2,len);
    int j;
    for(unsigned int i = 4; i<deets[siIndex].size();i++){
        if(deets[siIndex].substr(i,4)=="goto"){
            j=i;
            break;
        }
    }
    int gotoLine = stoi(deets[siIndex].substr(j+5,deets[siIndex].size()-j-5));
    string notSolved = deets[siIndex].substr(2+len,j-5);
    int secondV;//solver will find this!
    lineComp.insert(pair<int,int>(lineNums[siIndex],miIndex));
    if(notSolved.size()==1){
        secondV = variables[notSolved.at(0)];
    }
    else{
        secondV = solve(notSolved);
    }
    if (op == "==" || op == ">=" || op == "<="){
        mLangI[miIndex] = 2000 + firstV;
        miIndex ++;
        mLangI[miIndex] = 3100 + secondV;
        miIndex ++;
        gotoIt(4200,gotoLine);
    }
    else if (op == "<" || op == "<="){
        mLangI[miIndex] = 2000 + firstV;
        miIndex ++;
        mLangI[miIndex] = 3100 + secondV;
        miIndex ++;
        gotoIt(4100,gotoLine);
    }
    else if (op == ">" || op == ">="){
        mLangI[miIndex] = 2000 + secondV;
        miIndex ++;
        mLangI[miIndex] = 3100 + firstV;
        miIndex ++;
        gotoIt(4100,gotoLine);
    }
    else if (op == "!="){
        mLangI[miIndex] = 4100 + miIndex + 2;
        miIndex ++;
        gotoIt(4000,gotoLine);
    }
    else{
        cerr<<"You have invalid expression"<<endl;
        return 1;
    }
    return 0;
}
//Handels the simple command let
//Converts this into the proper sml code for that command
//Returns an int of zero
int SLang::let(){
    string eval = deets[siIndex].substr(4,deets[siIndex].size()-4);
    for(int i = 0; i < eval.length(); i++){
	string bob = string(1, eval[i]);
	if(isDigit(bob)){
		cerr << "You have a number in your let expression" << endl;
		exit(0);
	}
    }
    lineComp.insert(pair<int,int>(siIndex,miIndex));
    int loc = solve(eval);
    char var = deets[siIndex].at(0);
    if(isDigit(string(1,var))){
	cerr << "You have a number in your let expression" << endl;
	exit(0);
    }
    if(variables.count(var)==0){
        variables.insert(pair<char,int>(var,dIndex));
        dIndex--;
    }
    mLangI[miIndex]=2000+loc;
    miIndex++;
    mLangI[miIndex]=2100+ variables[var];
    return 0;
}
//Takes a string eval as in input
//Must be in proper infix order with a space inbetween each opertor and operand
//Turns this string into a post fix expression by calling infixRet
//Converts the post fix expression into the proper sml code version
//Returns an int of the data index
int SLang::solve(string eval){
    vector<char> infixed= infixRet(eval);
    locale loc;
    vector<string> doOps;
    for(int i = 0; i<infixed.size();i++){
        if((isdigit(infixed[i],loc))&&(variables.count(infixed[i])==0)){
            mLangI[dIndex] = infixed[i] - 48;//numbers in ascii, 0 is 48
            variables.insert(pair<char,int>(infixed[i],dIndex));
            dIndex--;
        }
        else if((isalpha(infixed[i],loc))&&(variables.count(infixed[i])==0)){
            variables.insert(pair<char,int>(infixed[i],dIndex));
            dIndex--;
        }	
        if((isdigit(infixed[i],loc))||(isalpha(infixed[i],loc))){
            doOps.push_back(to_string(variables[infixed[i]]));
        }
        else{
            string str(1,infixed[i]);
            doOps.push_back(str);
        }
    }
    int it=0;
    
    while(doOps.size()>1){
	//cerr << doOps.end() << endl;
	if(!isOp(doOps[doOps.size()-1])){
		cerr << "You do not have enough operands" << endl;
		exit(0);
	}
	 if((doOps[it]=="+")||(doOps[it]=="-")||(doOps[it]=="*")||(doOps[it]=="/")){
	    mLangI[miIndex] = 2000+ stoi(doOps[it-2]);
            miIndex++;
            if (doOps[it]=="+"){
                mLangI[miIndex] = 3000+stoi(doOps[it-1]);
            }
            else if (doOps[it]=="-"){
                mLangI[miIndex] = 3100+stoi(doOps[it-1]);
            }
            else if (doOps[it]=="*"){
                mLangI[miIndex] = 3200+stoi(doOps[it-1]);
            }
            else if (doOps[it]=="/"){
                mLangI[miIndex] = 3300+stoi(doOps[it-1]);
            }
            miIndex++;
            mLangI[miIndex] = 2100+dIndex;
            miIndex++;
            doOps.erase(doOps.begin()+it-1);
            doOps.erase(doOps.begin()+it-1);
            doOps[it-2] = to_string(dIndex);
            it = 0;
            dIndex--;
        }
        it++;
    }
    return dIndex+1;
}
//This is the second pass over the code to tie up loose ends during the conversion
//It finishes off the goto command by giving it a line number to point to
void SLang::secondRun(){
    typedef map<int,int>::iterator it_type;
    for(it_type iterator = reCheck.begin(); iterator != reCheck.end(); iterator++) {
        if (instructions[iterator->first] == "goto"){
            int goLine = stoi(deets[iterator->first]);

	if(find(lineNums.begin(), lineNums.end(), goLine) != lineNums.end()) {
	
	} else {
     		cerr <<"Your goto line is to a line number that doesn't exist" << endl;
		exit(0);
	}

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
	if(find(lineNums.begin(), lineNums.end(), goLine) != lineNums.end()) {
	
	} else {
     		cerr <<"Your goto line is to a line number that doesn't exist" << endl;
		exit(0);
	}

            mLangI[iterator->second] += lineComp[goLine];
        }
    }
}
//Takes a string infix as an input
//This string must be an infix expresion with each item seperated by a space I.E. ( 3 + 5 ) * ( 3 - 5 )
//It converts this into the proper post fix version of this expresion I.E. 3 5 + 3 5 - *
//Returns a vecotor of characters that stores the post fix expression
vector<char> SLang::infixRet(string infix){
    stack<string> processingStack;
	queue<string> postFixStack;
	map<string, int> bob;
	bob["+"] = 1;	bob["-"] = 1;	bob["*"] = 2;	bob["/"] = 2;	bob["("] = 0;
	string ops = "+-*/";
	for (unsigned int i = 0; i<infix.length(); i = i + 1){
		locale loc;
		char p =  infix[i];
		string g = string(1,p);
 		if(isdigit(p, loc)){
			postFixStack.push(g);
		}
		if(isalpha(p, loc)){
			postFixStack.push(g);
		}
		if(g.compare("(") == 0){
			processingStack.push(g);
		}
		if(ops.find(g) != string::npos){
			bool highPrecedent = true;
			while(processingStack.size() > 0 && highPrecedent){
				string red = processingStack.top();
				if(bob[red] >= bob[g]){
					postFixStack.push(processingStack.top());
					processingStack.pop();
				}
				else{
					highPrecedent = false;
				}
			}
			processingStack.push(g);
		}
		if(g.compare(")") == 0){
			bool isFound = false;
			while(processingStack.size() > 0 and !isFound){
				string red = processingStack.top();
				if(red != "("){
					postFixStack.push(processingStack.top());
					processingStack.pop();
				}else{
					processingStack.pop();
					isFound = true;
				}
			}
			if(!isFound){
				cerr << "You are missing a paranthesis somewhere in your program. GoodBye." << endl;
}
		}

	}
	while(!processingStack.empty()){
		if(processingStack.top() != "("){
			postFixStack.push(processingStack.top());
		}
		processingStack.pop();
	}
	vector<char> results;
	while(!postFixStack.empty()){
        results.push_back(postFixStack.front().at(0));
		postFixStack.pop();
	}
	return results;
}

//Returns a string vector that contains all the commands for the sml file in the format Line number:Command
vector<string> SLang::returnFinal(){
    vector<string> finalMLang;
    for(int i = 0; i<miIndex-1;i++)
    {
       finalMLang.push_back(to_string(i) + ": " + to_string(mLangI[i]));
    }
    return finalMLang;
}
//Returns a string vector containg the literals needed for the sml code
vector<string> SLang::returnData(){
    vector<string> finalData;
    for(int i = 99; i>dIndex;i--)
    {
       finalData.push_back(to_string(i) + ": " + to_string(mLangI[i]));
    }
    return finalData;
}
//Returns an array that contains the sml code translation
array<int,100> SLang::returnAll(){
    return mLangI;
}

//Takes a string t and returns true if T is a digit and false is T isn't a digit
bool SLang::isDigit(string t){
	char* p;
	strtol(t.c_str(), &p, 10);
	return *p == 0;
}
//Takes a string t and returns true if t is a an operator and false if it is not
bool SLang::isOp(string t){
	string ops = "*-+/";
	if (ops.find(t) != string::npos) {
		return true;
	}
	else{
		return false;
	}
}

