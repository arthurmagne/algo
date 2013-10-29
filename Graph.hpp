#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include "Vertex.hpp"
#include "Edge.hpp"

class Graph
{
public:
    Graph();
    ~Graph();
    static Graph * generate_graph(int number_of_vertexes, double p);
    static Graph * generate_bipartite_graph(int number_of_vertexes, double p);
    int get_number_of_vertexes();
    vector<Vertex*>::iterator get_iterator_begin();
    vector<Vertex*>::iterator get_iterator_end();

private:
    vector<Vertex *> vertexes;
    vector<Edge *> edges;

};

#endif // GRAPH_HPP
