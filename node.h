//Header guards and imports
#ifndef NODE_H
#define NODE_H
#include <iostream>
//using namespace std;

//Node class
class Node{
public:
  Node();
  //~Node();
  /*
  void setLeft(node*);
  void setRight(node*);
  void setParent(node*);
  */
  //private:
  Node* left;
  Node* right;
  Node* parent;
  int data;
  char type; // red/black
};

//End of header guard
#endif
