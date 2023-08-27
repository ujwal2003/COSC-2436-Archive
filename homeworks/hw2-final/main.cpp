#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
#include "LinkedList.h"

using namespace std;

struct Records {
	string id;
	string firstName;
	string lastName;
	string DOB;
	string GPA;
	
	Records(string _id, string _fname, string _lname, string _dob, string _gpa) {
		id = _id;
		firstName = _fname;
		lastName = _lname;
		DOB = _dob;
		GPA = _gpa;
	}
	
	Records() {}
};

//checks if name is greater alphabetically
bool isNameGreater(string n1, string n2) {
	bool b = n1 > n2;
	return b;
}

//checks if one date occured after the other
bool isDateGreater(string d1, string d2) {
	stringstream d1ss(d1);
	string d1_yr, d1_month, d1_day;
	getline(d1ss, d1_yr, '-');
	getline(d1ss, d1_month, '-');
	getline(d1ss, d1_day, '-');
	
	stringstream d2ss(d2);
	string d2_yr, d2_month, d2_day;
	getline(d2ss, d2_yr, '-');
	getline(d2ss, d2_month, '-');
	getline(d2ss, d2_day, '-');
	
	if(stoi(d1_yr) > stoi(d2_yr)) {
		return true;
	} else if(stoi(d1_yr) == stoi(d2_yr)) {
		if(stoi(d1_month) > stoi(d2_month)) {
			return true;
		} else if(stoi(d1_month) == stoi(d2_month)) {
			if(stoi(d1_day) > stoi(d2_day)) {
				return true;
			}
		}
	}
	
	return false;
}

void sortListBy(LinkedList<Records> rList, string command) {
	Records tempRec;
	if(command == "id") {
		int key, j;
		for(int i=1; i<rList.getSize(); i++) {
			tempRec = rList.getElm(i);
			key = stoi(tempRec.id);
			
			j = i-1;
			while(j >= 0 && stoi(rList.getElm(j).id) > key) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j-1;
			}
			rList.replaceElm(j+1, tempRec);
		}
	} 
	
	else if(command == "first") {
		string key;
		int j;
		for(int i=1; i<rList.getSize(); i++) {
			tempRec = rList.getElm(i);
			key = tempRec.firstName;
			
			j = i-1;
			while(j >= 0 && isNameGreater(rList.getElm(j).firstName, key)) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j-1;
			}
			rList.replaceElm(j+1, tempRec);
		}
	} 
	
	else if(command == "last") {
		string key;
		int j;
		for(int i=1; i<rList.getSize(); i++) {
			tempRec = rList.getElm(i);
			key = tempRec.lastName;
			
			j = i-1;
			while(j >= 0 && isNameGreater(rList.getElm(j).lastName, key)) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j-1;
			}
			rList.replaceElm(j+1, tempRec);
		}
	} 
	
	else if(command == "DOB") {
		string key;
		int j;
		for(int i=1; i<rList.getSize(); i++) {
			tempRec = rList.getElm(i);
			key = tempRec.DOB;
			
			j = i-1;
			while(j >= 0 && isDateGreater(rList.getElm(j).DOB, key)) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j-1;
			}
			rList.replaceElm(j+1, tempRec);
		}
	} 
	
	else if(command == "GPA") {
		float key;
		int j;
		for(int i=1; i<rList.getSize(); i++) {
			tempRec = rList.getElm(i);
			key = stof(tempRec.GPA);
			
			j = i-1;
			while(j>=0 && stof(rList.getElm(j).GPA) > key) {
				rList.replaceElm(j+1, rList.getElm(j));
				j = j-1;
			}
			rList.replaceElm(j+1, tempRec);
		}
	}
	
	else
		return;
}

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string sortfile = am.get("sort");
	string outfile = am.get("output");

	ifstream ifs(infile.c_str());
	ifstream sfs(sortfile.c_str());
	ofstream ofs(outfile.c_str());
	
	LinkedList<Records> recordsList;
	
	//parsing input
	string line;
	while(getline(ifs, line)) {
		std::size_t found = line.find_last_not_of("\r\n");
		if(found != std::string::npos){line.erase(found+1);}
		if(line.find("{") == std::string::npos && line[0] != 'd'){continue;}
		
		if(line.find("delete") != std::string::npos) {
			string deletionId = line.substr(7);
			
			for(int i=0; i<recordsList.getSize(); i++) {
				Records r = recordsList.getElm(i);
				if(r.id == deletionId) {
					recordsList.deleteElm(i);
					break;
				}
			}
			
			continue;
		}
		
		stringstream ss(line);
		string id, fname, lname, dob, gpa;
		getline(ss, id, ',');
		getline(ss, fname, ',');
		getline(ss, lname, ',');
		getline(ss, dob, ',');
		getline(ss, gpa, ',');
		
		//id, fname, lname, dob, gpa
		Records currRec(id.substr(4, 7), fname.substr(6), lname.substr(5), dob.substr(4), gpa.substr(4, 3));
		
		bool duplicateFound = false;
		for(int i=0; i<recordsList.getSize(); i++) {
			Records r = recordsList.getElm(i);
			if(r.id == currRec.id) {
				recordsList.replaceElm(i, currRec);
				duplicateFound = true;
				break;
			}
		}
		
		if(!duplicateFound) {
			recordsList.add(currRec);
		} else {
			continue;
		}
	}
	
	//sort list by IDs first
	sortListBy(recordsList, "id");
	
	//sort list by commands given
	string sortCmd;
	while(sfs >> sortCmd) {
		sortListBy(recordsList, sortCmd);
	}
	
	//print out linked list
	for(int i=0; i<recordsList.getSize(); i++) {
		Records r = recordsList.getElm(i);
		ofs << "{id:" << r.id << ",first:" << r.firstName << ",last:" << r.lastName << ",DOB:" << r.DOB << ",GPA:" << r.GPA << '}' << endl;
	}
	
	ofs.flush();

	ifs.close();
	ofs.close();
}