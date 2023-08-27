/*
* COSC2436 Lab 1: checking if a word exists in a matrix of characters.
*
* parts of the code were implemented with the examples provided by the TA
* in the lab. The method to use backtracking for checked letters was taken
* from a youtube tutorial on backtracking.
*
* basic idea: keep finding the letters of the word until the length of the 
* word is found with its correct letters, or until it fails to find a letter.
*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "ArgumentManager.h"
using namespace std;

#define LOG(x) cout << x << endl;

//prints out the vector
void printVector(vector<vector<char>> &v) {
	for(int i=0; i<v.size(); i++) {
		for(int j=0; j<v.at(i).size(); j++) {
			cout << v[i][j] << ' ';
		}
		cout << "\n";
	}
}

bool searchForWord(vector<vector<char>> &board, string word, int pos, int x, int y, int m, int n) {
	char letter = board[x][y];
	bool out = false;
	
	if(word.size() == pos+1) {
		return true;
	}
	
	if(letter != word[pos]) {
		return out;
	}
	
	board[x][y] = '~';
	//left
	if(x>0 && searchForWord(board, word, pos+1, x-1, y, m, n)) {
		out = true;
	}
	//down
	if(!out && y>0 && searchForWord(board, word, pos+1, x, y-1, m, n)) {
		out = true;
	}
	//right
	if(!out && x<m-1 && searchForWord(board, word, pos+1, x+1, y, m, n)) {
		out = true;
	}
	//up
	if(!out && y<n-1 && searchForWord(board, word, pos+1, x, y+1, m, n)) {
		out = true;
	}
	board[x][y] = letter;
	
	return out;
}

bool wordExists(vector<vector<char>> &board, string word, int m, int n) {
	if(word == "")
		return false;
	
	if(word.size() > m*n)
		return false;
	
	for(int x=0; x<m; x++) {
		for(int y=0; y<n; y++) {
			if(searchForWord(board, word, 0, x, y, m, n)) {
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    string infilename = am.get("input");
    string outfilename = am.get("output");
    ifstream input(infilename);
    ofstream output(outfilename);

    int row; //integer m, # of row in the matrix (width)
    int col; //integer n, # of column in the matrix (height)
    char value;
    string target; //the string to be search in the matrix
    vector<vector<char>> board; //this 2d vector will be the character matrix

    input >> row;
    input >> col;

    for(int i=0; i<row; i++) {
        vector<char> temp;
        for(int j=0; j<col; j++) {
            input >> value;
            temp.push_back(value);
        }
        board.push_back(temp);
    }

    input >> target;
	
	// LOG("starting:");
	// cout << target << endl;
	// cout << wordExists(board, target, row, col);
	
	if(wordExists(board, target, row, col)) {
		output << "true";
	} else {
		output << "false";
	}

    return 0;
}