#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"
#include "Graph.h"

using namespace std;

//DFS traversal of all paths in the graph
void findAllPaths(Graph &g, int src, int dest, map<int, bool> visited, int &pathCounter, vector<double> &currLens, vector<vector<double>> &weights) {
	visited[src] = true;
	
	if(src == dest) {
		pathCounter += 1;
		weights.push_back(currLens);
	} else {
		for(auto ed: g.adjList[src]) {
			if(!visited[ed.first]) {
				currLens.push_back(ed.second);
				findAllPaths(g, ed.first, dest, visited, pathCounter, currLens, weights);
			}
		}
	}
	
	currLens.pop_back();
	visited[src] = false;
}

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string pathfile = am.get("path");
	string outfile = am.get("output");

	ifstream ifs(infile.c_str());
	ifstream pfs(pathfile.c_str());
	ofstream ofs(outfile.c_str());
	
	//initialize graph
	Graph g;
	map<int, bool> visited;
	
	//parsing input and placing in graph
	int i, j;
	double length;
	while(ifs >> i && ifs >> j && ifs >> length) {
		g.addEdge(i, j, length);
		visited[i] = false;
		visited[j] = false;
	}
	//cout << "Graph as adjacency list representation:" << endl;
	//g.printAdjList();
	
	//parsing path file
	int src, dest;
	pfs >> src;
	pfs >> dest;
	//cout << endl << "starting node: " << src << endl << "destination node: " << dest << endl << endl;
	
	//counting number of paths, and storing all distances from paths
	int pathCounter = 0;
	vector<double> temp;
	vector<vector<double>> weights;
	findAllPaths(g, src, dest, visited, pathCounter, temp, weights);
	
	//calculating total distance for each path taken
	vector<double> distances;
	for(int x=0; x<weights.size(); x++) {
		double currDist = 0.0;
		for(double d: weights[x]) {
			currDist += d;
		}
		distances.push_back(currDist);
	}
	
	//sort distances from least to greates
	sort(distances.begin(), distances.end());
	
	if(pathCounter == 0) {
		//if there are no paths
		ofs << "Infinite" << endl;
		ofs << "Infinite" << endl;
		ofs << '0' << endl;
	} else {
		ofs << distances[0] << endl; //shortest path
		ofs << distances[distances.size()-1] << endl; //longest path
		ofs << pathCounter << endl; //number of paths
	}
	
	ofs.flush();

	ifs.close();
	ofs.close();
}