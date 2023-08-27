#include <iostream>
#include <map>

using namespace std;

class Graph {
	public:
		map<int, map<int, double>> adjList;
		
		void addEdge(int i, int j, double length) {
			adjList[i][j] = length;
		}
		
		// void printAdjList() {
			// for(auto x: adjList) {
				// cout << x.first << " -> ";
				
				// map<int, double> temp = x.second;
				// for(auto m: temp) {
					// cout << '{' << m.first << " [" << m.second << "]} ";
				// }
				// cout << endl;
			// }
		// }
};