#include <iostream>
#include <string>
#include "Tree.hpp"

using namespace std;


Tree::Tree(Node * root)
{
    this->root = root;
    this->nodes.push_back(root);
}

Tree::~Tree(){
    //delete nodes;
}

// Old way (too many nodes at the top of the tree)
/*
void Node::random_insert(Node* leaf)
{
  // If the current node doesn't have any child, we put our node here
  if(leaf->children.size() == 0){
     Node * child = new Node(val);
     leaf->children.push_back(child);
     return;
  }


  // This number will be an integer between 1 and the number of children of our current node + 1
  // (because we can insert our node directly in the current node)
  int randomNumber = rand() % (leaf->children.size() + 1);

  // We need to subtract one to select the child number 0
  // We insert the node here
  if(randomNumber == leaf->children.size()){
      Node * child = new Node(val);
      leaf->children.push_back(child);
      return;
  }
  random_insert(val, leaf->children.at(randomNumber));

}*/


void Tree::random_insert(Node* leaf)
{
    if (this->nodes.size() == 0)
        this->nodes.at(0)->add_child(leaf);

  // We choose a random node in all the nodes already in the tree and we put our new node into his list of children
  int randomNumber = rand() % this->nodes.size();

  this->nodes.at(randomNumber)->add_child(leaf);
}


Tree* Tree::generate_tree(int nb_vertices)
{
  // seed rand
  srand(time(NULL));
  Node * root = new Node(0);
  Tree * tree = new Tree(root);
  for(int i=1; i<nb_vertices; i++){
    Node * child = new Node(i);
    tree->random_insert(child);
    tree->nodes.push_back(child);
  }
  return tree;
}

int Tree::get_number_of_nodes(){
    return this->nodes.size();
}

vector<Node*>::iterator  Tree::get_iterator_begin(){
    return this->nodes.begin();
}

vector<Node*>::iterator  Tree::get_iterator_end(){
    return this->nodes.end();
}

// Old way
/*
void Tree::display_tree(){
    cout << this->nodes.size() << endl;
    Node* root = this->root;
    cout << root->get_key() << ": ";
    for (vector<Node*>::iterator it = root->children.begin() ; it != root->children.end(); ++it){
        cout << (*it)->get_key() << " ";
    }
    for (vector<Node*>::iterator it = root->children.begin() ; it != root->children.end(); ++it){
        Tree::display_subtree(*it);
    }
    cout << endl;
}

void Tree::display_subtree(Node * subtree){
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
*/

