#include "dealership.h"
#include <iostream>

using namespace std;

void dealership::addAtBeg(string n, int yr, int pr) {
	car *temp = new car;
	
	temp->name = n;
	temp->year = yr;
	temp->price = pr;
	temp->next = 0;
	
	temp->next = head;
	head = temp;
	
	length++;
}

void dealership::print() {
	car *current = head;
	
	while(current!=nullptr) {
		cout << "{name: " << current->name << ", year: " << current->year << ", price: $" << current->price << "} ";
		current = current->next;
	}
}

int dealership::getLength() {
	return length;
}