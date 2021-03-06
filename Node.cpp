#include <iostream>
#include <string>
#include "Node.hpp"

using namespace std;

Node::Node(int key)
{
  key_value = key;
}

Node::~Node(){
    //delete children;
}

int Node::get_key(){
    return this->key_value;
}

int Node::number_of_children(){
    return this->children.size();
}

void Node::add_child(Node* node){
    this->children.insert(node);
}

set<Node *> &Node::get_children(){
    return this->children;
}

Node* Node::get_parent(){
    return this->parent;
}

void Node::set_parent(Node* parent){
    this->parent = parent;
}

void Node::display_children(){
    for (set<Node*>::iterator it = this->children.begin() ; it != this->children.end(); ++it)
        cout << (*it)->get_key() << " ";
    cout << endl;
}
