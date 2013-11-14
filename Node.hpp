#ifndef NODE_HPP
#define NODE_HPP

#include <set>

using namespace std;

class Node
{

public:
  
  Node(int val);
  ~Node();
  int get_key();
  int number_of_children();
  void add_child(Node* node);
  void display_children();
  void set_parent(Node* parent);
  set<Node *>& get_children();
  Node *get_parent();


private:
  int key_value;
  set<Node *> children;
  Node* parent;
  

};

#endif
