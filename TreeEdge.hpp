#ifndef TREEEDGE_HPP
#define TREEEDGE_HPP

#include "Node.hpp"


class TreeEdge
{
public:
    TreeEdge(Node * node1, Node * node2);
    Node * get_node1();
    Node * get_node2();

private:
    Node * node1;
    Node * node2;
};

#endif // TREEEDGE_HPP
