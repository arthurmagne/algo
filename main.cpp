#include <iostream>
#include <stdlib.h>
#include "Tree.hpp"
#include "Utils.hpp"
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace std;

int main(int argc,char *argv[])
{
    if(argc < 2){
        cout << "not enough arguments, usage: [algorithm_name][file_path]" << endl;
        cout << "[algorithm_name][size_graph][probability]" << endl;
        cout << "[algorithm_name][size_graph][cover_size][probability]" << endl;
        return 0;
    }

    if (argv[1] == std::string("generate_graph_from_file"))
    {
        cout << endl << "Génération d'un graphe à partir d'un fichier contenant une liste d'adjacence' " << endl;
        cout << "La liste d'adjacences obtenue est la suivante: " << endl;
        Graph * g = Graph::generate_graph_from_file(argv[2]);
        Utils::display_graph(g);
        cout << endl;;
    }


    else if(argv[1] == std::string("greedy_algorithm")){
        Graph* graph_origin = Graph::generate_graph_from_file(argv[2]);
        set<Vertex*> greedy_cover = Algorithms::greedy_algorithm(graph_origin->get_graph_copy());
        for (set<Vertex*>::iterator it = greedy_cover.begin() ; it != greedy_cover.end(); ++it){
            cout << (*it)->get_key() << " ";
        }
        cout << endl;
    }

    else if(argv[1] == std::string("generate_graph")){
        std::string arg2 = argv[2];
        std::string arg3 = argv[3];
        Graph * graph_origin = Graph::generate_graph(atoi(arg2.c_str()), atof(arg3.c_str()));
        cout << endl << "On génère un graphe à " << graph_origin->get_number_of_vertexes() << " sommets." << endl;
        cout << "La liste d'adjacences obtenue est la suivante: " << endl;
        Utils::display_graph(graph_origin);
    }

    else if(argv[1] == std::string("generate_tree")){
        std::string arg2 = argv[2];
        Tree * tree = Tree::generate_tree(atoi(arg2.c_str()));
        cout << endl << "On génère un arbre à " << tree->get_number_of_nodes() << " noeuds." << endl;
        cout << "La liste d'adjacences obtenue est la suivante: " << endl;
        Utils::display_tree(tree);
    }

    else if(argv[1] == std::string("generate_bipartite")){
        std::string arg2 = argv[2];
        std::string arg3 = argv[3];
        Graph * bipartite_graph = Graph::generate_bipartite_graph(atoi(arg2.c_str()), atof(arg3.c_str()));
        cout << endl << "On génère un graphe biparti à " << bipartite_graph->get_number_of_vertexes() << " sommets." << endl;
        cout << "La liste d'adjacences obtenue est la suivante: " << endl;
        Utils::display_graph(bipartite_graph);
    }

    else if(argv[1] == std::string("generate_graph_with_min_cover")){
        std::string arg2 = argv[2];
        std::string arg3 = argv[3];
        std::string arg4 = argv[4];
        Graph * graph_with_cover_origin = Graph::generate_graph_with_min_cover(atoi(arg2.c_str()), atoi(arg3.c_str()),atof(arg4.c_str()) );
        cout << endl << "On génère un graphe avec une couverture de taille " + arg3 + " à " << graph_with_cover_origin->get_number_of_vertexes() << " sommets." << endl;
        cout << "La liste d'adjacences obtenue est la suivante: " << endl;
        Utils::display_graph(graph_with_cover_origin);
    }

    else if(argv[1] == std::string("two_approx_algorithm")){
        Graph * graph = Graph::generate_graph_from_file(argv[2]);
        set<Vertex*> cover = Algorithms::two_aprox_algorithm(graph);
        for (set<Vertex*>::iterator it = cover.begin() ; it != cover.end(); ++it){
            cout << (*it)->get_key() << " ";
        }
        cout << endl;
    }

    else if(argv[1] == std::string("optimal_tree")){
        std::string arg2 = argv[2];
        Tree * tree = Tree::generate_tree(atoi(arg2.c_str()));
        Utils::display_tree(tree);
        set<Node*> optimal_tree_cover = Algorithms::optimal_tree(tree->get_tree_copy());
        cout << endl << "La couverture est " << endl;
        for (set<Node*>::iterator it = optimal_tree_cover.begin() ; it != optimal_tree_cover.end(); ++it){
            cout << (*it)->get_key() ;
        }
        cout << endl << "Fin optimal tree" << endl;
        cout << endl;
    }

    else if(argv[1] == std::string("two_approx_first_depth")){
        Graph * graph = Graph::generate_graph_from_file(argv[2]);
        std::vector<Vertex*> s = Algorithms::two_aprox_first_depth(graph);
        for(int i = 0; i<s.size(); i++){
            cout << s[i]->get_key() << " ";
        }
        cout << endl;
    }


    return 0;
}
