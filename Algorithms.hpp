#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Vertex.hpp"
#include "Graph.hpp"
#include "Node.hpp"
#include "Tree.hpp"
#include <queue>

using namespace std;

class Algorithms
{
public:
    Algorithms();
    static set<Vertex *> two_aprox_algorithm(Graph *any_graph);
    static set<Vertex*> greedy_algorithm(Graph *any_graph);
    static set<Node*> optimal_tree(Tree *any_tree);


    static set<Vertex*> bi_part_algorithm(Graph *any_graph);
    static void ford_fulkerson(queue<Vertex*> queue, Vertex* source, Vertex* terminal,set<Vertex*> part_S,set<Vertex*> part_T, int** edge_flow);


    static set<int> parametric_algorithm_impl(Graph *any_graph, set<int> current_cover, int cpt, int k);
    static set<int> parametric_algorithm(Graph * current_graph, int k);


    static std::vector<Vertex*> two_aprox_first_depth(Graph* g);
    static std::vector<Vertex*> two_aprox_first_depth_rec(Graph * g, std::vector<Vertex*> s, Vertex* current, Vertex* prec, std::vector<int> keys);

};

#endif // ALGORITHMS_HPP
