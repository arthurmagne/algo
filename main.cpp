#include <iostream>
#include "Tree.hpp"
#include "Utils.hpp"
#include "Graph.hpp"

using namespace std;

int main()
{
    Tree * tree = Tree::generate_tree(10);
    cout << endl << "On génère un arbre à " << tree->get_number_of_nodes() << " noeuds." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_tree(tree);

    Graph * graph = Graph::generate_graph(10, 0.25);
    cout << endl << "On génère un graphe à " << graph->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(graph);

    Graph * bipartite_graph = Graph::generate_bipartite_graph(10, 0.25);
    cout << endl << "On génère un graphe biparti à " << bipartite_graph->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(bipartite_graph);

    return 0;
}
