#include <iostream>
#include "Tree.hpp"
#include "Utils.hpp"
#include "Graph.hpp"
#include "Algorithms.hpp"

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

    Graph * graph_with_cover = Graph::generate_graph_with_min_cover(10, 4, 0.25);
    cout << endl << "On génère un graphe avec une couverture de taille 4 à " << graph_with_cover->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(graph_with_cover);

    /* Algo */
    cout << endl << "Greedy algorithm: " << endl;
    set<Vertex*> greedy_cover = Algorithms::greedy_algorithm(graph_with_cover);
    for (set<Vertex*>::iterator it = greedy_cover.begin() ; it != greedy_cover.end(); ++it){
        cout << (*it)->get_key() ;
    }

    Graph * graph_with_cover_2 = Graph::generate_graph_with_min_cover(10, 4, 0.25);
    cout << endl << "2-aprox algorithm: " << endl;
    set<Vertex*> cover = Algorithms::two_aprox_algorithm(graph_with_cover_2);
    for (set<Vertex*>::iterator it = cover.begin() ; it != cover.end(); ++it){
        cout << (*it)->get_key() ;
    }
    cout << endl;
    /*cout << endl << "Génération d'un graphe à partir d'un fichier contenant une liste d'adjacence' " << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Graph * g = Graph::generate_graph_from_file("../../../Documents/CAA/algo/file");
    Utils::display_graph(g);
    cout << endl;*/
}
