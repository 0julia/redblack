//Header guards and imports
#include <iostream>
#include "node.h"
using namespace std;

Node::Node(){

  left=NULL;
  right=NULL;
  parent=NULL;
  data=0;
  type='r'; // red/black

}

