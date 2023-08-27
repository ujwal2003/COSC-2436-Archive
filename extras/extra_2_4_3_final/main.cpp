#include <iostream>
#include "stackArr.h"

using namespace std;

int main() {
	stackArr s;
	for(int i=0; i<15; i++)
		s.push(i);
	
	while(!s.isEmpty())
		cout << s.pop() << ' ';
}