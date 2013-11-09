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
set<Vertex*> Algorithms::greedy_algorithm(Graph *any_graph){
    // We do have an adjacency list : all vertexes already have a list of neighbours!
    vector<Vertex*> vertexes = any_graph->get_vertexes_copy();
    cout << " la taille est de :" << vertexes.size() << endl;
    set<Vertex*> cover;
    bool contains_edges = true;
    while (contains_edges){
        contains_edges = false;
        for (vector<Vertex*>::iterator current = vertexes.begin() ; current != vertexes.end(); ++current){
            // we pick an edge randomly (the first one in our adjacency list)
            if ((*current)->get_neighbours().size() == 0){
                // if we don't have neighbours, continue
                continue;
            }else{
                contains_edges = true;
                Vertex* first = (*current);
                Vertex* last = (*(*current)->get_neighbours().begin());

                cover.insert(first);
                cover.insert(last);

                // First we absolutly need to remove those edges in the others list !
                /* to refactor */
                // remove edges sibbling first vertex
                for (set<Vertex*>::iterator it = first->get_neighbours().begin() ; it != first->get_neighbours().end(); ++it){
                    (*it)->get_neighbours().erase(first);

                }

                // do the same for the other vertex
                for (set<Vertex*>::iterator it = last->get_neighbours().begin() ; it != last->get_neighbours().end(); ++it){
                    (*it)->get_neighbours().erase(last);
                }

                // remove this node and the first one in his neighbours list
                first->get_neighbours().clear();
                last->get_neighbours().clear();
                break;

            }
        }
        Utils::display_graph(any_graph);

    }

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
