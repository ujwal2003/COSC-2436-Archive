#include <iostream>
using namespace std;

template <typename T>
struct node {
	T data;
	node<T> *next;
};

template <typename T>
class LinkedList {
	private:
		node<T> *head;
		int length;
		
	public:
		//constructor
		LinkedList() {
			head = nullptr;
			length = 0;
		}
		
		//returns if list is empty
		bool isEmpty() {
			return head == nullptr;
		}
		
		//return length of list
		int getLength() {
			return length;
		}
		
		//adds node at the end
		void add(T a) {
			node<T>* curr = nullptr;
			node<T>* n = new node<T>();
			
			n->next = nullptr;
			n->data = a;
			
			if(head != nullptr) {
				curr = head;
				while(curr->next != nullptr)
					curr = curr->next;
				curr->next = n;
			} else {
				head = n;
			}
			length++;
		}
		
		//deletes last node
		void deleteEnd() {
			node<T>* curr = head;
			node<T>* prev = nullptr;
			
			if(curr != nullptr) {
				while(curr->next != nullptr) {
					prev = curr;
					curr = curr->next;
				}
				
				prev->next = nullptr;
				delete curr;
				length--;
			}
		}
		
		//adds node at the start
		void addAtStart(T a) {
			node<T>* temp = new node<T>();
			temp->data = a;
			temp->next = head;
			head = temp;
			length++;
		}
		
		//deletes the first node
		void deleteStart() {
			if(head != nullptr) {
				node<T>* curr = head;
				if(head->next == nullptr) {
					head = nullptr;
				} else {
					head = head->next;
					delete curr;
				}
				length--;
			}
		}
		
		//delete element at specified index
		void deleteElm(int index) {
			if(head==nullptr){return;}
			
			node<T>* curr = head;
			
			if(index == 0) {
				head = curr->next;
				delete curr;
				length--;
			}
			
			for(int i=0; curr != nullptr && i < index-1; i++)
				curr = curr->next;
			
			if(curr == nullptr || curr->next == nullptr)
				return;
			
			node<T>* after = curr->next->next;
			delete(curr->next);
			curr->next = after;
			length--;
		}
		
		//add at specific index
		void addAt(T a, int index) {
			if(index < 0 || index > length){return;}
			
			if(index==0) {
				addAtStart(a);
			} else {
				node<T>* curr = head;
				node<T>* prev = nullptr;
				node<T>* insertNode = new node<T>();
				
				insertNode->data = a;
				insertNode->next = nullptr;
				
				for(int i=0; i<length; i++) {
					if(i==index) {
						prev->next = nullptr;
						prev->next = insertNode;
						insertNode->next = curr;
						length++;
						return;
					}
					prev = curr;
					curr = curr->next;
				}
			}
		}
		
		//get value of index
		T getElm(int index) {
			node<T>* curr = head;
			int i = 0;
			try {
				while(curr != nullptr) {
					if(i == index && index < length) {
						return curr->data;
					}
					i++;
					curr = curr->next;
				}
				
				throw "Error: index either out of bounds, or some other error.";
			} catch(const char* e) {
				cout << e << endl;
				exit(10);
			}
		}
		
		//replace value of node at specified index
		void replaceElm(int index, T a) {
			node<T>* curr = head;
			if(index == 0) {
				head->data = a;
			}
			
			int i = 0;
			try {
				while(curr != nullptr) {
					if(i == index && index < length) {
						curr->data = a;
						return;
					}
					i++;
					curr = curr->next;
				}
				throw "Error: could not complete LinkedList::replaceElm(int, T)";
			} catch(const char* e) {
				cout << e << endl;
				exit(10);
			}
		}
		
		//swap the values of two indexes
		void swap(int index1, int index2) {
			T data1 = getElm(index1);
			T data2 = getElm(index2);
			
			replaceElm(index1, data2);
			replaceElm(index2, data1);
		}
		
		//remove repeating [T data]
		void removeRepeating() {
			node<T>* temp1 = head;
			node<T>* temp2 = nullptr;
			node<T>* discard = nullptr;
			
			while(temp1 != nullptr && temp1->next != nullptr) {
				temp2 = temp1;
				while(temp2->next != nullptr) {
					if(temp1->data == temp2->next->data) {
						discard = temp2->next;
						temp2->next = temp2->next->next;
						length = length - 1;
						delete(discard);
					} else {
						temp2 = temp2->next;
					}
				}
				temp1 = temp1->next;
			}
		}
		
		//remove all occurences of a data
		void removeAllOccurrencesOf(T a) {
			node<T>* curr = head;
			node<T>* prev = head;
			
			while(curr != nullptr) {
				if(curr->data == a) {
					if(curr == head) {
						head = curr->next;
						delete curr;
						curr = head;
						length--;
					} else {
						prev->next = curr->next;
						delete curr;
						curr = prev->next;
						length--;
					}
				} else {
					prev = curr;
					curr = curr->next;
				}
			}
		}
		
		//prints the list
		void printList() {
			node<T>* curr = head;
			while(curr != nullptr) {
				cout << curr->data << ' ';
				curr = curr->next;
			}
			cout << endl;
		}
		
};