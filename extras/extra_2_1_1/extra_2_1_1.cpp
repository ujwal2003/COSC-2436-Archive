/*
* Extra_2_1_1: Car Dealership
*/

#include <iostream>
#include "dealership.h"

using namespace std;

int main() {
	dealership carsList;
	
	carsList.addAtBeg("Volkswagen Jetta", 2016, 14241);
	carsList.addAtBeg("Toyota Camry", 2012, 12200);
	carsList.addAtBeg("Tesla Model S", 2022, 94990);
	
	cout << "length of list: " << to_string(carsList.getLength()) << endl;
	carsList.print();
}