#include <iostream>
#include "stackArr.h"

using namespace std;

bool stackArr::isEmpty() {
	return (top==-1);
}

bool stackArr::isFull() {
	return (top==size);
}

void stackArr::push(int val) {
	if(isFull()) {
		int* temp = new int[size*2];
		for(int i=0; i<top; i++)
			temp[i] = arr[i];
		size *= 2;
		arr = temp;
		
		top++;
		arr[top] = val;
	} else {
		top++;
		arr[top] = val;
	}
}

int stackArr::pop() {
	if(isEmpty()) {
		//cout << "stack is empty" << endl;
		return -1;
	} else {
		return arr[top--];
	}
}

int stackArr::peek() {
	if(isEmpty()) {
		//cout << "stack is empty" << endl;
		return -1;
	} else {
		return arr[top];
	}
}

int stackArr::getSize() {
	return size;
}