#pragma once

#include<iostream> 
#include<vector>
#include<list>
using namespace std;

class Graph
{
	int _numOfVertices;    
	vector<vector<int>> _adjList;
	void DFSRecursive(int v, std::vector<bool>& visited) {
		visited[v] = true;
		cout << v << " ";

		for (const auto& i : _adjList[v])
			if (!visited[i]) {
				DFSRecursive(i, visited);
			}
	}

	void Graph::BFSIterative(int s){
		std::vector<bool> visited(_numOfVertices, false);
		list<int> queue;

		visited[s] = true;
		queue.push_back(s);

		while (!queue.empty()){

			s = queue.front();
			cout << s << " ";
			queue.pop_front();

			for (const auto& i : _adjList[s]){
				if (!visited[i]){
					visited[i] = true;
					queue.push_back(i);
				}
			}
		}
	}

public:
	Graph(int num):_numOfVertices(num){
		_adjList.reserve(_numOfVertices);
	}

	void addEdge(int v, int w)
	{
		_adjList[v].push_back(w);
	}

	void DFS(int v) {
		std::vector<bool> visited(_numOfVertices,false);
		DFSRecursive(v, visited);
	}
	
	void BFS(int v) {
		BFSIterative(v);
	}

	

};


int testGraphTraversal()
{
	// Create a graph given in the above diagram 
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "Following is Depth First Traversal"
		" (starting from vertex 2) \n";
	g.DFS(2);
	
	cout << "Following is Breadth First Traversal"
		" (starting from vertex 2) \n";
	g.BFS(2);

	return 0;
}

