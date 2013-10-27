#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Node.hpp"

using namespace std;

Node::Node(int key)
{
  key_value = key;
}

void Node::random_insert(int val, Node* current)
{
  // If the current node doesn't have any child, we put our node here
  if(current->children == NULL){
     Node child(val);
     current->children->push_back(child);
     return;
  }

  // This number will be an integer between 1 and the number of children of our current node + 1
  // (because we can insert our node directly in the current node)
  int randomNumber = rand() % current->children->size() + 1;

  // We need to subtract one to select the child number 0
  // We insert the node here
  if(randomNumber == current->children->size()){
      Node child(val);
      current->children->push_back(child);
      return;
  }
  random_insert(val, &current->children->at(randomNumber-1));

}

 

Node* Node::generate_tree(int nb_vertices)
{
  Node root(0);
  for(int i=1; i<nb_vertices; i++){
    random_insert(i, &root);
  }
  return &root;
}

string Node::display_tree(){
    string tree;
    tree += this->children->size();
    for (vector<Node>::iterator it = this->children->begin() ; it != this->children->end(); ++it){
        cout << it->key_value << " : " ;
        cout << '\n';
    }
    return tree;
}
