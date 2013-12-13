#ifndef UTILS_HPP
#define UTILS_HPP

#include "Tree.hpp"
#include "Graph.hpp"
#include "Node.hpp"
#include "Vertex.hpp"
#include <fstream>
#include <cstring>


class Utils
{
public:
    Utils();
    static void display_tree(Tree * tree);
    static void display_graph(Graph * graph);
    static bool detect_cycle(char* filename);
    static void* generate_graph_from_file(char* filename);


};

#endif // UTILS_HPP
