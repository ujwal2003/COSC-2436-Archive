#include <string>
using namespace std;

struct node {
	string book;
	node* next;
};

class Books {
	private:
		node* top;
		
	public:
		Books() {
			top = nullptr;
		}
		
		bool isEmpty();
		void push(string b);
		string peek();
		string pop(); 
};