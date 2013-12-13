#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Vertex.hpp"
#include "Graph.hpp"
#include "Node.hpp"
#include "Tree.hpp"

using namespace std;

class Algorithms
{
public:
    Algorithms();
    static set<Vertex *> two_aprox_algorithm(Graph *any_graph);
    static set<Vertex*> greedy_algorithm(Graph *any_graph);
    static set<Node*> optimal_tree(Tree *any_tree);
    static set<int> parametric_algorithm_impl(Graph *any_graph, set<int> current_cover, int cpt, int k);
    static set<int> parametric_algorithm(Graph * current_graph, int k);

    static set<Vertex*> two_aprox_first_depth(Graph* g);
    static void two_aprox_first_depth_rec(set<Vertex*> s, Vertex* current, Vertex* prec);

};

#endif // ALGORITHMS_HPP
