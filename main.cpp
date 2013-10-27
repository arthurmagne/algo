#include <iostream>
#include "Node.hpp"

using namespace std;

int main()
{
    Node * node = Node::generate_tree(5);
    cout << "Hello World!" << node->display_tree() << endl;
    return 0;
}
