#pragma once
#include<vector>
#include<list>
#include<algorithm>
#include<cassert>

/// <summary> 
///   graph G = (V, E) consists of a set of vertices, V, and a set of edges E
///			Each edge is a pair (v, w), If the pair is ordered, then the graph is directed.
/// </summary>
/// 
/// 


// A simple representation of graph using STL 
#include <vector>
#include <iostream>

template<size_t SIZE>
class AdjacencyGraph {
private:
	std::vector<int> adj[SIZE];
public:
	explicit Graph() {
	}
	void addEdge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	void print()
	{
		for (int v = 0; v < SIZE; ++v)
		{
			std::cout << "\n Adjacency list of vertex " << v << "\n head ";
			for (auto x : adj[v])
				std::cout << "-> " << x;
			std::cout << std::endl;
		}
	}

};


int TestAdjacencylist()
{
	AdjacencyGraph<5> ag;
	ag.addEdge(0, 1);
	ag.addEdge(0, 4);
	ag.addEdge(1, 2);
	ag.addEdge(1, 3);
	ag.addEdge(1, 4);
	ag.addEdge(2, 3);
	ag.addEdge(3, 4);
	ag.print();
	return 0;
}


void TestGraph() {
	TestAdjacencylist();
}