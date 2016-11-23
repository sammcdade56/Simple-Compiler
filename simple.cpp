#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

int accumulator = 0;
int instrPointer = 0;
int instrRegister = 0;
int memory[100] = { };


void read(int num){
	int g;
	cout << "Number Please" << endl;
	cin >> g;
	if(g > 9999){
		cout << "That numbers to big bye" << endl;
	}
	memory[num] = g;
	instrPointer = instrPointer + 1;
}

void write(int num){
	cout << memory[num] << endl;
	instrPointer = instrPointer + 1;

}

void load(int num){
	accumulator = memory[num];
	instrPointer = instrPointer + 1;
}

void store(int num){
	memory[num] = accumulator;
	instrPointer = instrPointer + 1;

}

void add(int num){
	if(memory[num] + accumulator > 9999){
		cout << "You tried to add to big of a number to the accumulator" << endl;
	}
	else{	
		accumulator = accumulator + memory[num];
	}
	instrPointer = instrPointer + 1;

}

void sub(int num){
	accumulator = accumulator - memory[num];
	instrPointer = instrPointer + 1;

}

void divide(int num){
	accumulator = accumulator / memory[num];
	instrPointer = instrPointer + 1;

}

void multiply(int num){
	if(memory[num] * accumulator > 9999){
		cout << "You tried to add to big of a number to the accumulator" << endl;
	}
	else{	
		accumulator = accumulator * memory[num];
	}

	instrPointer = instrPointer + 1;

}

void branch(int num){
	instrPointer = num;
}

void branchNeg(int num){
	if(accumulator < 0){
		instrPointer = num;
	}
	else{
		instrPointer = instrPointer + 1;
	}
}

void branchZero(int num){
	if(accumulator = 0){
		instrPointer = num;
	}else{
			instrPointer = instrPointer + 1;
	}
}

int main(){
	ifstream fileVar;
	fileVar.open("sml.txt", ifstream::in);
	//ifstream fileVar ("file.text", ifstream::in);
	if (!fileVar.is_open()){
		cout << " Cannot open file!" << endl;
	}
	int tracker = 0;
	while(!fileVar.eof()){
		int data = 0;
		fileVar >> data;
		if(data > 9999 and data < 1000){
			cout << "Your file and you are flawed" << endl;
			exit(0);
		}else{
			memory[tracker] = data;
		}
		tracker = tracker + 1;
	}
	while(true){
		int x = 0;
		instrRegister = memory[instrPointer];
		if(instrRegister >= 1000 and instrRegister <=1099){
			int num = instrRegister - 1000;
			read(num);
			x = x+1;
		}
		if(instrRegister >= 1100 and instrRegister <=1199){
			int num = instrRegister - 1100;
			write(num);
			x = x+1;

		}
		if(instrRegister >= 2000 and instrRegister <=2099){
			int num = instrRegister - 2000;
			load(num);
			x = x+1;

		}
		if(instrRegister >= 2100 and instrRegister <=2199){
			int num = instrRegister - 2100;
			store(num);
			x = x+1;

		}
		if(instrRegister >= 3000 and instrRegister <=3099){
			int num = instrRegister - 3000;
			add(num);
			x = x+1;

		}
		if(instrRegister >= 3100 and instrRegister <=3199){
			int num = instrRegister - 3100;
			sub(num);
			x = x+1;

		}
		if(instrRegister >= 3200 and instrRegister <=3299){
			int num = instrRegister - 3200;
			divide(num);
			x = x+1;

		}
		if(instrRegister >= 3300 and instrRegister <=3399){
			int num = instrRegister - 3300;
			multiply(num);
			x = x+1;

		}
		if(instrRegister >= 4000 and instrRegister <=4099){
			int num = instrRegister - 4000;
			branch(num);
			x = x+1;

		}
		if(instrRegister >= 4100 and instrRegister <=4199){
			int num = instrRegister - 4100;
			branchNeg(num);
			x = x+1;

		}
		if(instrRegister >= 4200 and instrRegister <=4299){
			int num = instrRegister - 4200;
			branchZero(num);
			x = x+1;

		}
		if(instrRegister >= 4300 and instrRegister <=4399){
			exit(0);
		}
		if(x == 0){
			cout << "You have used a command that is not found in this langague"<< endl;
		exit(0);
		}
	}	
	return 0;
}
