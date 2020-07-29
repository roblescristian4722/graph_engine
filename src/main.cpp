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
    cout << g.vertex_exists("2") << endl
         << g.vertex_exists("1") << endl;
    
    return 0;
}
