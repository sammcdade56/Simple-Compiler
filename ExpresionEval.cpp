#include <iostream>
#include <string> 
#include <map>
#include <stack>
#include <queue>
#include <locale>

using namespace std;

int main(){
	string infix;
	stack<string> processingStack;
	queue<string> postFixStack;
	string letters = "abcdefghigklmnopqrstuvwxyz";
	string digits = "1234567890";
	map<string, int> bob;
	bob["+"] = 1;	bob["-"] = 1;	bob["*"] = 2;	bob["/"] = 2;	bob["("] = 0;
	string ops = "+-*/";
	cout << "What I truly crave is an  inFix Expresion! Give me one Now!" << endl;
	getline(cin,infix);
	cout << infix << endl;
	cout << infix.length() << endl;
	for (int i = 0; i<infix.length(); i = i + 1){
		locale loc;
		char p =  infix[i];
		cout << p << endl;
		string g = string(1,p);
		cout << g << endl;
 		if(isdigit(p, loc)){
			cout << "Here She Is: " << &p << "!" << endl;	
			postFixStack.push(g);
			cout << "We gotta digit! It is " << p << endl;
		}
		if(isalpha(p, loc)){
			postFixStack.push(g);
		}
		if(g.compare("(") == 0){
			processingStack.push(g);
		}
		if(ops.find(g) != string::npos){
			bool highPrecedent = true;
			cout << "Found an op! It is " << g << endl;
			while(processingStack.size() > 0 && highPrecedent){
				string red = processingStack.top();
				if(bob[red] >= bob[g]){							
					postFixStack.push(processingStack.top());
					cout << processingStack.top() << endl;	
					processingStack.pop();
				}
				else{
					highPrecedent = false;
				}
			}
			processingStack.push(g);
			//cout << postFixStack.front() << endl;
		}
		if(g.compare(")") == 0){
			bool isFound = false;
			while(processingStack.size() > 0 and !isFound){
				string red = processingStack.top();
				cout << "red is " << red << endl;
				if(red != "("){
					postFixStack.push(processingStack.top());
					processingStack.pop();
				}else{
					processingStack.pop();
					isFound = true;	
				}
			}	
			if(!isFound){
				cout << "You are missing a paranthesis somewhere in your program. GoodBye." << endl;
			}		
		}
		
	}
	while(!processingStack.empty()){
		if(processingStack.top() != "("){	
			postFixStack.push(processingStack.top());
		}
		processingStack.pop();	
	}
	while(!postFixStack.empty()){
		cout << postFixStack.front() << ' ';
		postFixStack.pop();	
	}	
	return 0;
}
