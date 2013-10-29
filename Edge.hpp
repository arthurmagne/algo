#ifndef EDGE_HPP
#define EDGE_HPP

#include "Vertex.hpp"

class Edge
{
public:
    Edge(Vertex * vertex1, Vertex * vertex2);

private:
    Vertex * vertex1;
    Vertex * vertex2;

};

#endif // EDGE_HPP