#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Vertex.hpp"
#include "Graph.hpp"

using namespace std;

class Algorithms
{
public:
    Algorithms();
    static set<Vertex *> greedy_algorithm(Graph *any_graph);
};

#endif // ALGORITHMS_HPP
