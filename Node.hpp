#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

using namespace std;

class Node
{

public:
  
  Node(int val);
  int get_key();
  int number_of_children();
  void add_child(Node* node);
  void display_children();


private:
  int key_value;
  vector<Node *> children;
  

};

#endif
