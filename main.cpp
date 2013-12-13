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

    Graph * graph_origin = Graph::generate_graph(10, 0.25);

    cout << endl << "On génère un graphe à " << graph_origin->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(graph_origin);

    Graph * bipartite_graph = Graph::generate_bipartite_graph(10, 0.25);
    cout << endl << "On génère un graphe biparti à " << bipartite_graph->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(bipartite_graph);

    Graph * graph_with_cover_origin = Graph::generate_graph_with_min_cover(30, 7, 0.25);
    cout << endl << "On génère un graphe avec une couverture de taille 4 à " << graph_with_cover_origin->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(graph_with_cover_origin);

    //Algo

    cout << endl << "Parametric algorithm: " << endl;
    set<int> greedy_cover = Algorithms::parametric_algorithm(graph_with_cover_origin->get_graph_copy(), 8);
    // If the result is a set containing -1 that mean that the algorithm couldn't find a cover smaller than k
    cout << "le cover obtenu est : " ;
    for (set<int>::iterator it = greedy_cover.begin(); it != greedy_cover.end() ; ++it)
        cout << *it << " ";
    cout << endl;


    /*cout << endl << "Greedy algorithm: " << endl;
    set<Vertex*> greedy_cover = Algorithms::greedy_algorithm(graph_with_cover_origin->get_graph_copy());

    cout << endl << "La couverture trouvée par Greedy algorithm est : ";
    for (set<Vertex*>::iterator it = greedy_cover.begin() ; it != greedy_cover.end(); ++it){
        cout << (*it)->get_key();
    }

    cout << endl << "2-aprox algorithm: " << endl;
    set<Vertex*> cover = Algorithms::two_aprox_algorithm(graph_with_cover_origin->get_graph_copy());
    for (set<Vertex*>::iterator it = cover.begin() ; it != cover.end(); ++it){
        cout << (*it)->get_key() ;
    }
    cout << endl;

    cout << endl << "Génération d'un graphe à partir d'un fichier contenant une liste d'adjacence' " << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Graph * g = Graph::generate_graph_from_file("../../../Documents/CAA/algo/file");
    Utils::display_graph(g);
    cout << endl;

    cout << endl << "Optimal Tree: " << endl;
    set<Node*> optimal_tree_cover = Algorithms::optimal_tree(tree->get_tree_copy());
    cout << endl << "La couverture est " << endl;
    for (set<Node*>::iterator it = optimal_tree_cover.begin() ; it != optimal_tree_cover.end(); ++it){
        cout << (*it)->get_key() ;
    }
    cout << endl << "Fin optimal tree" << endl;
    cout << endl;

    Graph * graph_with_cover_origin = Graph::generate_graph_with_min_cover(10, 4, 0.25);
    cout << endl << "On génère un graphe avec une couverture de taille 4 à " << graph_with_cover_origin->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(graph_with_cover_origin);


    //Algorithms::parametric_algorithm(graph_with_cover_origin, 10);

*/

}
