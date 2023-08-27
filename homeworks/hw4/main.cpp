#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "ArgumentManager.h"
#include "BTree.h"

using namespace std;

//in order traversal of the b-tree
//modified version from geeksforgeeks 
void inOrderTraverse(node* n, stringstream &ss) {
	string out;
	int i;
	for(i=0; i<n->size; i++) {
		if(!(n->leaf))
			inOrderTraverse(n->childptr[i], ss);
		ss << n->keys[i] << ' ';
	}
	
	if(n->leaf == false)
		inOrderTraverse(n->childptr[i], ss);
}

//gets the specified level of the b-tree
//originally from geekforgeeks as a function for a binary tree
//modified to fit specifications of b tree
void getLevel(node* root, int level, stringstream &ss) {
	if(root == nullptr)
		return;
	if(level == 1) {
		for(int i=0; i<root->size; i++)
			ss << root->keys[i] << ' ';
	} else if(level > 1) {
		for(int i=0; i<(root->size)+1; i++) {
			getLevel(root->childptr[i], level - 1, ss);
		}
	}
}

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string cmdfile = am.get("command");
	string outfile = am.get("output");

	ifstream ifs(infile.c_str());
	ifstream cfs(cmdfile.c_str());
	ofstream ofs(outfile.c_str());
	
	int degree;
	vector<string> cmds;
	
	//parsing command file
	string line;
	while(getline(cfs, line)) {
		if(line.find("Degree=") != std::string::npos) {
			degree = stoi(line.substr(line.find("Degree=")+7));
		} else {
			if(line.empty()){continue;}
			cmds.push_back(line);
		}
	}
	
	//parsing input file
	vector<int> nums;
	int num;
	while(ifs >> num) {
		nums.push_back(num);
	}
	
	//removing duplicate numbers
	auto end = nums.end();
	for(auto it = nums.begin(); it != end; ++it) {
		end = remove(it+1, end, *it);
	}
	nums.erase(end, nums.end());
	
	//btree
	btree tree(degree);
	for(int i=0; i<nums.size(); i++) {
		tree.insert(nums[i]); //inserts numbers into btree
	}
	
	//run the commands
	for(int i=0; i<cmds.size(); i++) {
		if(cmds[i].find("Inorder Traversal") != std::string::npos) {
			stringstream ss;
			inOrderTraverse(tree.getRoot(), ss);
			ofs << ss.str() << endl;
		} else if(cmds[i].find("Level ") != std::string::npos){
			int level = stoi(cmds[i].substr(cmds[i].find("Level ") + 6));
			stringstream ss;
			getLevel(tree.getRoot(), level, ss);
			
			if(ss.str().empty())
				ofs << "empty" << endl;
			else
				ofs << ss.str() << endl;
		}
	}
	
	//ofs << "write to file here" << endl;
	ofs.flush();

	ifs.close();
	ofs.close();
}

//printing out inputs:
	// cout << "degree: " << degree << endl;
	// cout << "commands:" << endl;
	// printVector(cmds, " ", "\n");
	// cout << "numbers: ";
	// printVector(nums);
	// cout << "no duplicates: ";
	// printVector(nums);
	
// stringstream ss;
	// inOrderTraverse(tree.getRoot(), ss);
	// cout << "Inorder Traversal: " << ss.str() << endl;
	// cout << endl;
	
	// ss.str("");
	// int l = 2;
	// getLevel(tree.getRoot(), l, ss);
	// if(ss.str().empty())
		// cout << "Level " << l << ": empty" << endl;
	// else
		// cout << "Level " << l << ": " << ss.str() << endl;

// template <typename T>
// void printVector(vector<T> &v, string offset = "", string backOffset = " ") {
// 	for(int i=0; i<v.size(); i++) {
// 		cout << offset << v[i] << backOffset;
// 	}
// 	cout << endl;
// }