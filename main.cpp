#include <iostream>
#include "Tree.hpp"
#include "Utils.hpp"
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace std;

int main()
{
    /*Tree * tree = Tree::generate_tree(10);
    cout << endl << "On génère un arbre à " << tree->get_number_of_nodes() << " noeuds." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_tree(tree);*/

    Graph * graph_bi = Graph::generate_bipartite_graph(5, 0.5);
    cout << endl << "On génère un graphe bipartie à " << graph_bi->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
   // Utils::display_graph(graph_bi);

    Graph * test = new Graph();
    Vertex * v0 = new Vertex(0);
    Vertex * v1 = new Vertex(1);
    Vertex * v2 = new Vertex(2);
    Vertex * v3 = new Vertex(3);
    Vertex * v4 = new Vertex(4);
    Vertex * v5 = new Vertex(5);

    v0->add_neighbour(v1);
    v0->add_neighbour(v3);
    v0->add_neighbour(v5);

    v1->add_neighbour(v0);
    v1->add_neighbour(v2);
    v1->add_neighbour(v4);

    v2->add_neighbour(v1);
    v3->add_neighbour(v0);
    v4->add_neighbour(v1);
    v5->add_neighbour(v0);

    test->get_vertexes_copy().push_back(v0);
    test->get_vertexes_copy().push_back(v1);
    test->get_vertexes_copy().push_back(v2);
    test->get_vertexes_copy().push_back(v3);
    test->get_vertexes_copy().push_back(v4);
    test->get_vertexes_copy().push_back(v5);
    Utils::display_graph(test);






   /* Graph * graph_origin = Graph::generate_graph(10, 0.25);

    cout << endl << "On génère un graphe à " << graph_origin->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(graph_origin);

    Graph * bipartite_graph = Graph::generate_bipartite_graph(10, 0.25);
    cout << endl << "On génère un graphe biparti à " << bipartite_graph->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(bipartite_graph);

    Graph * graph_with_cover_origin = Graph::generate_graph_with_min_cover(10, 4, 0.25);
    cout << endl << "On génère un graphe avec une couverture de taille 4 à " << graph_with_cover_origin->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(graph_with_cover_origin);

    /* Algo
    cout << endl << "Greedy algorithm: " << endl;
    set<Vertex*> greedy_cover = Algorithms::greedy_algorithm(graph_with_cover_origin->get_graph_copy());
    for (set<Vertex*>::iterator it = greedy_cover.begin() ; it != greedy_cover.end(); ++it){
        cout << (*it)->get_key() ;
    }

    cout << endl << "2-aprox algorithm: " << endl;
    set<Vertex*> cover = Algorithms::two_aprox_algorithm(graph_with_cover_origin->get_graph_copy());
    for (set<Vertex*>::iterator it = cover.begin() ; it != cover.end(); ++it){
        cout << (*it)->get_key() ;
    }
    cout << endl;

    /*cout << endl << "Génération d'un graphe à partir d'un fichier contenant une liste d'adjacence' " << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Graph * g = Graph::generate_graph_from_file("../../../Documents/CAA/algo/file");
    Utils::display_graph(g);
    cout << endl;*/

   /* cout << endl << "Optimal Tree: " << endl;
    set<Node*> optimal_tree_cover = Algorithms::optimal_tree(tree->get_tree_copy());
    cout << endl << "La couverture est " << endl;
    for (set<Node*>::iterator it = optimal_tree_cover.begin() ; it != optimal_tree_cover.end(); ++it){
        cout << (*it)->get_key() ;
    }
    cout << endl << "Fin optimal tree" << endl;
    cout << endl;*/

   set<Vertex*> cover_bi = Algorithms::bi_part_algorithm(test);
   for (set<Vertex*>::iterator it = cover_bi.begin() ; it != cover_bi.end(); ++it){
       cout << (*it)->get_key() << "--" ;
   }
   cout << endl;

   /* Graph * graph_with_cover_origin = Graph::generate_graph_with_min_cover(10, 4, 0.25);
    cout << endl << "On génère un graphe avec une couverture de taille 4 à " << graph_with_cover_origin->get_number_of_vertexes() << " sommets." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display_graph(graph_with_cover_origin);


    Algorithms::parametric_algorithm(graph_with_cover_origin, 10);*/



}
