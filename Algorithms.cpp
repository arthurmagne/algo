#include "Algorithms.hpp"
#include "Utils.hpp"
#include <iostream>


using namespace std;

/* We'll work only with adjacency list */

Algorithms::Algorithms()
{
}

/* A greedy algorithm always makes the choice that looks best at the moment. */
/* The greedy heuristic cannot always find an optimal solution! */
/* If the graph is represented by an adjacency list this can be implemented in O(m + n) time. */
vector<Vertex*> Algorithms::greedy_algorithm(Graph *any_graph){
    // We do have an adjacency list : all vertexes already have a list of neighbours!
    vector<Vertex*> vertexes = any_graph->get_vertexes_copy();
    cout << " la taille est de :" << vertexes.size() << endl;
    vector<Vertex*> cover;
    bool contains_edges = true;
    while (contains_edges){
        // [BUG] -> the adjacency list isn't correctly generate (some edges are missing)
        contains_edges = false;
        for (vector<Vertex*>::iterator current = vertexes.begin() ; current != vertexes.end(); ++current){
            // we pick an edge randomly (the first one in our adjacency list)
            if ((*current)->get_neighbours().size() == 0){
                // if we don't have neighbours, continue
                cout << "on a pas de voisins on est " << (*current)->get_key() << endl;
                continue;
            }else{
                contains_edges = true;
                cover.push_back(*current);
                cover.push_back((*current)->get_neighbours()[0]);
                cout << "le current" << (*current)->get_key() << " celui qu'on trouve " << ((*current)->get_neighbours()[0])->get_key() << endl;

                // remove this node and the first one in his neighbours list
                // !! always remove the neighbour first (before the current, the current can change otherwise)
                vertexes.erase(remove(vertexes.begin(), vertexes.end(), (*current)->get_neighbours()[0]), vertexes.end());

                cout << " la taille aprés suppr first neigh:" << ((*current)->get_neighbours()[0])->get_key() << " " << vertexes.size() << endl;
                cout << " la taille avant suppr :" << (*current)->get_key() << " " << vertexes.size() << endl;
                vertexes.erase(remove(vertexes.begin(), vertexes.end(), (*current)), vertexes.end());

                cout << " la taille APRES est de :" << vertexes.size() << endl;
                break;

            }
            cout << "oula on a des voisins!" << endl;

        }

        cout << "on est dans le WHILE!" << endl;

    }
    cout << "c'est la fin!" << endl;


    return cover;
}

/* maybe usefull later
vector* max_degree;

 *while (vertexes.size() != 0) {
    // We choose the vertex with the higher degree, add it to the cover
    // and remove it and his neighbours from the vertex vector
    for (vector<Vertex*>::iterator current = vertexes.begin() ; current != vertexes.end(); ++current){
        if (current == vertexes.begin())
            max_degree = *current;
        if ((*current)->get_number_of_neighbours() > max_degree->get_number_of_neighbours())
            max_degree = *current;
    }
    cover.push_back(max_degree);

    for (vector<Vertex*>::iterator current = vertexes.begin() ; current != vertexes.end(); ++current){

    }


}
*/
