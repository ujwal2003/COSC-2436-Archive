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

//check if a number is mergable with the next one in a specific direction
bool isMergeable(vector<vector<int>> &v, int row, int col, int direction) {
	int currNum = v[row][col];
	if(currNum == 0 || currNum == 2048){return false;}
	
	if(direction == UP) {
		if(isMoveable(v, row, col, UP) && (row - 1 >= 0) && !isMoveable(v, row-1, col, UP) && (currNum == v[row-1][col]))
			return true;
	}
	
	if(direction == RIGHT) {
		if(isMoveable(v, row, col, RIGHT) && (col + 1 <= v.size()) && !isMoveable(v, row, col+1, RIGHT) && (currNum == v[row][col+1]))
			return true;
	}
	
	if(direction == DOWN) {
		if(isMoveable(v, row, col, DOWN) && (row + 1 <= v.size()) && !isMoveable(v, row+1, col, DOWN) && (currNum == v[row+1][col]))
			return true;
	}
	
	if(direction == LEFT) {
		if(isMoveable(v, row, col, LEFT) && (col - 1 >= 0) && !isMoveable(v, row, col-1, LEFT) && (currNum == v[row][col-1]))
			return true;
	}
	
	return false;
}

//shifts all the numbers up and merges them if necessarry
void shiftUp(vector<vector<int>> &v) {
	vector<int> currCol;
	stack<int> s;
	for(int i=0; i<v.size(); i++) {
		currCol.clear();
		for(int j=0; j<v.size(); j++) {
			int num = v[j][i];
			currCol.push_back(num);
			
			if(num != 0 && num != 2048) {
				if(isMergeable(v, j, i, UP)) {
					int above = s.top();
					s.pop();
					s.push(above + num);
				} else {
					s.push(num);
				}
			} else if(num == 2048) {
				if(s.size() != j) {
					while(s.size() != j)
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
		
		for(int j=0; j<v.size(); j++) {
			v[j][i] = currCol[j];
		}
	}
}

//shifts all the numbers right and merges them if necessarry
void shiftRight(vector<vector<int>> &v) {
	vector<int> currRow;
	stack<int> s;
	
	for(int i=0; i<v.size(); i++) {
		currRow.clear();
		int count = 0;
		for(int j=v.size()-1; j>=0; j--) {
			int num = v[i][j];
			currRow.push_back(num);
			count += 1;
			
			if(num != 0 && num != 2048) {
				if(isMergeable(v, i, j, RIGHT)) {
					int rightNum = s.top();
					s.pop();
					s.push(rightNum + num);
				} else {
					s.push(num);
				}
			} else if(num == 2048) {
				if(s.size() != (count-1)) {
					while(s.size() != (count-1))
						s.push(0);
				}
				s.push(num);
			}
		}
		
		while(s.size() != currRow.size())
			s.push(0);
		
		for(int k=0; k<currRow.size(); k++) {
			int n = s.top();
			currRow[k] = n;
			s.pop();
		}
		
		v[i] = currRow;
	}
}

//shifts all the numbers down and merges them if necessarry
void shiftDown(vector<vector<int>> &v) {
	vector<int> currCol;
	stack<int> s;
	
	for(int i=0; i<v.size(); i++) {
		currCol.clear();
		int count = 0;
		for(int j=v.size()-1; j>=0; j--) {
			int num = v[j][i];
			currCol.push_back(num);
			count += 1;
			
			if(num != 0 && num != 2048) {
				if(isMergeable(v, j, i, DOWN)) {
					int below = s.top();
					s.pop();
					s.push(below + num);
				} else {
					s.push(num);
				}
			} else if(num == 2048) {
				if(s.size() != (count-1)) {
					while(s.size() != (count-1))
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

//shifts all the number lefts and merges them if necessarry
void shiftLeft(vector<vector<int>> &v) {
	vector<int> currRow;
	stack<int> s;
	
	for(int i=0; i<v.size(); i++) {
		currRow.clear();
		int count = 0;
		for(int j=0; j<v.size(); j++) {
			int num = v[i][j];
			currRow.push_back(num);
			count += 1;
			
			if(num != 0 && num != 2048) {
				if(isMergeable(v, i, j, LEFT)) {
					int leftNum = s.top();
					s.pop();
					s.push(leftNum + num);
				} else {
					s.push(num);
				}
			} else if(num == 2048) {
				if(s.size() != (count-1)) {
					while(s.size() != (count-1))
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
			int n = newStack.top();
			currRow[k] = n;
			newStack.pop();
		}
		
		v[i] = currRow;
	}
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
	
	/*int r = 2, c = 0;
	cout << "the value at [" << r << "," << c << "] is: " << matrix[r][c] << endl;
	cout << "(values of 0 or 2048 cannot be moved)" << endl;
	cout << "can [" << r << "," << c << "] be moved up? " << isMoveable(matrix, r, c, UP);
	cout << "        " << "steps to wall by going up: " << distanceToWall(matrix, r, c, UP) << endl;
	cout << "can [" << r << "," << c << "] be moved right? " << isMoveable(matrix, r, c, RIGHT);
	cout << "     " << "steps to wall by going right: " << distanceToWall(matrix, r, c, RIGHT) << endl;
	cout << "can [" << r << "," << c << "] be moved down? " << isMoveable(matrix, r, c, DOWN);
	cout << "      " << "steps to wall by going down: " << distanceToWall(matrix, r, c, DOWN) << endl;
	cout << "can [" << r << "," << c << "] be moved left? " << isMoveable(matrix, r, c, LEFT);
	cout << "      " << "steps to wall by going left: " << distanceToWall(matrix, r, c, LEFT) << endl;*/
	
	cout << endl << "original matrix shifted up:" << endl;
	vector<vector<int>> matrixCopy = matrix;
	shiftUp(matrixCopy);
	printVector(matrixCopy);
	cout << endl;
	
	cout << "original matrix shifted right:" << endl;
	clear2DVector(matrixCopy);
	matrixCopy = matrix;
	shiftRight(matrixCopy);
	printVector(matrixCopy);
	cout << endl;
	
	cout << "original matrix shifted down:" << endl;
	clear2DVector(matrixCopy);
	matrixCopy = matrix;
	shiftDown(matrixCopy);
	printVector(matrixCopy);
	cout << endl;
	
	cout << "original matrix shifted left:" << endl;
	clear2DVector(matrixCopy);
	matrixCopy = matrix;
	shiftLeft(matrixCopy);
	printVector(matrixCopy);
	cout << endl;
	
	//writing output to file
	ofs << "write to file here" << endl;
	ofs.flush();

	ifs.close();
	ofs.close();
}