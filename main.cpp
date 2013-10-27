#include <iostream>
#include "Node.hpp"

using namespace std;

int main()
{
    Node * node = Node::generate_tree(20);
    cout << endl << "On génère un arbre à " << node->get_number_of_nodes() << " noeuds." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    node->display_tree();
    return 0;
}
