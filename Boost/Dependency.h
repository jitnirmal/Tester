#include <iostream> // std::cout
#include <utility> // std::pair
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>

//https://www.boost.org/doc/libs/1_42_0/libs/graph/doc/file_dependency_example.html
enum files_e {
	dax_h, yow_h, boz_h, zow_h, foo_cpp,
	foo_o, bar_cpp, bar_o, libfoobar_a,
	zig_cpp, zig_o, zag_cpp, zag_o,
	libzigzag_a, killerapp, FILE_MAX
};

const char* name[] = { "dax.h", "yow.h", "boz.h", "zow.h", "foo.cpp",
					"foo.o", "bar.cpp", "bar.o", "libfoobar.a",
					"zig.cpp", "zig.o", "zag.cpp", "zag.o",
					"libzigzag.a", "killerapp" };

typedef std::pair<int, int> Edge;

Edge used_by[] = {
	Edge(dax_h, foo_cpp), Edge(dax_h, bar_cpp), Edge(dax_h, yow_h),
	Edge(yow_h, bar_cpp), Edge(yow_h, zag_cpp),
	Edge(boz_h, bar_cpp), Edge(boz_h, zig_cpp), Edge(boz_h, zag_cpp),
	Edge(zow_h, foo_cpp),
	Edge(foo_cpp, foo_o),
	Edge(foo_o, libfoobar_a),
	Edge(bar_cpp, bar_o),
	Edge(bar_o, libfoobar_a),
	Edge(libfoobar_a, libzigzag_a),
	Edge(zig_cpp, zig_o),
	Edge(zig_o, libzigzag_a),
	Edge(zag_cpp, zag_o),
	Edge(zag_o, libzigzag_a),
	Edge(libzigzag_a, killerapp)
};

using namespace boost;

typedef adjacency_list<vecS, vecS, bidirectionalS,
	property<vertex_color_t, default_color_type>
> Graph;

typedef graph_traits<Graph>::vertex_descriptor Vertex;

void CompilationOrder(const Graph& g, std::list<Vertex>& orderedMakeFiles )
{

	boost::topological_sort(g, std::front_inserter(orderedMakeFiles));

	std::cout << "make ordering: ";
	for (const auto& i : orderedMakeFiles)
		std::cout << name[i] << " ";

	std::cout << std::endl;
}

void ParallelCompilation(const Graph& g, std::list<Vertex>& orderedMakeFiles)
{
	std::vector<int> time(FILE_MAX, 0);
	
	for (auto i = orderedMakeFiles.begin(); i != orderedMakeFiles.end(); ++i) {
		if (in_degree(*i, g) > 0) {
			Graph::in_edge_iterator j, j_end;
			int maxdist = 0;
			for (tie(j, j_end) = in_edges(*i, g); j != j_end; ++j)
				maxdist = std::max(time[source(*j, g)], maxdist);
			time[*i] = maxdist + 1;
		}
	}
	
	graph_traits<Graph>::vertex_iterator i, iend;

	std::cout << "parallel make ordering, " << std::endl
		<< "  vertices with same group number" << std::endl
		<< "  can be made in parallel" << std::endl << std::endl;
	for (boost::tie(i, iend) = vertices(g); i != iend; ++i)
		std::cout << "time_slot[" << name[*i] << "] = " << time[*i] << std::endl;
}

struct cycle_detector : public dfs_visitor<>
{
	cycle_detector(bool& has_cycle)
		: _has_cycle(has_cycle) { }

	template <class Edge, class Graph>
	void back_edge(Edge, Graph&) {
		_has_cycle = true;
	}
protected:
	bool& _has_cycle;
};

void checkCycle(const Graph& g)
{
	bool has_cycle = false;
	cycle_detector vis(has_cycle);
	boost::depth_first_search(g, visitor(vis));
	std::cout << "The graph has a cycle? " << has_cycle << std::endl;
}

void testDependencyGraph() 
{
	
	auto size = used_by + sizeof(used_by) / sizeof(Edge);
	Graph g(used_by, size , FILE_MAX);

	std::list<Vertex> orderedMakeFiles;
	CompilationOrder(g, orderedMakeFiles);
	ParallelCompilation(g, orderedMakeFiles);
	checkCycle(g);

}
