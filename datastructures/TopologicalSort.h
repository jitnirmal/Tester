#pragma once
#include<vector>
#include<list>
#include<algorithm>
#include<cassert>
#include<list>
#include<stack>
#include<iostream>
//https://www.youtube.com/watch?v=_9a95v2shgQ
//https://www.youtube.com/watch?v=qXdt1AHMB2o
// Class to represent a graph 
class Graph
{
private:	
	int _numOfVertices;   
	std::list<int>* _adj;

private:
	void topologicalSortUtil(int v, bool visited[], std::stack<int> &Stack) {
		visited[v] = true;
		
		std::list<int>::iterator i;
		for (i = _adj[v].begin(); i != _adj[v].end(); ++i)
			if (!visited[*i])
				topologicalSortUtil(*i, visited, Stack);

		Stack.push(v);
	}
public:
	Graph(int numOfVertices):
		_numOfVertices(numOfVertices),
		_adj (new std::list<int>[numOfVertices])
	{
	}
	void AddEdge(int v, int w) {
		_adj[v].push_back(w);
	}

	void topologicalSort() {
		std::stack<int> Stack;

		bool* visited = new bool[_numOfVertices];
		for (int i = 0; i < _numOfVertices; i++)
			visited[i] = false;

		for (int i = 0; i < _numOfVertices; i++)
			if (visited[i] == false)
				topologicalSortUtil(i, visited, Stack);

		while (Stack.empty() == false)
		{
			std::cout << Stack.top() << " ";
			Stack.pop();
		}
	}
};

void TestTopologicalSort() {
	Graph g(6);
	g.AddEdge(5, 2);
	g.AddEdge(5, 0);
	g.AddEdge(4, 0);
	g.AddEdge(4, 1);
	g.AddEdge(2, 3);
	g.AddEdge(3, 1);

	g.topologicalSort();
}