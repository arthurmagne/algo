#include "TreeEdge.hpp"

TreeEdge::TreeEdge(Node * node1, Node * node2)
{
    this->node1 = node1;
    this->node2 = node2;
}

Node * TreeEdge::get_node1(){
    return this->node1;
}

Node * TreeEdge::get_node2(){
    return this->node2;
}
