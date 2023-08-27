/*
* COSC 2436 hw2
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include "ArgumentManager.h"
#include "LinkedList.h"

using namespace std;

struct Records {
	int id;
	string first;
	string last;
	string DOB;
	float gpa;
};

//function to get input as one string separated by commas
string strInput(ifstream &fs) {
	string str;
	string out;
	int count = 0;
	while(getline(fs, str)) {
		if(str == "") {continue;}
		out += str;
		out += ",";
		count++;
	}
	out += "[end_sort]::_" + to_string(count+1);
	return out;
}

string fillWithZero(int n) {
	int len = int(log10(n)+1);
	if(n==0){len=1;}
	if(int(log10(n)+1) != 7) {
		std::ostringstream ss;
		ss << n;
		string t(ss.str());
		string temp;
		
		int toAdd = 7 - len;
		for(int i=0; i<toAdd; i++) {
			temp += "0";
		}
		return(temp + t);
	}
	return to_string(n);
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

//find the student id in the linked list, and return its index
int getIndexOfId(LinkedList<Records> rList, int idNum) {
	for(int i=0; i<rList.getLength(); i++) {
		if(rList.getElm(i).id == idNum)
			return i;
	}
	return -1;
}

//update all duplicates with latter one, makr duplicated items for deletion.
void updateDuplicateIds(LinkedList<Records> rList) {
	Records temp; 
	temp.id = -1000;
	temp.first = "[delete_this]";
	temp.last = "[delete_this]";
	temp.DOB = "[delete_this]";
	temp.gpa = 0.00;
	
	for(int i=0; i<rList.getLength(); i++) {
		if(i!=0) {
			int currId = rList.getElm(i).id;
			for(int j=i-1; j>=0; j--) {
				if(rList.getElm(j).id == currId) {
					Records prior = rList.getElm(j);
					Records curr = rList.getElm(i);
					prior = curr;
					rList.replaceElm(j, prior);
					curr = temp;
					rList.replaceElm(i, curr);
				}
			}
		}
	}
}

//checks if name occurs later in the alphabet 
bool nameIsGreater(string name1, string name2) {
	int shorterSize;
	if(name1.size() > name2.size()) {
		shorterSize = name2.size();
	} else if(name2.size() > name1.size()) {
		shorterSize = name1.size();
	} else if(name1.size() == name2.size()) {
		shorterSize = name1.size();
	}
	
	for(int i=0; i<shorterSize; i++) {
		if(name1[i] == '_' || name2[i] == '_'){continue;}
		if(name1[i] > name2[i]) {
			return true;
		} else {
			if(name1[i] != name2[i]) {
				return false;
			}
		}
	}
	return false;
}

//checks if the date is greater than the other
bool dateIsGreater(string date1, string date2) {
	string dateComp1[3];
	string dateComp2[3];
	split(date1, '-', dateComp1);
	split(date2, '-', dateComp2);
	
	//0: year, 1: month, 2: day
	if(stoi(dateComp1[0]) > stoi(dateComp2[0])) {
		return true;
	} else if(stoi(dateComp1[0]) == stoi(dateComp2[0])) {
		if(stoi(dateComp1[1]) > stoi(dateComp2[1])) {
			return true;
		} else if(stoi(dateComp1[1]) == stoi(dateComp2[1])) {
			if(stoi(dateComp1[2]) > stoi(dateComp2[2])) {
				return true;
			}
		}
	}
	return false;
}

//sorts list by command
void sortListBy(LinkedList<Records> rList, string sortCmd) {
	for(int i=1; i<rList.getLength(); i++) {
		Records selected = rList.getElm(i);
		
		int j;
		if(sortCmd == "id") {
			int keyId = selected.id;
			j = i - 1;
			
			while(j >= 0 && rList.getElm(j).id > keyId) {
				rList.replaceElm(j+1,rList.getElm(j));
				j = j-1;
			}
			rList.replaceElm(j+1,selected);
			
		} else if(sortCmd == "first") {
			string keyFirst = selected.first;
			j = i - 1;
			
			while(j >= 0 && nameIsGreater(rList.getElm(j).first, keyFirst)) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j-1;
			}
			rList.replaceElm(j+1, selected);
			
		} else if(sortCmd == "last") {
			string keyLast = selected.last;
			j = i - 1;
			
			while(j >= 0 && nameIsGreater(rList.getElm(j).last, keyLast)) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j-1;
			}
			rList.replaceElm(j+1, selected);
			
		} else if(sortCmd == "DOB") {
			string keyDOB = selected.DOB;
			j = i - 1;
			
			while(j >= 0 && dateIsGreater(rList.getElm(j).DOB, keyDOB)) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j-1;
			}
			rList.replaceElm(j+1, selected);
			
		} else if(sortCmd == "gpa") {
			float keyGpa = selected.gpa;
			j = i - 1;
			
			while(j >= 0 && rList.getElm(j).gpa > keyGpa) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j-1;
			}
			rList.replaceElm(j+1,selected);
		}
	}
}

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string outfile = am.get("output");
	string sortfile = am.get("sort");
	
	ifstream ifs(infile.c_str());
	ofstream ofs(outfile.c_str());
	ifstream sfs(sortfile.c_str());
	
	LinkedList<Records> list;
	
	//parsing input
	string str;
	while(getline(ifs, str)) {
		if(str==""){continue;}
		
		if(str.find("delete ") == string::npos) {
			string records[5];
			split(str, ',', records);
			
			Records r;
			int id_in = stoi(records[0].erase(records[0].find("{id:"), 4));
			string first_in = records[1].erase(records[1].find("first:"), 6);
			string last_in = records[2].erase(records[2].find("last:"), 5);
			string DOB_in = records[3].erase(records[3].find("DOB:"), 4);
			string gpa_s = records[4].erase(records[4].find("GPA:"), 4);
			float gpa_in = stof(gpa_s.erase(gpa_s.find("}"), 1));
			
			r.id = id_in;
			r.first = first_in;
			r.last = last_in;
			r.DOB = DOB_in;
			r.gpa = gpa_in;
			
			list.add(r);
		} else {
			int delId = stoi(str.erase(str.find("delete "), 7));
			list.deleteElm(getIndexOfId(list, delId));
		}
	}
	
	//update and remove duplicated ids
	updateDuplicateIds(list);
	LinkedList<Records> newList;
	for(int i=0; i<list.getLength(); i++) {
		Records curr = list.getElm(i);
		if(curr.id != -1000) {
			newList.add(curr);
		}
	}
	
	//getting the sort commands
	string sortStr = strInput(sfs);
	int size;
	for(int i=0; i<sortStr.size(); i++) {
		if(i > 0 && sortStr.at(i) == '_' && sortStr.at(i-1) == ':')
			size = (sortStr.at(i+1)) - '0';
	}
	string sortCmds[size];
	split(sortStr, ',', sortCmds);
	
	//doing the sorting
	sortListBy(newList, "id");
	for(int i=0; i<size-1; i++) {
		string cmd = sortCmds[i];
		sortListBy(newList, cmd);
	}
	
	//writing to file
	for(int i=0; i<newList.getLength(); i++) {
		ofs << "{id:" << fillWithZero(newList.getElm(i).id) << ",";
		ofs << "first:" << newList.getElm(i).first << ",";
		ofs << "last:" << newList.getElm(i).last << ",";
		ofs << "DOB:" << newList.getElm(i).DOB << ",";
		std::ostringstream ss;
		ss << newList.getElm(i).gpa;
		string t(ss.str());
		if(t.find(".") == std::string::npos) {t += ".0";}
		ofs << "GPA:" << t << "}\n";
	}
	
	ofs.flush();
	
	ifs.close();
	ofs.close();
	sfs.close();
}