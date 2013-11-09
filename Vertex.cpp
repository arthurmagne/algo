#include <iostream>
#include <string>
#include "Vertex.hpp"

Vertex::Vertex(int key_value)
{
    this->key_value = key_value;
}

Vertex::~Vertex(){
    //delete neighbours;
}

int Vertex::get_key(){
    return this->key_value;
}

int Vertex::get_number_of_neighbours(){
    return this->neighbours.size();
}

void Vertex::add_neighbour(Vertex * vertex){
    this->neighbours.insert(vertex);
}

set<Vertex *> &Vertex::get_neighbours(){
    return this->neighbours;
}

void Vertex::display_neighbours(){
    for (set<Vertex*>::iterator it = this->neighbours.begin() ; it != this->neighbours.end(); ++it)
        cout << (*it)->get_key() << " ";
    cout << endl;
}
