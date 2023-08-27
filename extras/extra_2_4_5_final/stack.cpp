#include "stack.h"

bool stack::isEmpty() {
	return (top==nullptr);
}

void stack::push(char c) {
	node* temp = new node;
	temp->val = c;
	temp->next = top;
	top = temp;
}

char stack::peek() {
	if(!isEmpty())
		return top->val;
	return '\0';
}

char stack::pop() {
	if(!isEmpty()) {
		node* temp = top;
		char c = top->val;
		top = top->next;
		delete temp;
		return c;
	} else {
		return '\0';
	}
}