#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

using namespace std;

Node::Node(int key)
{
  key_value = key;
}

void Node::random_insert(int val, Node current)
{
  if(current->children == NULL){
      Node child(val);
      current.children.push_back(child);

  }
  else{

   
  
}
}
 

Node Node::generate_tree(int nb_vertices)
{
  Node root = new Node(0);
  for(int i=1; i<nb_vertices; i++)
    random_insert(i, root);


  return root;
}
