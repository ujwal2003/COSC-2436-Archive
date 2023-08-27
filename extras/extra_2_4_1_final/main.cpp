#include <iostream>
#include <cstdlib>
#include <ctime>
#include "myStack.h"

using namespace std;

Books removeNonCS(Books stack) {
	Books newStack;
	cout << "Before:\n" << "\t";
	while(!stack.isEmpty()) {
		string s = stack.pop();
		cout << s << ' ';
		
		if(s.substr(0,2) == "CS")
			newStack.push(s);
	}
	return newStack;
}

int main() {
	string a[6] = {"Sci:Geology", "Math:Calculus", "CS:Data_Structures", "CS:Algorithms", "Math:Geometry", "Sci:Physics"};
	srand(time(0));
	
	Books init;
	for(int i=0; i<5; i++) {
		init.push(a[rand()%6]);
	}
	
	Books CS;
	Books temp = removeNonCS(init);
	while(!temp.isEmpty())
		CS.push(temp.pop());
	
	cout << "\n" << endl;
	cout << "After:\n" << "\t";
	
	if(CS.isEmpty()) {
		cout << "there were no CS books in the original stack" << endl;
	} else {
		while(!CS.isEmpty())
		cout << CS.pop() << ' ';
	}
}