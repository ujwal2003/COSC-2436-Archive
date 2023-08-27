#include <iostream>

using namespace std;

struct node {
	string val;
	double priority;
	node* next;
};

class pQueue {
	private:
		node* head;
		
	public:
		pQueue() {
			head = nullptr;
		}
		
		bool isEmpty() {
			return (head == nullptr);
		}
		
		string peek() {
			return head->val;
		}
		
		string dequeue() {
			node* temp = head;
			string v = head->val;
			head = head->next;
			delete(temp);
			return v;
		}
		
		void enqueue(string data, double p) {
			node* start = head;
			node* temp = new node();
			temp->val = data;
			temp->priority = p;
			temp->next = nullptr;
			
			if(head == nullptr || head->priority > p) {
				temp->next = head;
				head = temp;
			} else {
				while(start->next != nullptr && start->next->priority <= p) {
					start = start->next;
				}
				
				temp->next = start->next;
				start->next = temp;
			}
		}
};