#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

void printMatrix(vector<vector<int>> &v) {
	for(int i=0; i<v.size(); i++) {
		cout << i << ": ";
		vector<int> temp = v[i];
		for(int j: temp) {
			cout << j << ' ';
		}
		cout << endl;
		temp.clear();
	}
}

void printAdjList(int v, vector<list<int>> &adjList) {
	for(int i=0; i<v; i++) {
		cout << i << " -> ";
		for(int j: adjList[i]) {
			cout << j << ' ';
		}
		cout << endl;
	}
}

void DFS_recursive(int v, vector<list<int>> &adjList, vector<bool> &visited) {
	visited[v] = true;
	cout << v << ' ';
	
	for(int i: adjList[v]) {
		if(!visited[i]) {
			DFS_recursive(i, adjList, visited);
		}
	}
}

int main() {
	int vertices;
	cout << "How many vertices do you want? ";
	cin >> vertices;
	
	srand(time(0));
	
	//create temporary adjacency matrix
	vector<vector<int>> adjMatrix;
	for(int i=0; i<vertices; i++) {
		vector<int> temp;
		for(int j=0; j<vertices; j++) {
			if(i == j)
				temp.push_back(0);
			else
				temp.push_back(rand()%2);
		}
		adjMatrix.push_back(temp);
		temp.clear();
	}
	
	cout << endl << "temporary matrix:" << endl;
	printMatrix(adjMatrix);
	
	//make adjacency list
	vector<list<int>> adjList;
	adjList.resize(vertices);
	for(int i=0; i<adjMatrix.size(); i++) {
		for(int j=0; j<adjMatrix[i].size(); j++) {
			if(adjMatrix[i][j] == 1) {
				adjList.at(i).push_back(j);
			}
		}
	}
	adjMatrix.clear();
	
	cout << endl << "Adjacency List (" << vertices << " vertices):" << endl;
	printAdjList(adjList.size(), adjList);
	
	//get random source
	int source = rand() % ((vertices-1) - 0) + 0;
	
	//run recursive dfs
	cout << endl << "recursive DFS Traversal starting at source " << source << ':' << endl;
	vector<bool> visited(vertices, false);
	DFS_recursive(source, adjList, visited);
}