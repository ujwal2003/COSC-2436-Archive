#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>
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

void depthFirstSearch(int v, int numVertices, vector<vector<int>> &matrix) {
	vector<bool> visited(numVertices, false);
	stack<int> st;
	
	st.push(v);
	while(!st.empty()) {
		v = st.top();
		st.pop();
		
		if(!visited[v]) {
			cout << v << ' ';
			visited[v] = true;
		}
		
		for(int i=matrix[v].size(); i>=0; i--) {
			if(matrix[v][i] == 1 && !visited[i])
				st.push(i);
		}
	}
}

int main() {
	int vertices;
	cout << "How many vertices do you want? ";
	cin >> vertices;
	
	srand(time(0));
	
	//create adjacency matrix
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
	
	cout << endl << "Adjacency Matrix:" << endl;
	printMatrix(adjMatrix);
	
	int source = rand() % ((vertices-1) - 0) + 0;
	
	cout << endl << "DFS Traversal starting at source " << source << ':' << endl;
	depthFirstSearch(source, vertices, adjMatrix);
}