#include <iostream>
#include <string>
#include "Node.hpp"

using namespace std;

Node::Node(int key)
{
  key_value = key;
}

int Node::get_key(){
    return this->key_value;
}

int Node::number_of_children(){
    return this->children.size();
}

void Node::add_child(Node* node){
    this->children.push_back(node);
}

void Node::display_children(){
    for (vector<Node*>::iterator it = this->children.begin() ; it != this->children.end(); ++it)
        cout << (*it)->get_key() << " ";
    cout << endl;
}
