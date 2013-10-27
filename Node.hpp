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
  string display_tree();
  

  int key_value;
  vector<Node> *children;
  

};
