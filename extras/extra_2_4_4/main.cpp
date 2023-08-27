#include <iostream>
#include "stack.h"

using namespace std;

bool isBegMatch(char beg, char end) {
	if(beg == '{' && end == '}')
		return true;
	else if(beg == '[' && end == ']')
		return true;
	else if(beg == '(' && end == ')')
		return true;
	else
		return false;
}

bool isExpressionBalanced(string str, stack s) {
	for(int i=0; i<str.length(); i++) {
		if(str[i] == '{' || str[i] == '[' || str[i] == '(') {
			s.push(str[i]);
		} else if(str[i] == '}' || str[i] == ']' || str[i] == ')') {
			if(isBegMatch(s.peek(), str[i]))
				s.pop();
		}
	}
	
	if(s.isEmpty())
		return true;
	else
		return false;
}

int main() {
	cout << "Type in a expression (such as: {2+[3*2]}): ";
	string str;
	getline(cin, str);
	
	cout << endl;
	cout << "You inputted: " << str << endl;
	
	cout << endl;
	stack s;
	if(isExpressionBalanced(str, s))
		cout << "Balanced." << endl;
	else
		cout << "Not Balanced." << endl;
}