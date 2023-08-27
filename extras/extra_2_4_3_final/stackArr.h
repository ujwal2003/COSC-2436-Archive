class stackArr {
	private:
		int size;
		int top;
		int* arr;
		
	public:
		stackArr(int s=10) {
			size = s;
			top = -1;
			arr = new int[size];
		}
		
		bool isEmpty();
		bool isFull();
		void push(int val);
		int pop();
		int peek();
		int getSize();
};