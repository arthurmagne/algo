#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include "TreeEdge.hpp"

class Tree
{
public:
    Tree(Node * root);
    ~Tree();
    static Tree *generate_tree(int nb_vertices);
    void random_insert(Node *leaf);
    //void display_subtree(Node * subtree);
    int get_number_of_nodes();
    vector<Node*>::iterator get_iterator_begin();
    vector<Node*>::iterator get_iterator_end();


private:
    Node* root;
    vector<Node *> nodes;
    vector<TreeEdge *> edges;
};

#endif // TREE_HPP

