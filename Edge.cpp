#include "Edge.hpp"

Edge::Edge(Vertex * vertex1, Vertex * vertex2)
{
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
}

Vertex * Edge::get_vertex1(){
    return this->vertex1;
}

Vertex * Edge::get_vertex2(){
    return this->vertex2;
}

int Edge::get_flow(){
    return this->flow;
}

void Edge::set_flow(int flow){
    this->flow = flow;
}
