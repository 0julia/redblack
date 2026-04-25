#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"
using namespace std;


void add(Node*& head, Node* current, int info);
void print(Node* head, int depth);
Node* search(Node* head, int query);
Node* uncle(Node* current);
//void del(Node*& head, int info);
void allDone(Node* head);
void whichCase(Node* current, Node*& head);
Node* lrotate(Node* current, Node*& head);
void rrotate(Node*& current, Node*& head);


int main(){
  Node* head=NULL;
  fstream f("nums.txt");
  int fnum;
  bool done = false;
  
  do{ // keep going till quit
    string input;
    //cout << "What would you like to do?(add, print, quit) ";//search, delete, print, quit) ";
    //cin >> input;

    //if(input == "add"){
      //ask input
      cout << "input a number to add please (If you would like to input a file type '0') ";
      int num;
      cin >> num;
      if (num == 0){
	print(head,0);
	/*while (f >> fnum){
	  add(head, head, fnum);
	  }*/
	cout <<endl;
      }else{
	add(head, head, num);
      }
      if (head != NULL){head->type='b';}//double check that head is black
      //search
      /*}else if(input == "print"){
      print(head, 0);
    }else if(input == "quit"){
      //leave
      done=true;
    }else{
      cout<<"Sorry, that was an invalid command" << endl;
      }*/
    cout << endl;
  }while(done==false);
  
  f.close();
  return 0;
}


/*moves ill need to do:
  look at gpa
  look at uncle
  rotate left
  rotate right

  1)put node in right spot (need to pass thru current into functions too)
  2)if parent black, leave as is
  3)if parent red:
     3.1)if node is left child and parent is right, rotate (grandchild and child switch spots)
     3.2)if both parent and child are right, rotate (child becomes parent with root and grandchild becoming children)

     3.3)if uncle red, push blackness from grandparnet, gpa becomes red
     3.4)
*/

//should it have a return type
void whichCase(Node* current, Node*& head){
  if(head==NULL){return;}
  if(current->parent==NULL){return;}
  if(current->parent->type == 'b'){return;}
  
  Node* unc = uncle(current);
  if(unc != NULL && unc->type == 'r'){
    current->parent->type = 'b';
    unc->type = 'b';
    current->parent->parent->type = 'r';
    current->type = 'r';
    whichCase(current->parent->parent, head);//put at end?
  }else{
      cout << "0" << endl;
    //if uncle is black or null...
    if(!uncle(current)||current->parent->data < uncle(current)->data){ // and left child...
      current=lrotate(current, head);//rotate LL or LR
    }
  }
  return;
}

Node* lrotate(Node* current, Node*& head){
  cout << "enter lrotate" << endl;
  if (!current->parent->parent){cout << "rotate error" << endl; return NULL;}
  Node* temp = current;
  Node* gpa = current->parent->parent;
  
  if(current->parent->data > current->data){ //left grandchild 
    current=current->parent;
    cout <<"ll"<< endl;
    Node* rightChild = current->right;
    Node* parentPointer = current->parent->parent;
    current->parent=parentPointer;
    current->left=temp;
    temp->parent=current;
    if (head==gpa){
      head=current;
    }else{
      parentPointer->left=current;
    }
    gpa->left=current->right;
    gpa->parent=current;
    current->right=gpa;
    char temp = gpa->type;
    gpa->type=current->type;
    current->type=temp;
    
    //move parent to grandparent spot
  }else{
    current=temp->parent;
    //set g-pa and parent pointing to each other
    gpa->left=temp;
    temp->parent=gpa;
    //set child and parent pointing to each other
    Node* child1 = temp->left;
    current->left=temp;
    temp->parent=current;
    temp->right=child1;
    cout << "Current: " << temp->data << " parent: " << temp->parent->data << " UNC: " << uncle(temp)->data << endl;
    //lrotate(temp,head);
  }
  
  return current;
  
}

void rrotate(Node*& current, Node*& head){
  cout <<"2"<< endl;
  if (!current->parent->parent){cout << "rotate error" << endl; return;}
  cout <<"3"<< endl;
  Node* gpa = current->parent->parent;
  if(current==current->parent->right){//RR rotation
    //move parent to grandparent spot
  }else{//RL rotation
    //switch child and parent then RR
  }
}

Node* uncle(Node* current){
  if (!current){return NULL;}
  if (!current->parent){return NULL;}
  if (!current->parent->parent){return NULL;}//do i need all these?

  Node* gpa= current->parent->parent;//grandpa
  if(gpa->left==current->parent){
    return gpa->right;
  }else{
    return gpa->left;
  }
  cout << "bug uncle function";
  return NULL;
  
}

void add(Node*& head, Node* current, int info) {
  //add leaf
  if (head==NULL) {
    head = new Node();
    head->data = info;
    return;
  }
  if (info < current->data) {
    if (current->left==NULL) { // if input is less than head and at end, add
      current->left = new Node();
      current->left->data = info;
      current->left->parent = current;
      cout << "0.1" << endl;
      //cout << "current: " << current->data << endl << "head: " << head->data << endl;
      whichCase(current->left, head);
    } else { 
      add(head, current->left, info); // recursive
    }
  } else if (info > current->data) {
    if (current->right==NULL) { //if input is bigger than head and at end, add
      current->right = new Node();
      current->right->data = info;
      current->right->parent = current;
      cout << "0.2" << endl;
      //cout << "current: " << current->data << endl << "head: " << head->data << endl;
      whichCase(current->right, head);
    } else {
      add(head, current->right, info); // recursive
    }
  } else {
    cout << "problem";
  }
  //
}


//deletes the stuff:
void allDone(Node* head){
  if (head==NULL){
    return;}
  allDone(head->left);
  allDone(head->right);
  delete head;
}

Node* search(Node* head, int query){
  if(!head){//at end of thread and its not there
    cout << "Sorry, that number is not in the tree";
    return NULL;
  }
  //if found, return it
  if(head->data == query){
    return head;
  }else if(head->data > query){
    //recursive
    return search(head->left, query);
  }else if(head->data < query){
    return search(head->right, query);
  }else{ // debug
    cout <<"Problem!" << endl;
  }
  return NULL;
}


void print(Node* current, int depth){
  if(current == NULL){ //if leaf, end that
    return;
  }
  //print right then middle then left
  print(current->right, depth+1);
  for (int i = 0; i< depth; i++){
    cout << "   ";
  }
  cout << current->data << " "<< current->type << endl;
  print(current->left, depth+1);
}
