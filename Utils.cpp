#include <iostream>
#include <string>
#include "Utils.hpp"


using std::cout;
using std::endl;
using std::ifstream;

Utils::Utils()
{
}

void Utils::display_tree(Tree * tree){
    cout << tree->get_number_of_nodes() << endl;
    for (vector<Node*>::iterator it = tree->get_iterator_begin() ; it != tree->get_iterator_end(); ++it){
        if ((*it)->number_of_children() == 0)
            continue;
        cout << (*it)->get_key() << ": ";
        (*it)->display_children();
    }
}

void Utils::display_graph(Graph * graph){
    cout << graph->get_number_of_vertexes() << endl;
    for (vector<Vertex*>::iterator it = graph->get_iterator_begin() ; it != graph->get_iterator_end(); ++it){
        if ((*it)->get_number_of_neighbours() == 0)
            continue;
        cout << (*it)->get_key() << ": ";
        (*it)->display_neighbours();
    }
}



