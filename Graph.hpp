#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include "Vertex.hpp"
#include "Edge.hpp"
#include <set>
#include <map>

class Graph
{
public:
    Graph();
    ~Graph();
    static Graph * generate_graph(int number_of_vertexes, double p);
    static Graph * generate_bipartite_graph(int number_of_vertexes, double p);
    static Graph * generate_graph_with_min_cover(int number_of_vertexes, int cover_size, double p);
    int get_number_of_vertexes();
    vector<Vertex*>::iterator get_iterator_begin();
    vector<Vertex*>::iterator get_iterator_end();
    vector<Vertex *> get_vertexes_copy();
    vector<Edge *> get_edges_copy();


private:
    vector<Vertex *> vertexes;
    vector<Edge *> edges;

};

#endif // GRAPH_HPP
