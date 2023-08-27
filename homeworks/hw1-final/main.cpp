/*
* COSC 2436 hw1
* This code was made in several study groups. No member of the group edited my code.
* The code to get the ArgumentManager working was taken with the guidance of 
* group members (notably Alex).
*
* Almost all of this code was typed by me. Some functions (such as split()) were taken 
* from either GeeksForGeeks or JavaTPoint and modified to suit my needs 
* (those functions are labeled).
*/

#include <iostream>
#include <fstream>
#include "ArgumentManager.h"


using namespace std;

//getting inout file as one string (from ArgumentManager tutorial)
string inputAsString(ifstream &fs) {
	string str;
	string out;
	while(getline(fs, str)) {
		for(unsigned int i = 0; i < str.size(); i++) {
			if(str.at(i) != ' ' && str.at(i) != '\r' && str.at(i) != '\n') {
				out += str.at(i);
			}
		}
	}
	
	return out;
}

//replace commas between records with spaces
string commaReplacedWithSpace(string str) {
	for(int i=0; i<str.size(); i++) {
		if(str.at(i) == ',' && str.at(i-1) == '}') {
			str[i] = ' ';
		}
	}
	return str;
}

//get the number of records
int numRecords(string records) {
	int len = 0;
	for(int i=0; i<records.size(); i++) {
		if(records.at(i) == ' ') {
			len++;
		}
	}
	return len+1;
}

//split a string by delimiter and store in an array
//original function taken from javaTpoint, and slightly modified
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

//print an array
void printArray(string arr[], int size) {
	for(int i=0; i<size; i++) {
		cout << arr[i] << " ";
	}
}

//changes all characters to lowercase
string toLowercase(string str) {
	for(int i=0; i<str.size(); i++) {
		str[i]=tolower(str[i]);
	}
	return str;
}

//checks if the target data is found
bool dataFound(string str, string target) {
	if(str.find(target) != string::npos) {
			return true;
	}
	return false;
}

//recursive function to search the data
string searchData(string arr[], int size, string target, int level) {
	if(target=="") {
		return ""; //return nothing if target is empty
	}
	
	if(size==1) {
		if(dataFound(toLowercase(arr[0]), toLowercase(target))) {
			return "Level " + to_string(level) + ": " + arr[0] + "\n";
		} else {
			//return "not found " + to_string(level);
			return "";
		}
	} else {
		if(size%2==0) {
			//split array into equal sizes and return both;
			int halfSize = size/2;
			string arr1[halfSize];
			string arr2[halfSize];
			
			for(int i=0; i<halfSize; i++) {
				arr1[i] = arr[i];
			}
			
			for(int i=halfSize; i<size; i++) {
				arr2[i-halfSize] = arr[i];
			}
			
			// level++;
			return searchData(arr1, halfSize, target, level+1) + searchData(arr2, halfSize, target, level+1);
		} else {
			//split array into unequal sizes and return both;
			int bigSize = (size/2)+1;
			int smallSize = size - bigSize;
			
			string bigArr[bigSize];
			string smallArr[smallSize];
			
			for(int i=0; i<bigSize; i++) {
				bigArr[i] = arr[i];
			}
			
			for(int i=bigSize; i<size; i++) {
				smallArr[i-bigSize] = arr[i];
			}
			
			// level++;
			return searchData(bigArr, bigSize, target, level+1) + searchData(smallArr, smallSize, target, level+1);
		}
	}
}

int main(int argc, char *argv[]) {
	if(argc<2) return 255;
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string cmdfile = am.get("command");
	string outfile = am.get("output");
	
	ifstream ifs(infile);
	ifstream cfs(cmdfile);
	ofstream ofs(outfile);
	
	//replacing commas in between records with spaces
	string input = commaReplacedWithSpace(inputAsString(ifs));
	string records[numRecords(input)];
	
	split(input, ' ', records); //placing input into an array
	string target = inputAsString(cfs);
	
	ofs << searchData(records, numRecords(input), target, 0);
	ofs.flush();
	
	ifs.close();
	cfs.close();
	ofs.close();
}