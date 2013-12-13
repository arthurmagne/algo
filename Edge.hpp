#ifndef EDGE_HPP
#define EDGE_HPP

#include "Vertex.hpp"

class Edge
{
public:
    Edge(Vertex * vertex1, Vertex * vertex2);
    Vertex * get_vertex1();
    Vertex * get_vertex2();
    int get_flow();
    void set_flow(int flow);

private:
    Vertex * vertex1;
    Vertex * vertex2;
    int flow;

};

#endif // EDGE_HPP
