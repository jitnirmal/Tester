#include <deque> // to store the vertex ordering
#include <vector>
#include <list>
#include <iostream>
#include <boost/graph/vector_as_graph.hpp>
#include <boost/graph/topological_sort.hpp>

/// <summary>
/// At step 1, The boost::adjacency_list is a class that represents graphs as two - dimensional structures
///			-- first dimension contains vertexes 
///			-- the second dimension contains edges for that vertex.
///	--The boost::adjacency_list must be the default choice for representing a graph because it suits most cases.
/// 
/// The BGL contains two primary graph classes
///		 a) adjacency_list
///		 b) adjacency_matrix.
/// adjacency_list parameters
///		a) EdgeList and VertexList 
///		b) Directed		
///				-- directed, undirected, or bidirectional
///		c)
/// 
/// </summary>

/// <summary>
///											2: get cash at ATM
///													|
///													V
///	0: pick up kids from school		1: buy groceries (and snacks)
///					|						|		|
///					V						V		|
///			3:	drop off kids at soccer practice	|		
///						|							|
///						V							V
///	  5: pick up kids from soccer		4: cook dinner
///								|			|	
///								V			V
///								6: eat dinner
/// 
/// </summary>

/// <summary>
/// output
/// +++++++++++++++++++++++
/// get cash at ATM
/// buy groceries(and snacks)
/// cook dinner
/// pick up kids from school
/// drop off kids at soccer practice
/// pick up kids from soccer
/// eat dinner
/// </summary>

void prepareGraph(std::vector< std::list<int> >& g)
{
	g[0].push_back(3);
	g[1].push_back(3);
	g[1].push_back(4);
	g[2].push_back(1);
	g[3].push_back(5);
	g[4].push_back(6);
	g[5].push_back(6);
}

void testGraphTopologicalSort()
{
	using namespace boost;
	
	const char* tasks[] = {
		"pick up kids from school",
		"buy groceries (and snacks)",
		"get cash at ATM",
		"drop off kids at soccer practice",
		"cook dinner",
		"pick up kids from soccer",
		"eat dinner" };

	const int n_tasks = sizeof(tasks) / sizeof(char*);
	
	std::vector< std::list<int> > g(n_tasks);
	prepareGraph(g);

	std::deque<int> topo_order;

	topological_sort(g, std::front_inserter(topo_order), vertex_index_map(identity_property_map()));

	int n = 1;
	for (std::deque<int>::iterator i = topo_order.begin();
		i != topo_order.end(); ++i, ++n) {
		std::cout << tasks[*i] << std::endl;
	}
}