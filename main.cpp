#include <iostream>
#include "Tree.hpp"
#include "Utils.hpp"

using namespace std;

int main()
{
    Tree * tree = Tree::generate_tree(10);
    cout << endl << "On génère un arbre à " << tree->get_number_of_nodes() << " noeuds." << endl;
    cout << "La liste d'adjacences obtenue est la suivante: " << endl;
    Utils::display(tree);
    return 0;
}
