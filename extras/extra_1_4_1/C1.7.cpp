/*
* Problem (C-1.7):
*   Write a short C++ program that takes all the lines input to standard input
*   and writes them to standard output in reverse order. That is, each line is
*   output in the correct order, but the ordering of the lines is reversed.
*
* Ethan (via GroupMe) explained what the problem itself was asking for.
* They did not help me in the code, they only helped me understand the problem itself.
*/

#include <iostream>
#include <string>
#include <locale>
#include<limits>
using namespace std;

void printArray(string arr[], int size) {
	for(int i=0; i<size; i++) {
		cout << arr[i] << endl;
	}
}

string reverseStr(string str) {
	int len = str.size();
	string temp;
	for(int i=len-1; i>=0; i--) {
		temp = temp + str[i];
	}
	return temp;
}

int main() {
	int lineNum;
	cout << "How many lines are you going to input? ";
	cin >> lineNum;
	cout << "\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //from tutorialspoint site on how to use cin.ignore
	
	//cout << lineNum << endl;
	
	if(lineNum == 0) {
		cout << "Please enter only numbers or numbers greater than 0!" << endl;
	} else {
		string lines[lineNum];
		for(int i=0; i<lineNum; i++) {
			string temp;
			cout << "enter input " << i + 1 << " : ";
			getline(cin, lines[i]);
		}
		cout << "\n";
		
		string reversed[lineNum];
		for(int i=0; i<lineNum; i++) {
			string temp = lines[i];
			reversed[i] = reverseStr(temp);
		}
		
		printArray(reversed, lineNum);
	}
}