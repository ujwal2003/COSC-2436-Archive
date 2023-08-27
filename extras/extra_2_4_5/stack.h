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
		
		bool isEmpty();
		void push(char c);
		char peek();
		char pop();
};