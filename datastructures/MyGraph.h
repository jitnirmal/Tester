#pragma once
#include <vector>
#include <iostream>
#include <list>
#include <stack>
#include <queue>

/// <summary> 
///   graph G = (V, E) consists of a set of vertices, V, and a set of edges E
///			Each edge is a pair (v, w), If the pair is ordered, then the graph is directed.
/// </summary>
/// 
/// 

template<typename T>
class graph
{
public:
	graph(const int numOfVertices) : mNumOfVertices(numOfVertices)
	{
		for (int i = 0; i < mNumOfVertices; ++i)
		{
			mAdjList.push_back(std::vector<T>());
		}
	}

	graph(std::initializer_list<std::pair<T, T>> vertices) : mNumOfVertices(vertices.size())
	{
		for (int i = 0; i < mNumOfVertices; ++i)
		{
			mAdjList.push_back(std::vector<T>());
		}
		for (const auto& item : vertices)
		{
			insert_edge(item.first, item.second);
		}
	}

	void insert_edge(const T& u, const T& v) noexcept
	{
		mAdjList[u].emplace_back(v);
	}

	void DFS(const T& v) const noexcept
	{
		std::cout << "DFS : (" << v << ") : ";
		std::vector<bool> isVisited(mNumOfVertices, false);
		dfsRecursive(v, isVisited);
		std::cout << std::endl;
	}

	void BFS(const T& v) const noexcept
	{
		std::vector<bool> isVisited(mNumOfVertices, false);
		std::list<T> queue;
		queue.push_back(v);

		std::cout << "BFS : (" << v << ") : ";
		while (!queue.empty())
		{
			auto item = queue.front();
			queue.pop_front();

			isVisited[item] = true;
			std::cout << item << " ";
			for (const auto& item : mAdjList[item])
			{
				if (!isVisited[item])
				{
					queue.push_back(item);
				}
			}
		}
		std::cout << std::endl;
	}

	void TopologicalSort() const noexcept
	{
		//sub vector items has depdency on the main vector index item, so indepth will be incremented
		std::vector<T> in_degree(mNumOfVertices);
		for (const auto& vt : mAdjList)
		{
			for (const auto& item : vt)
				++in_degree[item];
		}

		// queue is helper to keep track of item with no dependecy
		std::queue<T> q;
		for (size_t i = 0; i < in_degree.size(); ++i)
		{
			if (in_degree[i] == 0)
				q.push(i);
		}

		// sort will keep picking up item where dependency is 0
		int cnt{ 0 };
		std::vector<T> topSort;
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
	void dfsRecursive(const T& v, std::vector<bool>& isVisited) const noexcept
	{
		isVisited[v] = true;
		std::cout << v << " ";
		for (const auto& item : mAdjList[v])
		{
			if (!isVisited[item])
			{
				dfsRecursive(item, isVisited);
			}
		}
	}


	std::vector<std::vector<T>> mAdjList;
	const int mNumOfVertices;
};

void testGraph()
{
	//graph g{ { 5,2 }, {5,0}, { 4,0 }, {4,1}, { 2,3 }, {3,1} };
	graph<int> g{ { 1,3 }, {1,4}, { 2,4 }, {2,7}, { 3,6 }, {5,2}, {5,7}, {6,4}, {6,5} };

	g.BFS(1);
	g.DFS(1);
	g.TopologicalSort();


	/*
		BFS : (1) : 1 3 4 6 5 2 7 7
		DFS : (1) : 1 3 6 4 5 2 7
		toposort : 0 1 8 3 6 5 2 4 7

	*/

	/*
	BFS: (5) : 5 2 0 3 1
	DFS : (5) : 5 2 3 1 0
	toposort : 4 5 2 0 3 1 */
}




struct Edge
{
	Edge(int src, int dst, int wt)
		: source(src)
		, dest(dst)
		, weight(wt)
	{}

	int source;
	int dest;
	int weight;

	bool operator<(const Edge& other) const noexcept
	{
		return source < other.source;
	}
};

class wtdGraph
{
public:
	wtdGraph(const std::initializer_list<Edge>& edges)
	{
		int maxIndex = 0;
		for (const auto& edge : edges)
		{
			maxIndex = std::max(maxIndex, std::max(edge.source, edge.dest));
		}
		mAdjList.resize(maxIndex + 1);
		for (const auto& edge : edges)
		{
			mAdjList[edge.source].emplace_back(edge);
		}
	}

	std::vector<int> GetShortestPath(int src) const
	{
		using mpair = std::pair<int, int>;

		// always give the node with minimum distance at top
		std::priority_queue<mpair, std::vector<mpair>, std::greater<mpair>> pq;

		std::vector<int> distance(mAdjList.size(), INF); // node and its distance.
		pq.push(std::make_pair(0, src));
		distance[src] = 0;

		while (!pq.empty())
		{
			auto u = pq.top().second; pq.pop();
			std::cout << "node : " << u << " : ";
			for (const auto& edge : mAdjList[u])
			{
				if (distance[edge.dest] > distance[edge.source] + edge.weight)
				{
					distance[edge.dest] = distance[edge.source] + edge.weight;
					pq.push(std::make_pair(distance[edge.dest], edge.dest));
					std::cout << " " << distance[edge.dest] << " ";
				}
			}
			std::cout << std::endl;
		}
		return distance;
	}

private:
	const int INF = std::numeric_limits<int>::max();
	std::vector<std::vector<Edge>> mAdjList;
};

void testGraph()
{
	wtdGraph g{ {0,1,4}, {0,7,8},
				{1,2,8}, {1,7,11},
				{2,3,7}, {2,8,2}, {2,5,4},
				{3,4,9}, {3,5,14},
				{4,5,10},
				{5,6,2},
				{6,7,1}, {6,8,6},
				{7,8,7},
	};

	auto result = g.GetShortestPath(0);

	for (const auto& item : result)
	{
		std::cout << item << " ";
	}
	std::cout << std::endl;
}


int TestGraph()
{
	testGraph();
}

/*
1. Traverse a given directory using BFS and DFS in Java
https://www.techiedelight.com/traverse-given-directory-bfs-dfs-java/

2. Snake and Ladder Problem
https://www.techiedelight.com/min-throws-required-to-win-snake-and-ladder-game/

*/