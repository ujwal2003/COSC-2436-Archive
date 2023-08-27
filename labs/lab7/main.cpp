#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <stack>
#include "ArgumentManager.h"

using namespace std;

class Graph {
	public:
		int vertices;
		vector<list<int>> adjList;
		
		Graph(int v) {
			vertices = v;
			adjList.resize(vertices);
		}
		
		void addEdge(int a, int b) {
			adjList[a].push_back(b);
			adjList[b].push_back(a);
		}
		
		// void printAdjList() {
			// for(int i=0; i<vertices; i++) {
				// cout << i << " -> ";
				// for(int j: adjList[i]) {
					// cout << j << ' ';
				// }
				// cout << endl;
			// }
		// }
};

void depthFirstSearch_validPath(Graph &g, int source, int dest, ofstream &os) {
	vector<bool> visited(g.vertices, false);
	stack<int> st;
	
	st.push(source);
	while(!st.empty()) {
		source = st.top();
		st.pop();
		
		if(!visited[source]) {
			//cout << source << ' ';
			if(source == dest) {
				os << "true";
				return;
			}
			visited[source] = true;
		}
		
		for(int i: g.adjList[source]) {
			if(!visited[i]) {
				st.push(i);
			}
		}
	}
	
	os << "false";
	return;
}

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	
	string infile = am.get("input");
	string outfile = am.get("output");

	ifstream ifs(infile);
	ofstream ofs(outfile);
	
	int numVertices, src, dest;
	ifs >> numVertices;
	ifs >> src;
	ifs >> dest;
	
	Graph g(numVertices);
	
	int a, b;
	while(ifs >> a && ifs >> b) {
		g.addEdge(a, b);
	}
	
	//cout << "start: " << src << " end: " << dest << endl << "graph with " << numVertices << " vertices:" << endl;
	//g.printAdjList();
	
	//cout << endl;
	depthFirstSearch_validPath(g, src, dest, ofs);
	
	ofs.flush();

	ifs.close();
	ofs.close();
}