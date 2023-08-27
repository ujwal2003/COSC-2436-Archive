#include <iostream>

using namespace std;

template <typename T>
struct node {
	T data;
	node<T>* next;
};

template <typename T>
class LinkedList {
	private:
		node<T>* head;
		int size;
		
	public:
		//constructor
		LinkedList() {
			head = nullptr;
			size = 0;
		}
		
		//checks if list is empty
		bool isEmpty() {
			return (head == nullptr);
		}
		
		//returns the size of the list
		int getSize() {
			return size;
		}
		
		//inserts data at start of list
		void insertBeg(T a) {
			node<T>* cu = head;
			node<T>* temp = new node<T>();
			temp->data = a;
			temp->next = cu;
			head = temp;
			size++;
		}
		
		//removes data from start of list
		void removeBeg() {
			if(head != nullptr) {
				node<T>* cu = head;
				if(head->next == nullptr) {
					head = nullptr;
				} else {
					head = head->next;
					delete cu;
				}
				size--;
			}
		}
		
		//adds data at end of list
		void add(T a) {
			node<T>* cu = head;
			node<T>* temp = new node<T>();
			temp->data = a;
			temp->next = nullptr;
			
			if(cu == nullptr) {
				head = temp;
			} else {
				while(cu->next != nullptr) {
					cu = cu->next;
				}
				cu->next = temp;
			}
			size++;
		}
		
		void removeEnd() {
			node<T>* cu = head;
			node<T>* prev = nullptr;
			if(cu != nullptr) {
				while(cu->next != nullptr) {
					prev = cu;
					cu = cu->next;
				}
				prev->next = nullptr;
				delete cu;
				size--;
			}
		}
		
		void replaceElm(int index, T a) {
			if(index > size || index < 0)
				return;
			
			node<T>* cu = head;
			if(index == 0) {
				head->data = a;
			} else {
				int i = 0;
				while(cu != nullptr) {
					if(i == index && index < size) {
						cu->data = a;
						return;
					}
					i++;
					cu = cu->next;
				}
			}
		}
		
		int findElm(T a) {
			node<T>* cu = head;
			int indxCtr = 0;
			
			while(cu != nullptr && cu->data != a) {
				indxCtr++;
				cu = cu->next;
			}
			
			if(cu->data == a) {
				return indxCtr;
			} else {
				return -1;
			}
		}
		
		T getElm(int index) {
			if(index > size || index < 0)
				exit(10);
			
			node<T>* cu = head;
			int i = 0;
			while(cu != nullptr) {
				if(i == index) {
					return cu->data;
				}
				i++;
				cu = cu->next;
			}
			
			exit(10);
		}
		
		void deleteElm(int index) {
			if(head == nullptr){return;}
			if(index > size || index < 0){return;}
			
			node<T>* cu = head;
			if(index == 0) {
				removeBeg();
				return;
			}
			
			for(int i=0; cu != nullptr && i < index-1; i++) {
				cu = cu->next;
			}
			
			if(cu == nullptr || cu->next == nullptr)
				return;
			
			node<T>* after = cu->next->next;
			delete(cu->next);
			cu->next = after;
			size--;
		}
		
		void printList() {
			node<T>* cu = head;
			while(cu != nullptr) {
			  cout<< cu->data << ' ';
			  cu = cu->next;
			}
			cout<<endl;
		}
};