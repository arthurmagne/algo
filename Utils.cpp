#include <iostream>
#include <string>
#include "Utils.hpp"
#include "Node.hpp"

Utils::Utils()
{
}

void Utils::display(Tree * tree){
    cout << tree->get_number_of_nodes() << endl;
    for (vector<Node*>::iterator it = tree->get_iterator_begin() ; it != tree->get_iterator_end(); ++it){
        if ((*it)->number_of_children() == 0)
            continue;
        cout << (*it)->get_key() << ": ";
        (*it)->display_children();
    }
}
