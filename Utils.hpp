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
   // static Graph generate_graph_from_file(std::string filename);

};

#endif // UTILS_HPP
