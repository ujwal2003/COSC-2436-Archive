#include <iostream>
using namespace std;

//prints array backwards
void PA(int a[], int n) {
	if(n==0)
		return;
	else {
		cout << a[n-1] << " ";
		PA(a, n-1);
	}
}

//prints array forwards
void PA2(int a[], int n) {
	if(n==0)
		return;
	else {
		PA2(a, n-1);
		cout << a[n-1] << " ";
	}
}

int main() {
	int a[6] = {10, 20, 30, 40, 50, 60};
	
	cout << "Printing out the array backwards: " << endl;
	PA(a, 6);
	cout << endl;
	
	cout << endl;
	
	cout << "Printing out the array forwards: " << endl;
	PA2(a, 6);
}