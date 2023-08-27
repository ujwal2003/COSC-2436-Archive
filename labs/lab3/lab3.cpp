#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ArgumentManager.h"
#include "priorityQueue.h"

using namespace std;

//code to extract number from string
//slightly modifed code from geeksforgeeks
long double getDoubleFromStr(string str) {
	stringstream ss;
	ss << str;
	
	string temp;
	long double num;
	while(!ss.eof()) {
		ss >> temp;
		if(stringstream(temp) >> num)
			return num;
		temp = "";
	}
	return -1;
}

string removeNumFromString2(string str) {
	vector<string> stuff;
	string delim = " ";
	
	size_t pos = 0;
	while((pos = str.find(delim)) != std::string::npos) {
		stuff.push_back(str.substr(0, pos));
		str.erase(0, pos + delim.length());
	}
	
	string result;
	for(int i=0; i<stuff.size(); i++) {
		if(i != stuff.size())
			result = result + stuff[i] + " ";
		else
			result += stuff[i];
	}
	return result;
}

//remove double from string of data
/*string removeNumFromString(string str, long double num) {
	ostringstream dstr_ss;
	dstr_ss << num;
	string dstr = dstr_ss.str();
	
	int index = str.find(dstr);
	int len = str.size() - index+1;
	int newLen = str.size() - len;
	string newStr = str.substr(0, newLen);
	return newStr;
}*/

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string outfile = am.get("output");

	ifstream ifs(infile.c_str());
	ofstream ofs(outfile.c_str());
	
	pQueue pq;
	
	string line;
	while(getline(ifs, line)) {
		if(line == ""){continue;}
		long double p = getDoubleFromStr(line);
		//string data = removeNumFromString(line, p);
		string data = removeNumFromString2(line);
		
		pq.enqueue(data, p);
		
		std::size_t found = line.find_last_not_of("\r");
        if(found != std::string::npos){line.erase(found+1);}
	}
	
	while(!pq.isEmpty())
		ofs << pq.dequeue() << endl;

	ofs.flush();

	ifs.close();
	ofs.close();
}