#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Node
{

public:
  
  Node(int val);
  static Node* generate_tree(int nb_vertices);
  static void random_insert(int key, Node *leaf);
  void display_tree();
  void display_subtree(Node * subtree);
  int get_key();
  int get_number_of_nodes();
  
  int number_of_nodes;
  int key_value;
  vector<Node *> children;
  

};
