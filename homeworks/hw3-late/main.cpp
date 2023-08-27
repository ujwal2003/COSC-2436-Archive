#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include "ArgumentManager.h"

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

using namespace std;

/*
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

//prints out a stack
void printStack(stack<int> &s) {
	while(!s.empty()) {
		cout << s.top() << ' ';
		s.pop();
	}
	cout << endl;
}
*/

//clears a 2d vector
void clear2DVector(vector<vector<int>> &v) {
	for(int i=0; i<v.size(); i++) {
		v.at(i).clear();
	}
	v.clear();
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

/*//checks how many positions till a wall is hit, either the edge, a wall, or an immovable number
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
		for(int i=col; i>=0; i--) {
			if(v[row][i] == 2048 || (v[row][i] != 0 && v[row][i] != currNum) || (v[row][i] != 0 && !isMoveable(v, row, i, LEFT))) {
				//steps++;
				break;
			}
			steps++;
		}
	}
	
	return steps;
}*/

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
void shiftUp(vector<vector<int>> &v) {
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
void shiftRight(vector<vector<int>> &v) {
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
void shiftDown(vector<vector<int>> &v) {
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
void shiftLeft(vector<vector<int>> &v) {
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

//checks if matrix is solved
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

//shifts the matrix around in specified direction to make it look cleaner
void move(vector<vector<int>> &v, int direction) {
	switch(direction) {
		case UP:
			shiftUp(v);
		break;
		
		case RIGHT:
			shiftRight(v);
		break;
		
		case DOWN:
			shiftDown(v);
		break;
		
		case LEFT:
			shiftLeft(v);
		break;
	}
	return;
}

//solves matrix
string solve(vector<vector<int>> &v, int init_move) {
	string out = "";
	vector<int> moves;
	
	if(isSolved(v)) {
		out += '0';
		//cout << '0' << endl;
		return out;
	}
	
	vector<vector<int>> prevState = v;
	int m = init_move;
	
	for(int i=0; i<12; i++) {
		move(v, m);
		moves.push_back(m);
		
		if(v != prevState) {
			prevState = v;
			//cout << "move: " << m << endl;
			//printVector(v);
			//cout << endl;
		} else if(v == prevState) {
			moves.pop_back();
			i--;
			if(isSolved(v))
				break;
			v = prevState;
			m += 1;
			if(m > 4){m=1;}
		}
	}
	
	if(!isSolved(v))
		return "Impossible";
	
	//cout << "moves: ";
	for(int i=0; i<moves.size(); i++) {
		out += to_string(moves[i]);
	}
	return out;
}

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string outfile = am.get("output");
	
	ifstream ifs(infile.c_str());
	ofstream ofs(outfile.c_str());
	
	//parsing input file and placing matrix in 2d vector
	unsigned int matrixSize;
	int numVal;
	vector<vector<int>> matrix;
	
	ifs >> matrixSize;
	for(int i=0; i<matrixSize; i++) {
		vector<int> temp;
		for(int j=0; j<matrixSize; j++) {
			ifs >> numVal;
			temp.push_back(numVal);
		}
		matrix.push_back(temp);
	}
	
	
	//printing things out for testing
	// cout << "matrix of size " << matrixSize << ":" << endl;
	// printVector(matrix);
	
	// cout << endl;
	// cout << "matrix.size(): " << matrix.size() << endl;
	
	// cout << endl;
	
	vector<vector<int>> orig = matrix;
	string upSol = solve(orig, UP);
	
	clear2DVector(orig);
	orig = matrix;
	string rightSol = solve(orig, RIGHT);
	
	clear2DVector(orig);
	orig = matrix;
	string downSol = solve(orig, DOWN);
	
	clear2DVector(orig);
	orig = matrix;
	string leftSol = solve(orig, LEFT);
	
	if(upSol == "Impossible" || rightSol == "Impossible" || downSol == "Impossible" || leftSol == "Impossible") {
		ofs << "Impossible" << endl;
	} else {
		ofs << std::min(stoll(upSol), std::min(stoll(rightSol), std::min(stoll(downSol), stoll(leftSol)))) << endl;
	}
	
	ofs.flush();

	ifs.close();
	ofs.close();
}