#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Node
{

public:
  
  void Node();
  void generate_tree(int nb_vertices);
  void random_insert(int key, node *leaf);
  

  int key_value;
  vector<Node> *children;
  

};
