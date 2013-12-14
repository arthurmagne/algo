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

int Vertex::get_color(){
    return this->color;
}

void Vertex::set_color(int color){
    this->color=color;
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

void Vertex::add_pred(Vertex * vertex){
    this->pred.insert(vertex);
}

void Vertex::add_succ(Vertex * vertex){
    this->succ.insert(vertex);
}

set<Vertex *> &Vertex::get_neighbours(){
    return this->neighbours;
}

set<Vertex *> &Vertex::get_pred(){
    return this->pred;
}

set<Vertex *> &Vertex::get_succ(){
    return this->succ;
}

Vertex* Vertex::get_parent(){
    return this->parent;
}

void Vertex::set_parent(Vertex * parent){
     this->parent = parent;
}

void Vertex::display_neighbours(){
    for (set<Vertex*>::iterator it = this->neighbours.begin() ; it != this->neighbours.end(); ++it)
        cout << (*it)->get_key() << " ";
    cout << endl;
}
