#ifndef _MYSTACK_H
#define _MYSTACK_H

#include <iostream>

template <typename T>
struct nodeStack {
	T val;
	nodeStack<T>* next;
};

template <typename T>
class myStack {
	private:
		nodeStack<T>* top;
		int size;
	
	public:
		myStack() {
			top = nullptr;
			size = 0;
		}
		
		bool isEmpty() {
			return(top == nullptr);
		}
		
		void push(T data) {
			nodeStack<T>* temp = new nodeStack<T>();
			temp->val = data;
			temp->next = top;
			top = temp;
			size++;
		}
		
		T peek() {
			try {
				if(top != nullptr)
					return top->val;
				else
					throw "Error: stack is either empty or some other error.";
			} catch(const char* e) {
				std::cout << e << std::endl;
				exit(10);
			}
		}
		
		T pop() {
			try {
				if(!isEmpty()) {
					nodeStack<T>* temp = top;
					T d = top->val;
					top = top->next;
					delete temp;
					size--;
					return d;
				} else {
					throw "Error: stack is either empty or some other error."; 
				}
			} catch(const char* e) {
				std::cout << e << std::endl;
				exit(10);
			}
		}
		
		int getSize() {
			return size;
		}
};
#endif