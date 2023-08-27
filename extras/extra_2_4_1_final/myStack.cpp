#include <string>
#include "myStack.h"

using namespace std;

bool Books::isEmpty() {
	return(top==nullptr);
}

void Books::push(string b) {
	node* temp = new node;
	temp->book = b;
	temp->next = top;
	top = temp;
}

string Books::peek() {
	if(top != nullptr)
		return top->book;
	return "";
}

string Books::pop() {
	if(!isEmpty()) {
		node* temp = top;
		string b = top->book;
		top = top->next;
		delete temp;
		return b;
	} else {
		return "";
	}
}