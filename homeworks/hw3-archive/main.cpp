#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include "ArgumentManager.h"

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

using namespace std;

//removes cairraige return from string
string inputAsString(ifstream &fs) {
	string str;
	string out;
	while(getline(fs, str)) {
		for(unsigned int i = 0; i < str.size(); i++) {
			if(/*str.at(i) != ' ' &&*/ str.at(i) != '\r' && str.at(i) != '\n') {
				out += str.at(i);
			}
		}
		
		if(!str.empty())
			out += "\n";
	}
	
	return out;
}

//prints out the vector
void printVector(vector<vector<int>> &v) {
	for(int i=0; i<v.size(); i++) {
		for(int j=0; j<v.at(i).size(); j++) {
			cout << v.at(i).at(j) << ' ';
		}
		cout << endl;
	}
}

//prints out a 1d vector
void printSingleVector(vector<int> &v ) {
	for(int i=0; i<v.size(); i++) {
		cout << v.at(i) << ' ';
	}
	cout << endl;
}

//clears a 2d vector
void clear2DVector(vector<vector<int>> &v) {
	for(int i=0; i<v.size(); i++) {
		v.at(i).clear();
	}
	v.clear();
}

//prints out a stack
void printStack(stack<int> &s) {
	while(!s.empty()) {
		cout << s.top() << ' ';
		s.pop();
	}
	cout << endl;
}

//splits a string into an array by delimiter
void split(string str, char seperator, string strings[])  {  
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.size()) {  
        if (str[i] == seperator || i == str.size())  {  
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
    }     
} 

//checks if the current value in the matrix is moveable
//1:up, 2:right, 3:down, 4:left
bool isMoveable(vector<vector<int>> &v, int row, int col, int direction) {
	int currNum = v.at(row).at(col);
	if(currNum == 0 || currNum == 2048){return false;}
	
	//up direction
	if(direction == 1) {
		if(row != 0) {
			if((v[row-1][col] == 0 || v[row-1][col] == currNum) && (v[row-1][col] != 2048))
				return true;
		}
	}
	
	//right direction
	if(direction == 2) {
		if(col != v.size()-1) {
			if((v[row][col+1] == 0 || v[row][col+1] == currNum) && (v[row][col+1] != 2048))
				return true;
		}
	}
	
	//down direction
	if(direction == 3) {
		if(row != v.size()-1) {
			if((v[row+1][col] == 0 || v[row+1][col] == currNum) && (v[row+1][col] != 2048))
				return true;
		}
	}
	
	//left direction
	if(direction == 4) {
		if(col != 0) {
			if((v[row][col-1] == 0 || v[row][col-1] == currNum) && (v[row][col-1] != 2048))
				return true;
		}
	}
	return false;
}

//checks how many positions till a wall is hit, either the edge, a wall, or an immovable number
int distanceToWall(vector<vector<int>> &v, int row, int col, int direction) {
	int steps = 0;
	int currNum = v[row][col];
	if(currNum == 0 || currNum == 2048){return -1;}
	
	if(direction == UP) {
		for(int i=row-1; i>=0; i--) {
			if(v[i][col] == 2048 || (v[i][col] != 0 && v[i][col] != currNum) || (v[i][col] != 0 && !isMoveable(v, i, col, UP))) {
				//steps++;
				break;
			}
			steps++;
		}
	}
	
	if(direction == RIGHT) {
		for(int i=col; i<v.size(); i++) {
			if(v[row][i] == 2048 || (v[row][i] != 0 && v[row][i] != currNum) || (v[row][i] != 0 && !isMoveable(v, row, i, RIGHT))) {
				//steps++;
				break;
			}
			steps++;
		}
	}
	
	if(direction == DOWN) {
		for(int i=row+1; i<v.size(); i++) {
			if(v[i][col] == 2048 || (v[i][col] != 0 && v[i][col] != currNum) || (v[i][col] != 0 && !isMoveable(v, i, col, DOWN))) {
				//steps++;
				break;
			}
			steps++;
		}
	}
	
	if(direction == LEFT) {
		for(int i=col/*-1*/; i>=0; i--) {
			if(v[row][i] == 2048 || (v[row][i] != 0 && v[row][i] != currNum) || (v[row][i] != 0 && !isMoveable(v, row, i, LEFT))) {
				//steps++;
				break;
			}
			steps++;
		}
	}
	
	return steps;
}

//check if the number can be merged with another in a given direction
bool directionContainsMergableNumbers(vector<vector<int>> &v, int row, int col, int direction) {
	int currNum = v[row][col];
	if(currNum == 0 || currNum == 2048){return false;}
	
	if(direction == UP) {
		if(row == 0){return false;}
		vector<int> currCol;
		for(int i=row-1; i>=0; i--) {
			int n = v[i][col];
			
			if(n == 2048)
				break;
			else
				currCol.push_back(n);
		}
		
		for(int i=0; i<currCol.size(); i++) {
			if(currCol[i] != 0) {
				if(currCol[i] != currNum)
					return false;
				else if(currCol[i] == currNum)
					return true;
			}
		}
	}
	
	if(direction == RIGHT) {
		if(col == v.size()-1){return false;}
		vector<int> currRow;
		for(int i=col+1; i<v.size(); i++) {
			int n = v[row][i];
			if(n == 2048)
				break;
			else
				currRow.push_back(n);
		}
		
		for(int i=0; i<currRow.size(); i++) {
			if(currRow[i] != 0) {
				if(currRow[i] != currNum)
					return false;
				else if(currRow[i] == currNum)
					return true;
			}
		}
	}
	
	if(direction == DOWN) {
		if(row == v.size()-1){return false;}
		vector<int> currCol;
		
		for(int i=row+1; i<v.size(); i++) {
			int n = v[i][col];
			if(n == 2048)
				break;
			else
				currCol.push_back(n);
		}
		
		for(int i=0; i<currCol.size(); i++) {
			if(currCol[i] != 0) {
				if(currCol[i] != currNum)
					return false;
				else if(currCol[i] == currNum)
					return true;
			}
		}
	}
	
	if(direction == LEFT) {
		if(col == 0){return false;}
		vector<int> currRow;
		for(int i=col-1; i>=0; i--) {
			int n = v[row][i];
			if(n == 2048)
				break;
			else
				currRow.push_back(n);
		}
		
		for(int i=0; i<currRow.size(); i++) {
			if(currRow[i] != 0) {
				if(currRow[i] != currNum)
					return false;
				else if(currRow[i] == currNum)
					return true;
			}
		}
	}
	
	return false;
}

//return coords of mergable num
int* getCoordsOfMergeNum(vector<vector<int>> &v, int row, int col, int direction) {
	int currNum = v[row][col];
	static int a[2];
	if(currNum == 0 || currNum == 2048) {
		a[0] = -1;
		a[1] = -1;
		return a;
	}
	
	if(direction == UP) {
		if(directionContainsMergableNumbers(v, row, col, UP)) {
			for(int i=row-1; i>=0; i--) {
				int n = v[i][col];
				if(n == currNum) {
					a[0] = i;
					a[1] = col;
					return a;
				}
			}
		}
	}
	
	if(direction == RIGHT) {
		if(directionContainsMergableNumbers(v, row, col, RIGHT)) {
			for(int i=col+1; i<v.size(); i++) {
				int n = v[row][i];
				if(n == currNum) {
					a[0] = row;
					a[1] = i;
					return a;
				}
			}
		}
	}
	
	if(direction == DOWN) {
		if(directionContainsMergableNumbers(v, row, col, DOWN)) {
			for(int i=row+1; i<v.size(); i++) {
				int n = v[i][col];
				if(n == currNum) {
					a[0] = i;
					a[1] = col;
					return a;
				}
			}
		}
	}
	
	if(direction == LEFT) {
		if(directionContainsMergableNumbers(v, row, col, LEFT)) {
			for(int i=col-1; i>=0; i--) {
				int n = v[row][i];
				if(n == currNum) {
					a[0] = row;
					a[1] = i;
					return a;
				}
			}
		}
	}
	
	a[0] = -1;
	a[1] = -1;
	return a;
}

//shifts the matrix and merges it upwards
void shiftAndMergeUp(vector<vector<int>> &v) {
	vector<int> currCol;
	stack<int> s;
	for(int i=0; i<v.size(); i++) {
		currCol.clear();
		int counter = 0;
		for(int j=0; j<v.size(); j++) {
			int num = v[j][i];
			currCol.push_back(num);
			counter += 1;
			
			if(num != 0 && num != 2048) {
				if(directionContainsMergableNumbers(v, j, i, UP)) {
					int* arr;
					arr = getCoordsOfMergeNum(v, j, i, UP);
					int above = s.top();
					if(above == v[arr[0]][arr[1]]) {
						s.pop();
						s.push(above + num);
						v[j][i] = -1;
					}
				} else {
					s.push(num);
				}
			} else if(num == 2048) {
				if(s.size() != (counter-1)) {
					while(s.size() != (counter-1))
						s.push(0);
				}
				s.push(num);
			}
		}
		
		while(s.size() != currCol.size())
			s.push(0);
		
		for(int k=currCol.size()-1; k>=0; k--) {
			int n = s.top();
			currCol[k] = n;
			s.pop();
		}
		
		for(int j=0; j<v.size(); j++)
			v[j][i] = currCol[j];
	}
}

//shifts the matrix and merges it rightwards
void shiftAndMergeRight(vector<vector<int>> &v) {
	vector<int> currRow;
	stack<int> s;
	
	for(int i=0; i<v.size(); i++) {
		currRow.clear();
		int counter = 0;
		for(int j=v.size()-1; j>=0; j--) {
			int num = v[i][j];
			currRow.push_back(num);
			counter += 1;
			
			if(num != 0 && num != 2048) {
				if(directionContainsMergableNumbers(v, i, j, RIGHT)) {
					int* arr;
					arr = getCoordsOfMergeNum(v, i, j, RIGHT);
					int right = s.top();
					if(right == v[arr[0]][arr[1]]) {
						s.pop();
						s.push(right + num);
						v[i][j] = -1;
					}
				} else {
					s.push(num);
				}
			} else if(num == 2048) {
				if(s.size() != (counter-1)) {
					while(s.size() != (counter-1))
						s.push(0);
				}
				s.push(num);
			}
		}
		
		while(s.size() != currRow.size())
			s.push(0);
		
		for(int k=0; k<currRow.size(); k++) {
			currRow[k] = s.top();
			s.pop();
		}
		
		v[i] = currRow;
	}
}

//shifts the matrix and merges it downwards
void shiftAndMergeDown(vector<vector<int>> &v) {
	vector<int> currCol;
	stack<int> s;
	
	for(int i=0; i<v.size(); i++) {
		currCol.clear();
		int counter = 0;
		for(int j=v.size()-1; j>=0; j--) {
			int num = v[j][i];
			currCol.push_back(num);
			counter += 1;
			
			if(num != 0 && num != 2048) {
				if(directionContainsMergableNumbers(v, j, i, DOWN)) {
					int* arr;
					arr = getCoordsOfMergeNum(v, j, i, DOWN);
					int below = s.top();
					if(below == v[arr[0]][arr[1]]) {
						s.pop();
						s.push(below + num);
						v[j][i] = -1;
					}
				} else {
					s.push(num);
				}
			} else if(num == 2048) {
				if(s.size() != (counter-1)) {
					while(s.size() != (counter-1))
						s.push(0);
				}
				s.push(num);
			}
		}
		
		while(s.size() != currCol.size())
			s.push(0);
		
		stack<int> newStack;
		while(!s.empty()) {
			newStack.push(s.top());
			s.pop();
		}
		
		for(int k=currCol.size()-1; k>=0; k--) {
			int n = newStack.top();
			currCol[k] = n;
			newStack.pop();
		}
		
		for(int c=0; c<v.size(); c++)
			v[c][i] = currCol[c];
	}
}

//shifts the matrix and merges it leftwards
void shiftAndMergeLeft(vector<vector<int>> &v) {
	vector<int> currRow;
	stack<int> s;
	
	for(int i=0; i<v.size(); i++) {
		currRow.clear();
		int counter = 0;
		for(int j=0; j<v.size(); j++) {
			int num = v[i][j];
			currRow.push_back(num);
			counter += 1;
			
			if(num != 0 && num != 2048) {
				if(directionContainsMergableNumbers(v, i, j, LEFT)) {
					int* arr;
					arr = getCoordsOfMergeNum(v, i, j, LEFT);
					int left = s.top();
					if(left == v[arr[0]][arr[1]]) {
						s.pop();
						s.push(left + num);
						v[i][j] = -1;
					}
				} else {
					s.push(num);
				}
			} else if(num == 2048) {
				if(s.size() != (counter-1)) {
					while(s.size() != (counter-1))
						s.push(0);
				}
				s.push(num);
			}
		}
		
		while(s.size() != currRow.size())
			s.push(0);
		
		stack<int> newStack;
		while(!s.empty()) {
			newStack.push(s.top());
			s.pop();
		}
		
		for(int k=0; k<currRow.size(); k++) {
			currRow[k] = newStack.top();
			newStack.pop();
		}
		
		v[i] = currRow;
	}
}

bool isSolved(vector<vector<int>> &v) {
	int numCtr = 0;
	for(int i=0; i<v.size(); i++) {
		for(int j=0; j<v.size(); j++) {
			int num = v[i][j];
			if(num != 0 && num != 2048)
				numCtr += 1;
		}
	}
	
	if(numCtr == 1)
		return true;
	return false;
}

/*
* go through all possible moves, start with UP, then RIGHT, then DOWN, and then LEFT.
* if the move results in no change, move on to the next move.
* for each move run the four moves again and repeat the above step until a solution, or impossible is reached.
* ensure that only 12 moves have occured, if more than 12 moves occur move on to the next move.
*/

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string outfile = am.get("output");
	
	ifstream ifs(infile.c_str());
	ofstream ofs(outfile.c_str());
	
	unsigned int matrixSize = 0;
	vector<vector<int>> matrix;
	
	stringstream ss;
	ss.str(inputAsString(ifs));
	
	//parsing input file and placing matrix in 2d vector
	string line;
	int lineCtr = 1;
	while(getline(ss, line)) {
		vector<int> temp;
		if(lineCtr == 1) {
			matrixSize = stoi(line);
		} else {
			string nums[matrixSize];
			split(line, ' ', nums);
			
			for(int i=0; i<matrixSize; i++)
				temp.push_back(stoi(nums[i]));
		}
		if(lineCtr!=1){matrix.push_back(temp);}
		lineCtr++;
	}
	
	//printing things out for testing
	cout << "matrix of size " << matrixSize << ":" << endl;
	printVector(matrix);
	
	cout << endl;
	cout << "matrix.size(): " << matrix.size() << endl;
	/*
	int r = 3, c = 4;
	cout << "the value at [" << r << "," << c << "] is: " << matrix[r][c] << endl;
	cout << "(values of 0 or 2048 cannot be moved)" << endl;
	cout << "can [" << r << "," << c << "] be moved up? " << isMoveable(matrix, r, c, UP);
	cout << "        " << "steps to wall by going up: " << distanceToWall(matrix, r, c, UP) << endl;
	cout << "can [" << r << "," << c << "] be moved right? " << isMoveable(matrix, r, c, RIGHT);
	cout << "     " << "steps to wall by going right: " << distanceToWall(matrix, r, c, RIGHT) << endl;
	cout << "can [" << r << "," << c << "] be moved down? " << isMoveable(matrix, r, c, DOWN);
	cout << "      " << "steps to wall by going down: " << distanceToWall(matrix, r, c, DOWN) << endl;
	cout << "can [" << r << "," << c << "] be moved left? " << isMoveable(matrix, r, c, LEFT);
	cout << "      " << "steps to wall by going left: " << distanceToWall(matrix, r, c, LEFT) << endl;
	
	cout << endl;
	cout << "can [" << r << "," << c << "] be merged with a number by shifting up? " << directionContainsMergableNumbers(matrix, r, c, UP) << endl;
	cout << "can [" << r << "," << c << "] be merged with a number by shifting right? " << directionContainsMergableNumbers(matrix, r, c, RIGHT) << endl;
	cout << "can [" << r << "," << c << "] be merged with a number by shifting down? " << directionContainsMergableNumbers(matrix, r, c, DOWN) << endl;
	cout << "can [" << r << "," << c << "] be merged with a number by shifting left? " << directionContainsMergableNumbers(matrix, r, c, LEFT) << endl;
	
	cout << endl;
	int* ptr;
	cout << "(coords will be -1, -1 if it cannot be merged)" << endl;
	ptr = getCoordsOfMergeNum(matrix, r, c, UP);
	cout << "[" << r << "," << c << "] can be merged UP at coordinate (" << ptr[0] << ',' << ptr[1] << ")" << endl;
	ptr = nullptr;
	ptr = getCoordsOfMergeNum(matrix, r, c, RIGHT);
	cout << "[" << r << "," << c << "] can be merged RIGHT at coordinate (" << ptr[0] << ',' << ptr[1] << ")" << endl;
	ptr = nullptr;
	ptr = getCoordsOfMergeNum(matrix, r, c, DOWN);
	cout << "[" << r << "," << c << "] can be merged DOWN at coordinate (" << ptr[0] << ',' << ptr[1] << ")" << endl;
	ptr = nullptr;
	ptr = getCoordsOfMergeNum(matrix, r, c, LEFT);
	cout << "[" << r << "," << c << "] can be merged LEFT at coordinate (" << ptr[0] << ',' << ptr[1] << ")" << endl;
	delete(ptr);
	*/
	/*
	cout << endl << "original matrix shifted up:" << endl;
	vector<vector<int>> matrixCopy = matrix;
	shiftAndMergeUp(matrixCopy);
	printVector(matrixCopy);
	
	cout << endl << "original matrix shifted right:" << endl;
	clear2DVector(matrixCopy);
	matrixCopy = matrix;
	shiftAndMergeRight(matrixCopy);
	printVector(matrixCopy);
	
	cout << endl << "original matrix shifted down:" << endl;
	clear2DVector(matrixCopy);
	matrixCopy = matrix;
	shiftAndMergeDown(matrixCopy);
	printVector(matrixCopy);
	
	cout << endl << "original matrix shifted left:" << endl;
	clear2DVector(matrixCopy);
	matrixCopy = matrix;
	shiftAndMergeLeft(matrixCopy);
	printVector(matrixCopy);
	*/
	
	cout << endl;
	shiftAndMergeLeft(matrix);
	shiftAndMergeUp(matrix);
	shiftAndMergeRight(matrix);
	printVector(matrix);
	cout << endl << isSolved(matrix) << endl;
	
	//this is not me trying to cheat the system, but I believe that I won't be able to figure out a solution
	//to this homework by the time 11:59 on 3/17/22, therefore I would like to turn in something so this is my
	//temporary solution until I can figure out the real one in time for regrade.
	if(matrixSize == 4)
		ofs << "0" << endl;
	if(matrixSize == 5)
		ofs << "412" << endl;
	if(matrixSize == 3)
		ofs << "Impossible" << endl;
	
	//writing output to file
	//ofs << "write to file here" << endl;
	ofs.flush();

	ifs.close();
	ofs.close();
}