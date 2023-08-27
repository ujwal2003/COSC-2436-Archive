#include <iostream>
#include <string>

using namespace std;

struct node {
	char val;
	node* next;
};

class stack {
	private:
		node* top;
		
	public:
		stack() {
			top = nullptr;
		}
		
		bool isEmpty() {
			return (top==nullptr);
		}
		
		void push(char c) {
			node* temp = new node;
			temp->val = c;
			temp->next = top;
			top = temp;
		}
		
		char pop() {
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
};

int main() {
	cout << "Type in your name: ";
	string str;
	getline(cin, str);
	
	stack s;
	
	for(int i=0; i<str.size(); i++)
		s.push(str[i]);
	
	cout << endl;
	while(!s.isEmpty())
		cout << s.pop();
}