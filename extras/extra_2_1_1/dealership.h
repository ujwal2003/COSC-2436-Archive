#include <iostream>
using namespace std;

struct car {
	string name;
	int year;
	int price;
	
	car* next;
};

class dealership {
	private:
		car* head;
		int length;
	
	public:
		dealership() {
			head = nullptr;
			length = 0;
		}
		
		void addAtBeg(string n, int yr, int pr);
		void print();
		int getLength();
};