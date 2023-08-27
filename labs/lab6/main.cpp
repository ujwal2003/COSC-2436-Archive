#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
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
};

void depthFirstSearch(int source, Graph &g, ofstream &os) {
	vector<bool> visited(g.vertices, false);
	stack<int> st;
	
	st.push(source);
	while(!st.empty()) {
		source = st.top();
		st.pop();
		
		if(!visited[source]) {
			os << source << ' ';
			visited[source] = true;
		}
		
		for(int i: g.adjList[source]) {
			if(!visited[i]) {
				st.push(i);
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
	
	//retrieve number of vertices and source node
	int numVertices, source;
	ifs >> numVertices;
	ifs >> source;
	
	Graph g(numVertices);
	
	//adding edges to graph
	int a, b;
	while(ifs >> a && ifs >> b) {
		g.addAdjVertices(a, b);
	}
	
	depthFirstSearch(source, g, ofs);
	ofs.flush();

	ifs.close();
	ofs.close();
}