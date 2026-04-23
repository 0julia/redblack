//Header guards and imports
#include <iostream>
#include "node.h"
using namespace std;

Node::Node(){//int data, Node* parent, Node* left, Node* right){
  left=NULL;
  right=NULL;
  parent=NULL;
  data=0;
  type='r'; // red/black
  
}

