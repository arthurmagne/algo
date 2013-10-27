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
  if(current->children->size() == 0){
      cout << "on a pas de fils on add ici" << endl;
     Node child(val);
     current->children->push_back(child);
     return;
  }

  cout << "on a un fils number of children" << current->children->size() << endl;

  // This number will be an integer between 1 and the number of children of our current node + 1
  // (because we can insert our node directly in the current node)
  srand(time(NULL));
  int randomNumber = rand() % (current->children->size() + 1);
  cout << "On a passé le rand : " << randomNumber << endl;

  // We need to subtract one to select the child number 0
  // We insert the node here
  if(randomNumber == current->children->size()){
      cout << "on insert ici meme a cause du rand" << endl;
      Node child(val);
      current->children->push_back(child);
      return;
  }
  cout << "on appel récursivement " << &current->children->at(randomNumber) << endl;

  random_insert(val, &current->children->at(randomNumber));

}

 

Node* Node::generate_tree(int nb_vertices)
{

  Node root(0);
  for(int i=1; i<nb_vertices; i++){
      cout << "insert" << i << endl;
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
