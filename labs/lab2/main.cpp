#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
#include "LinkedList.h"

using namespace std;

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string outfile = am.get("output");
	
	ifstream ifs(infile.c_str());
	ofstream ofs(outfile.c_str());
	
	string dataType;
	LinkedList<string> strList;
	LinkedList<int> intList;
	LinkedList<char> charList;
	
	string str;
	int line = 0;
	while(getline(ifs, str)) {
		if(str==""){continue;}
		
		if (!str.empty() && str[str.size() - 1] == '\r')
			str.erase(str.size() - 1);
		
		if(line == 0)
			dataType = str;
		
		if(line != 0) {
			//for the add command
			if(str.substr(0,3) == "Add") {
				int index = stoi(str.substr(5, str.find(")")-1));
				
				if(dataType == "string") {
					string data = str.substr(str.find("[")+1, str.find("]")-str.find("[")-1);
					if(index==0) {
						strList.addAtStart(data);
						continue;
					} else if(index < strList.getLength()) {
						strList.addAt(data, index);
					} else if(index==strList.getLength()) {
						strList.add(data);
						continue;
					} else if(index > strList.getLength()) {
						continue;
					}
				}
				
				if(dataType == "int") {
					int num = stoi(str.substr(str.find("[")+1, str.find("]")-str.find("[")-1));
					
					if(index==0) {
						intList.addAtStart(num);
						continue;
					} else if(index < intList.getLength()) {
						intList.addAt(num, index);
					} else if(index==intList.getLength()) {
						intList.add(num);
						continue;
					} else if(index > intList.getLength()) {
						continue;
					}
				} 
				
				if(dataType == "char") {
					char c = (str.substr(str.find("[")+1, str.find("]")-str.find("[")-1))[0];
					
					if(index==0) {
						charList.addAtStart(c);
						continue;
					} else if(index < charList.getLength()) {
						charList.addAt(c, index);
					} else if(index==charList.getLength()) {
						charList.add(c);
						continue;
					} else if(index > charList.getLength()) {
						continue;
					}
				}
			} 
			
			//for the remove command
			if(str.substr(0,6) == "Remove") {
				if(dataType == "string") {
					string data = str.substr(str.find("[")+1, str.find("]")-str.find("[")-1);
					strList.removeAllOccurrencesOf(data);
				}
				
				if(dataType == "int") {
					int num = stoi(str.substr(str.find("[")+1, str.find("]")-str.find("[")-1));
					intList.removeAllOccurrencesOf(num);
				}
				
				if(dataType == "char") {
					char c = (str.substr(str.find("[")+1, str.find("]")-str.find("[")-1))[0];
					charList.removeAllOccurrencesOf(c);
				}
			}
		}
		
		line++;
	}
	
	//outputting to file
	if(dataType == "string") {
		for(int i=0; i<strList.getLength(); i++)
			ofs << strList.getElm(i) << ' ';
	} else if(dataType == "int") {
		for(int i=0; i<intList.getLength(); i++)
			ofs << intList.getElm(i) << ' ';
	} else if(dataType == "char") {
		for(int i=0; i<charList.getLength(); i++)
			ofs << charList.getElm(i) << ' ';
	}
	
	ofs << "\n";
	
	ofs.flush();
	
	ifs.close();
	ofs.close();
}