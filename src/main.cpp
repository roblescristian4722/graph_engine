#include <iostream>
#include "base_graph.hpp"

using namespace std;
using namespace gph;

int main()
{
    Graph<int> g("334F");
    cout << g.vertex_exists("2") << endl
         << g.vertex_exists("1") << endl;
    g.add_vertex("1", 34);
    g.add_vertex("2", 35);
    g.add_vertex("4", 36);
    g.add_edge("1", "2", 23);
    cout << g.vertex_exists("2") << endl
         << g.vertex_exists("1") << endl
         << g.edge_exists("1", "2") << endl;



    return 0;
}