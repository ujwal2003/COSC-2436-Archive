#include <iostream>
using namespace std;

//counts to n
void count(int n) {
	static int i = 0;
	if(n == 0) {
		cout << 0;
		return;
	}
	else if(i == n)
		return;
	else if(n < 0) {
		if(i==0)
			cout << "0 ";
		i--;
		cout << i << " ";
		count(n);
	}
	else {
		if(i==0)
			cout << "0 ";
		i++;
		cout << i << " ";
		count(n);
	}
}

int main() {
	cout << "Counting to a number." << endl;
	int num;
	cout << "Enter a number (entering a non-number will default to 0): ";
	cin >> num;
	cout << endl;
	count(num);
}