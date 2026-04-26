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
Node* rrotate(Node* current, Node*& head);


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



//should it have a return type
void whichCase(Node* current, Node*& head){
  if(head==NULL){return;}
  if(current->parent==NULL){return;}
  if(current->parent->type == 'b'){return;}
  cout << "-2 "<<endl<<endl;
  Node* unc = uncle(current);
  if(unc != NULL && unc->type == 'r'){
    current->parent->type = 'b';
    unc->type = 'b';
    current->parent->parent->type = 'r';
    current->type = 'r';
    whichCase(current->parent->parent, head);//put at end?
  }else{
    cout << "-1 "<<endl;
    //if uncle is black or null...
    if(current->parent->data < current->parent->parent->data){ // and left child...
      cout << "8"<<endl;
      current=lrotate(current, head);//rotate LL or LR
      cout << "9"<<endl;
    }
    if(current->parent->data > current->parent->parent->data){ // and right child...
      cout << "0 "<<endl<<endl;
      current=rrotate(current, head);//rotate RR or RL
    }
  }
  cout << "10"<<endl;
  return;
}

Node* rrotate(Node* current, Node*& head){
  cout << "1 "<<endl;
  if (!current || !current->parent || !current->parent->parent){cout << "rotate error" << endl; return NULL;}
  cout << "2 "<<endl;
  Node* temp = current;
  Node* gpa = current->parent->parent;
  cout << "3 "<<endl;
  if(current->parent==gpa->right && current== current->parent->right){ //right grandchild 
    cout << "4 "<<endl;
    current=current->parent;
    Node* leftChild = current->left;
    Node* parentPointer = gpa->parent;
    current->parent=parentPointer;
    //current->right=temp;
    //temp->parent=current;
    if (parentPointer){//head==gpa){
      if(parentPointer->left==gpa){
	parentPointer->left=current;
      }else{
	parentPointer->right=current;
      }
    }
    
    current->left=gpa;
    gpa->parent=current;

    gpa->right=leftChild;//current->left;
    if(leftChild !=NULL){
      leftChild->parent=gpa;
    }
    if(head=gpa){
      head=current;
    }
    
    char temp = gpa->type;
    gpa->type=current->type;
    current->type=temp;
    return current;
  }else{//RL situation
    current=temp->parent;
    //set g-pa and parent pointing to each other
    gpa->right=temp;
    temp->parent=gpa;
    //set child and parent pointing to each other
    Node* child1 = temp->right;
    temp->right=current;
    current->left=child1;
    current->parent=temp;
    return rrotate(current,head);
  }
  return NULL;  
}

Node* lrotate(Node* current, Node*& head){
  cout << "0"<<endl;
  if (!current || !current->parent || !current->parent->parent){cout << "rotate error" << endl; return NULL;}
  Node* temp = current;
  Node* gpa = current->parent->parent;
  cout << "1"<<endl;

  if(current->parent->data > current->data){ //left grandchild 
    cout << "2"<<endl;
    current=current->parent;
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
    cout << "3"<<endl;
    gpa->left=current->right;
    gpa->parent=current;
    current->right=gpa;
    char temp = gpa->type;
    gpa->type=current->type;
    current->type=temp;
    cout << "4"<<endl;
    return current;
  }else{//LR situation
    cout << "5"<<endl;
    current=temp->parent;
    //set g-pa and parent pointing to each other
    gpa->left=temp;
    temp->parent=gpa;
    //set child and parent pointing to each other
    cout << "6"<<endl;
    Node* child1 = temp->left;
    temp->left=current;
    current->right=child1;
    current->parent=temp;
    cout << "7"<<endl;
    return lrotate(current,head);
  }
  return NULL;
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
      whichCase(current->left, head);
    } else { 
      add(head, current->left, info); // recursive
    }
  } else if (info > current->data) {
    if (current->right==NULL) { //if input is bigger than head and at end, add
      current->right = new Node();
      current->right->data = info;
      current->right->parent = current;
      whichCase(current->right, head);
    } else {
      add(head, current->right, info); // recursive
    }
  } else {
    cout << "problem in add function" << endl;
  }
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
    cout << "    ";
  }
  cout << current->data << " "<< current->type << endl;
  print(current->left, depth+1);
}
