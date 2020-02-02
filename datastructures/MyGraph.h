#pragma once
#include <vector>
#include <iostream>
#include <list>
#include <stack>

/// <summary> 
///   graph G = (V, E) consists of a set of vertices, V, and a set of edges E
///			Each edge is a pair (v, w), If the pair is ordered, then the graph is directed.
/// </summary>
/// 
/// 


class graph
{
public:
	graph(const int numOfVertices) : mNumOfVertices(numOfVertices)
	{
		for (int i = 0; i < mNumOfVertices; ++i)
		{
			mAdjList.push_back(std::vector<int>());
		}
	}

	graph(std::initializer_list<std::pair<int, int>> vertices) : mNumOfVertices(vertices.size())
	{
		for (int i = 0; i < mNumOfVertices; ++i)
		{
			mAdjList.push_back(std::vector<int>());
		}
		for (const auto& item : vertices)
		{
			insert_edge(item.first, item.second);
		}
	}

	void insert_edge(int u, int v)
	{
		mAdjList[u].push_back(v);
	}

	void DFSRecursive(int v)
	{
		std::cout << "DFS : (" << v << ")";
		std::vector<bool> isVisited(mNumOfVertices, false);
		DFSRecursive(v, isVisited);
		std::cout << std::endl;
	}

	void BFSIterative(int v)
	{
		std::vector<bool> isVisited(mNumOfVertices, false);
		std::list<int> queue;
		queue.push_back(v);
		std::cout << "BFS : (" << v << ")";
		while (!queue.empty())
		{
			int qi = queue.front();
			queue.pop_front();

			isVisited[qi] = true;
			std::cout << qi << " ";
			for (const auto& item : mAdjList[qi])
			{
				if (!isVisited[item])
				{
					queue.push_back(item);
				}
			}
		}
		std::cout << std::endl;
	}

	void topologicalSort()
	{
		std::vector<int> in_degree(mNumOfVertices);
		for (const auto& vt : mAdjList)
		{
			for (const auto& item : vt)
				++in_degree[item];
		}

		std::queue<int> q;
		for (int i = 0; i < in_degree.size(); ++i)
		{
			if (in_degree[i] == 0)
				q.push(i);
		}

		int cnt{ 0 };
		std::vector<int> topSort;
		while (!q.empty())
		{
			auto item = q.front();
			q.pop();
			topSort.push_back(item);

			for (const auto& v : mAdjList[item])
			{
				if (--in_degree[v] == 0)
					q.push(v);
			}
			++cnt;
		}

		if (cnt != mNumOfVertices)
			std::cout << "Topo sort is not possible" << std::endl;

		std::cout << "toposort : ";
		for (const auto& item : topSort)
			std::cout << item << " ";
		std::cout << std::endl;

	}

private:
	void DFSRecursive(int v, std::vector<bool> & isVisited)
	{
		isVisited[v] = true;
		std::cout << v << " ";
		for (const auto& item : mAdjList[v])
		{
			if (!isVisited[item])
			{
				DFSRecursive(item, isVisited);
			}
		}
	}


	std::vector<std::vector<int>> mAdjList;
	const int mNumOfVertices;
};

void testGraph()
{
	graph g{ { 5,2 }, {5,0}, { 4,0 }, {4,1}, { 2,3 }, {3,1} };
	g.BFSIterative(5);
	g.DFSRecursive(5);
	g.topologicalSort();
}


void TestGraph() {
	testGraph();
}