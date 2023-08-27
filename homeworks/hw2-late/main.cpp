#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"
#include "LinkedList.h"

using namespace std;

struct Records {
	string id;
	string first;
	string last;
	string DOB;
	string GPA;
};

//split a string into an array with a size by delimter
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

//get the index of a specified id in the linked list
int getIndexOfId(string id, LinkedList<Records> rList) {
	for(int i=0; i<rList.getLength(); i++) {
		if(rList.getElm(i).id == id) {
			return i;
		}
	}
	return -1;
}

//checks if name occurs later in alphabet
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
		// if(name1[i] == '_' || name2[i] == '_'){continue;}
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

//sort the list
void sortListBy(LinkedList<Records> rList, string sortCmd) {
	for(int i=0; i<rList.getLength(); i++) {
		Records curr = rList.getElm(i);
		
		int j;
		if(sortCmd.find("id") != string::npos) {
			int keyId = stoi(curr.id);
			j = i - 1;
			
			while(j >= 0 && stoi(rList.getElm(j).id) > keyId) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j - 1;
			}
			rList.replaceElm(j+1, curr);
		}
		
		if(sortCmd.find("first") != string::npos) {
			string keyFirst = curr.first;
			j = i - 1;
			
			while(j >= 0 && nameIsGreater(rList.getElm(j).first, keyFirst)) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j - 1;
			}
			rList.replaceElm(j+1, curr);
		}
		
		if(sortCmd.find("last") != string::npos) {
			string keyLast = curr.last;
			j = i - 1;
			
			while(j >= 0 && nameIsGreater(rList.getElm(j).last, keyLast)) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j - 1;
			}
			rList.replaceElm(j+1, curr);
		}
		
		if(sortCmd.find("DOB") != string::npos || sortCmd.find("dob") != string::npos) {
			string keyDOB = curr.DOB;
			j = i - 1;
			
			while(j >= 0 && dateIsGreater(rList.getElm(j).DOB, keyDOB)) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j - 1;
			}
			rList.replaceElm(j+1, curr);
		}
		
		if(sortCmd.find("gpa") != string::npos || sortCmd.find("GPA") != string::npos) {
			float keyGpa = stof(curr.GPA);
			j = i - 1;
			
			while(j >= 0 && stof(rList.getElm(j).GPA) > keyGpa) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j - 1;
			}
			rList.replaceElm(j+1, curr);
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
		if (!str.empty() && str[str.size() - 1] == '\r')
			str.erase(str.size() - 1);
		
		if(str.substr(0,6) != "delete") {
			string curr[5];
			split(str, ',', curr);
			
			// string currId = curr[0].erase(curr[0].find("{id:"), 4);
			// string currFirst = curr[1].erase(curr[1].find("first:"), 6);
			// string currLast = curr[2].erase(curr[2].find("last:"), 5);
			// string currDOB = curr[3].erase(curr[3].find("DOB:"), 4);
			// string currGPA = curr[4].erase(curr[4].find("GPA:"), 4);
			// currGPA = currGPA.erase(currGPA.find("}"), 1);
			
			string currId = curr[0].substr(4);
			string currFirst = curr[1].substr(6);
			string currLast = curr[2].substr(5);
			string currDOB = curr[3].substr(4);
			string currGPA = curr[4].substr(4);
			
			std::string curr_gpa{currGPA[0], currGPA[1], currGPA[2]};
			
			Records currRec;
			currRec.id = currId;
			currRec.first = currFirst;
			currRec.last = currLast;
			currRec.DOB = currDOB;
			currRec.GPA = curr_gpa;
			
			if(getIndexOfId(currId, list) != -1) {
				list.replaceElm(getIndexOfId(currId, list), currRec);
				continue;
			}
			
			list.add(currRec);
		} else {
			string deleteId = str.erase(0,7);
			if(getIndexOfId(deleteId, list) != -1)
				list.deleteElm(getIndexOfId(deleteId, list));
			else
				continue;
		}
	}
	
	sortListBy(list, "id");
	string sortStr;
	while(getline(sfs, sortStr)) {
		if(sortStr==""){continue;}
		if (!sortStr.empty() && sortStr[sortStr.size() - 1] == '\r')
			sortStr.erase(sortStr.size() - 1);
		
		sortListBy(list, sortStr);
	}
	
	for(int i=0; i<list.getLength(); i++) {
		ofs << "{id:" << list.getElm(i).id << ',';
		ofs << "first:" << list.getElm(i).first << ',';
		ofs << "last:" << list.getElm(i).last << ',';
		ofs << "DOB:" << list.getElm(i).DOB << ',';
		ofs << "GPA:" << list.getElm(i).GPA << '}';
		ofs << '\n';
	}
	
	ofs.flush();
	
	ifs.close();
	ofs.close();
	sfs.close();
}