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
  if(current->children.size() == 0){
     Node * child = new Node(val);
     current->children.push_back(child);
     return;
  }


  // This number will be an integer between 1 and the number of children of our current node + 1
  // (because we can insert our node directly in the current node)
  int randomNumber = rand() % (current->children.size() + 1);

  // We need to subtract one to select the child number 0
  // We insert the node here
  if(randomNumber == current->children.size()){
      Node * child = new Node(val);
      current->children.push_back(child);
      return;
  }
  random_insert(val, current->children.at(randomNumber));

}

 

Node* Node::generate_tree(int nb_vertices)
{
  // seed rand
  srand(time(NULL));

  Node * root = new Node(0);
  root->number_of_nodes = nb_vertices;
  for(int i=1; i<nb_vertices; i++){
    random_insert(i, root);
  }
  return root;
}

int Node::get_key(){
    return this->key_value;
}

int Node::get_number_of_nodes(){
    return this->number_of_nodes;
}

void Node::display_tree(){
    cout << this->get_number_of_nodes() << endl;
    cout << this->get_key() << ": ";
    for (vector<Node*>::iterator it = this->children.begin() ; it != this->children.end(); ++it){
        cout << (*it)->get_key() << " ";
    }
    for (vector<Node*>::iterator it = this->children.begin() ; it != this->children.end(); ++it){
        Node::display_subtree(*it);
    }
    cout << endl;
}

void Node::display_subtree(Node * subtree){
    if (subtree->children.size() == 0){
        return ;
    }
    cout << endl;
    cout << subtree->get_key() << ": ";
    for (vector<Node*>::iterator it = subtree->children.begin() ; it != subtree->children.end(); ++it){
        cout << (*it)->get_key() << " ";
    }
    for (vector<Node*>::iterator it = subtree->children.begin() ; it != subtree->children.end(); ++it){
        display_subtree(*it);
    }
}
