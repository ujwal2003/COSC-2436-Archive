#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "ArgumentManager.h"

using namespace std;

class Graph {
	public:
		int vertices;
		vector<vector<int>> adjList;
		
		Graph(int v) {
			vertices = v;
			adjList.resize(vertices);
		}
		
		void addAdjVertices(int a, int b) {
			adjList[a].push_back(b);
		}
		
		// void printAdjList() {
			// for(int i=0; i<vertices; i++) {
				// cout << i << "-> ";
				// for(int j=0; j<adjList[i].size(); j++) {
					// cout << adjList[i].at(j) << ' ';
				// }
				// cout << endl;
			// }
		// }
};

void breadthFirstSearch(int source, Graph &g, ofstream &stream) {
	queue<int> q;
	q.push(source);
	
	vector<bool> visited(g.vertices, false);
	
	while(!q.empty()) {
		source = q.front();
		q.pop();
		
		if(!visited[source]) {
			stream << source << ' ';
			visited[source] = true;
		}
		
		for(int i: g.adjList[source]) {
			if(!visited[i]) {
				q.push(i);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string outfile = am.get("output");

	ifstream ifs(infile.c_str());
	ofstream ofs(outfile.c_str());
	
	int numVertices, source;
	ifs >> numVertices;
	ifs >> source;
	
	Graph g(numVertices);
	
	int a, b;
	while(ifs >> a && ifs >> b) {
		g.addAdjVertices(a, b);
	}
	
	breadthFirstSearch(source, g, ofs);
	ofs.flush();

	ifs.close();
	ofs.close();
}