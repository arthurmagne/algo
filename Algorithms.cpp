#include "Algorithms.hpp"
#include "Utils.hpp"
#include <iostream>


using namespace std;

/* We'll work only with adjacency list */

Algorithms::Algorithms()
{
}

/* A greedy algorithm always makes the choice that looks best at the moment.
*  The greedy heuristic cannot always find an optimal solution!
*  If the graph is represented by an adjacency list this can be implemented in O(m + n) time. */
vector<Vertex*> Algorithms::greedy_algorithm(Graph *any_graph){
    // We do have an adjacency list : all vertexes already have a list of neighbours!
    vector<Vertex*> vertexes = any_graph->get_vertexes_copy();
    cout << " la taille est de :" << vertexes.size() << endl;
    vector<Vertex*> cover;
    bool contains_edges = true;
    while (contains_edges){
        contains_edges = false;
        for (vector<Vertex*>::iterator current = vertexes.begin() ; current != vertexes.end(); ++current){
            // we pick an edge randomly (the first one in our adjacency list)
            if ((*current)->get_neighbours().size() == 0){
                // if we don't have neighbours, continue
                cout << "on a pas de voisins on est " << (*current)->get_key() << endl;
                continue;
            }else{
                contains_edges = true;
                Vertex* first = (*current);
                Vertex* last = (*current)->get_neighbours()[0];

                cover.push_back(first);
                cover.push_back(last);
                cout << "le current est " << first->get_key() << " celui qu'on trouve " << last->get_key() << endl;

                // First we absolutly need to remove those edges in the others list !
                /* to refactor */
                // remove edges sibbling first vertex
                for (vector<Vertex*>::iterator it = first->get_neighbours().begin()+1 ; it != first->get_neighbours().end(); ++it){
                    cout << " On est dans le for " << endl;
                    cout << " On veut supprimer " << first->get_key() << endl;
                    cout << " dans " << (*it)->get_key() << endl;

                    (*it)->get_neighbours().erase(remove((*it)->get_neighbours().begin(), (*it)->get_neighbours().end(), first), (*it)->get_neighbours().end());
                    cout << " On a passé le truc " << endl;

                }

                // do the same for the other vertex
                for (vector<Vertex*>::iterator it = last->get_neighbours().begin()+1 ; it != last->get_neighbours().end(); ++it){
                    (*it)->get_neighbours().erase(remove((*it)->get_neighbours().begin(), (*it)->get_neighbours().end(), last), (*it)->get_neighbours().end());
                    cout << " On a passé le second (last) on affiche ------ " << endl;

                }

                Utils::display_graph(any_graph);


                // remove this node and the first one in his neighbours list
                // !! always remove the neighbour first (before the current, the current can change otherwise)
                vertexes.erase(remove(vertexes.begin(), vertexes.end(), last), vertexes.end());


                cout << " la taille aprés suppr first neigh:" << last->get_key() << " " << vertexes.size() << endl;
                cout << " la taille avant suppr :" << first->get_key() << " " << vertexes.size() << endl;
                vertexes.erase(remove(vertexes.begin(), vertexes.end(), first), vertexes.end());

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
