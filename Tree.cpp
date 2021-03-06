#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring>
#include "Graph.hpp"
#include "Utils.hpp"
#include "Tree.hpp"

using std::cout;
using std::endl;
using std::ifstream;

using namespace std;

#define BUFFER_LENGTH 10000

Tree::Tree()
{
}

Tree::Tree(Node * root)
{
    this->root = root;
    this->nodes.push_back(root);
}

Tree::~Tree(){
    //delete nodes;
}

void Tree::random_insert(Node* leaf)
{
    if (this->nodes.size() == 0){
        this->nodes.at(0)->add_child(leaf);
        return ;
    }

    // We choose a random node in all the nodes already in the tree and we put our new node into his list of children
    int randomNumber = rand() % this->nodes.size();
    leaf->set_parent(this->nodes.at(randomNumber));
    TreeEdge* edge = new TreeEdge(this->nodes.at(randomNumber), leaf);
    this->edges.push_back(edge);

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

// !!! This function doesn't copy the edges !!!
Tree* Tree::get_tree_copy(){

    Tree* tree_copy = new Tree();


    // we add all the nodes in the structure
    for (vector<Node*>::iterator current = this->nodes.begin() ; current != this->nodes.end(); ++current){
        Node * node = new Node((*current)->get_key());
        tree_copy->nodes.push_back(node);
    }
    // we add the children
    for (vector<Node*>::iterator current = this->nodes.begin() ; current != this->nodes.end(); ++current){
        if ((*current)->number_of_children() != 0){
            set<Node*> children;
            for (set<Node*>::iterator it = (*current)->get_children().begin() ; it != (*current)->get_children().end(); ++it){
                // we find the good node
                children.insert(tree_copy->nodes.at((*it)->get_key()));
            }
            ((Node*)tree_copy->nodes.at((*current)->get_key()))->get_children() = children;
        }
        // we add the father
        if ((*current)->get_parent() != NULL)
            ((Node*)tree_copy->nodes.at((*current)->get_key()))->set_parent((Node*)tree_copy->nodes.at(((Node*)(*current)->get_parent())->get_key()));
    }
    // set the root
    tree_copy->root = tree_copy->nodes.at(this->root->get_key());
    return tree_copy;
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

vector<Node*> & Tree::get_nodes(){

    return this->nodes;
}

bool Tree::exist_edge(Tree t){
    if (t.get_edges().size()==0)
        return false;
    return true;

}

vector<TreeEdge*> Tree::get_edges(){
    return this->edges;
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


// Old way (too many nodes at the top of the tree)

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


Tree * Tree::generate_tree_from_file(char* filename){

    ifstream fin;
    fin.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    Node* root = new Node(0);
    Tree* t = new Tree(root);

    vector<Node *> nodeList;
    vector<char *> v;
    vector<TreeEdge *> e;

    int loop = 0;
    int num_node=0;
    int size = 0;
    int nb_vertices = 0;

    while (!fin.eof()){

        char str[BUFFER_LENGTH];
        fin.getline(str, BUFFER_LENGTH);

        if(loop++ == 0){
            char* line_token[BUFFER_LENGTH] = {};
            line_token[0] = strtok(str, " :");
            nb_vertices = atoi(line_token[0]);
            for(int i = 0; i< nb_vertices; i++)
                nodeList.push_back(new Node(i));
        }
        if(loop>1 && loop<nodeList.size() + 2){
            char* line_token[BUFFER_LENGTH] = {};
            line_token[0] = strtok(str, " :");
            v.push_back(line_token[0]);
            if (line_token[0]){
                for (int n = 1; n < BUFFER_LENGTH; n++){
                    line_token[n] = strtok(0, " :");
                    if (!line_token[n])
                        break;
                    v.push_back(line_token[n]);
                }
            }
            if(v.size()>size +1)
            {
                for(int j =1+size; j<v.size(); j++){
                    string sv;
                    if(v[j] != NULL)
                        sv = v[j];
                    int nb = atoi(sv.c_str());
                    e.push_back(new TreeEdge(nodeList[num_node], nodeList[nb]));
                    nodeList[num_node]->add_child(nodeList[nb]);
                }
            }
            size = v.size();
            num_node++;
        }
    }


    t->edges = e;
    t->nodes = nodeList;
    return t;

}
