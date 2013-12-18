#include <iostream>
#include <stdlib.h>
#include <time.h>
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

     if (argv[1] == std::string("generate_tree_from_file")){
         cout << endl << "Génération d'un arbre à partir d'un fichier contenant une liste d'adjacence' " << endl;
         cout << "La liste d'adjacences obtenue est la suivante: " << endl;
         //Tree * t = Utils::generate_graph_from_file(argv[2]);
         //Utils::display_tree(t);
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
            cout << (*it)->get_key() << " " ;
        }
        cout << endl << "La taille de la couverture est : " << endl << optimal_tree_cover.size();
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

    else if(argv[1] == std::string("bi_part_algorithm")){
        std::string arg2 = argv[2];
        std::string arg3 = argv[3];

        Graph * bipartite_graph = Graph::generate_bipartite_graph(atoi(arg2.c_str()), atof(arg3.c_str()));
        Utils::display_graph(bipartite_graph);
        set<Vertex*> cover_biPart = Algorithms::bi_part_algorithm(bipartite_graph);
        cout << endl << "La couverture est " << endl;
        for (set<Vertex*>::iterator it = cover_biPart.begin() ; it != cover_biPart.end(); ++it){
            cout << (*it)->get_key() ;
        }
        cout << endl;
    }

     /* perf tests */
    set<int> testSuite;
    testSuite.insert(10);
    testSuite.insert(50);
    testSuite.insert(100);
    testSuite.insert(130);
    testSuite.insert(1000);
    testSuite.insert(3000);

    /*for (set<int>::iterator it = testSuite.begin(); it != testSuite.end(); ++it){
        Graph* graph_origin = Graph::generate_graph(*it, 0.25);
         int start = clock();
        Algorithms::greedy_algorithm(graph_origin);
         int end = clock();
         std::cout << "for " << *it << "vertexes, it took " << end - start << "ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "s" << endl;

    }

    else if(argv[1] == std::string("parametric")){
         if(argc == 5){
             std::string arg2 = argv[2];
             std::string arg3 = argv[3];
             std::string arg4 = argv[4];
             Graph * para = Graph::generate_graph(atoi(arg2.c_str()), atof(arg3.c_str()));
             Utils::display_graph(para);

             set<int> cover = Algorithms::parametric_algorithm(para, atoi(arg4.c_str()));
             for (set<int>::iterator it = cover.begin() ; it != cover.end(); ++it){
                 cout << *it << " ";
             }
             cout << endl;

         }
         else if(argc == 4){
             Graph * para = Graph::generate_graph_from_file(argv[2]);
             std::string arg3 = argv[3];
             Utils::display_graph(para);
             set<int> cover = Algorithms::parametric_algorithm(para, atoi(arg3.c_str()));
             for (set<int>::iterator it = cover.begin() ; it != cover.end(); ++it){
                 cout << *it << " ";
             }
             cout << endl;
         }
     }


     else if(argv[1] == std::string("reduction_sat")){

            cout << "AVANT" << endl;
            Graph * graph = Graph::generate_graph(10,0.5);
            Utils::display_graph(graph);
            Algorithms::reduction_SAT(graph,8);




            cout << "REDUCTION" << endl;
     }

     else if(argv[1] == std::string("find_cover_minisat")){




             set <int> cover = Algorithms::find_cover_minisat(argv[2],argv[3]);
             cout << "La couverture est :" << endl;
           for (set<int>::iterator it = cover.begin() ; it != cover.end(); ++it){
           cout << (*it) << " - " ;
           }
           cout << endl;




    }






    for (set<int>::iterator it = testSuite.begin(); it != testSuite.end(); ++it){
        Tree* tree_origin = Tree::generate_tree(*it);

         int start = clock();
        Algorithms::Algorithms::optimal_tree(tree_origin);
        cout << "on rentre" << endl;

         int end = clock();
         std::cout << "for " << *it << "nodes, it took " << end - start << "ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "s" << endl;

    }



    for (set<int>::iterator it = testSuite.begin(); it != testSuite.end(); ++it){
        Graph* graph_origin = Graph::generate_bipartite_graph(*it, 0.25);
         int start = clock();
        Algorithms::bi_part_algorithm(graph_origin);
         int end = clock();
         std::cout << "for " << *it << "vertexes, it took " << end - start << "ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "s" << endl;

    }

    for (set<int>::iterator it = testSuite.begin(); it != testSuite.end(); ++it){
        Graph* graph_origin = Graph::generate_graph(*it, 0.25);
         int start = clock();
        Algorithms::two_aprox_first_depth(graph_origin);
         int end = clock();
         std::cout << "for " << *it << "vertexes, it took " << end - start << "ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "s" << endl;

    }

    for (set<int>::iterator it = testSuite.begin(); it != testSuite.end(); ++it){
        Graph* graph_origin = Graph::generate_graph(*it, 0.25);
         int start = clock();
        Algorithms::two_aprox_algorithm(graph_origin);
         int end = clock();
         std::cout << "for " << *it << "vertexes, it took " << end - start << "ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "s" << endl;

    }

    for (set<int>::iterator it = testSuite.begin(); it != testSuite.end(); ++it){
        Graph* graph_origin = Graph::generate_graph_with_min_cover(*it, *it/3, 0.25);
         int start = clock();
        Algorithms::parametric_algorithm(graph_origin,*it/3);
         int end = clock();
         std::cout << "for " << *it << "vertexes, it took " << end - start << "ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "s" << endl;

    }*/

    Graph * test = new Graph();
    std::vector<Edge *> edges;
    std::vector<Vertex *> vertex;
    Vertex* v1 = new Vertex(0);
    Vertex* v2 = new Vertex(1);
    Vertex* v3 = new Vertex(2);
    Vertex* v4 = new Vertex(3);
    Vertex* v5 = new Vertex(4);
    Vertex* v6 = new Vertex(5);
    Vertex* v7 = new Vertex(6);
    Vertex* v8 = new Vertex(7);
    Vertex* v9 = new Vertex(8);
    Vertex* v10 = new Vertex(9);
    Vertex* v11 = new Vertex(10);
    v1->add_neighbour(v2);
    v1->add_neighbour(v3);
    edges.push_back(new Edge(v1, v2));
    edges.push_back(new Edge(v1, v3));
    v2->add_neighbour(v1);
    v2->add_neighbour(v3);
    v2->add_neighbour(v4);
    edges.push_back(new Edge(v2, v1));
    edges.push_back(new Edge(v2, v3));
    edges.push_back(new Edge(v2, v4));
    v3->add_neighbour(v1);
    v3->add_neighbour(v2);
    v3->add_neighbour(v4);
    edges.push_back(new Edge(v3, v1));
    edges.push_back(new Edge(v3, v2));
    edges.push_back(new Edge(v3, v4));
    v4->add_neighbour(v3);
    v4->add_neighbour(v2);
    edges.push_back(new Edge(v4, v3));
    edges.push_back(new Edge(v4, v2));
    v5->add_neighbour(v6);
    v5->add_neighbour(v7);
    edges.push_back(new Edge(v5, v6));
    edges.push_back(new Edge(v5, v7));
    v6->add_neighbour(v5);
    v6->add_neighbour(v7);
    v6->add_neighbour(v8);
    edges.push_back(new Edge(v6, v5));
    edges.push_back(new Edge(v6, v7));
    edges.push_back(new Edge(v6, v8));
    v7->add_neighbour(v5);
    v7->add_neighbour(v6);
    v7->add_neighbour(v8);
    edges.push_back(new Edge(v7, v5));
    edges.push_back(new Edge(v7, v6));
    edges.push_back(new Edge(v7, v8));
    v8->add_neighbour(v7);
    v8->add_neighbour(v6);
    v8->add_neighbour(v9);
    edges.push_back(new Edge(v8, v7));
    edges.push_back(new Edge(v8, v6));
    edges.push_back(new Edge(v8, v9));
    v9->add_neighbour(v8);
    v9->add_neighbour(v10);
    edges.push_back(new Edge(v9, v8));
    edges.push_back(new Edge(v9, v10));
    v10->add_neighbour(v8);
    edges.push_back(new Edge(v10, v8));
    vertex.push_back(v1);
    vertex.push_back(v2);
    vertex.push_back(v3);
    vertex.push_back(v4);
    vertex.push_back(v5);
    vertex.push_back(v6);
    vertex.push_back(v7);
    vertex.push_back(v8);
    vertex.push_back(v9);
    vertex.push_back(v10);
    vertex.push_back(v11);
    test->vertexes = vertex;
    test->edges = edges;
    Utils::display_graph(test);
    //Utils::display_graph(para);
    set<int> cover = Algorithms::parametric_algorithm(test, 17);
    for (set<int>::iterator it = cover.begin() ; it != cover.end(); ++it){
       cout << *it << " ";
    }
    cout << endl;





    return 0;
}
