#include <iostream>
#include <fstream>
#include <map>
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string outfile = am.get("output");

	ifstream ifs(infile.c_str());
	ofstream ofs(outfile.c_str());
	
	map<string, int> wordMap;
	
	int size;
	string word;
	
	ifs >> size;
	for(int i=0; i<size; i++) {
		ifs >> word;
		wordMap[word] ++;
	}
	
	for(auto x : wordMap) {
		ofs << x.first << ": " << x.second << endl;
	}
	
	ofs.flush();

	ifs.close();
	ofs.close();
}