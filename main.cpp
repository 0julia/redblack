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
void rotate(Node* current, Node*& head);


int main(){
  Node* head=NULL;
  fstream f("nums.txt");
  int fnum;
  bool done = false;
  
  do{ // keep going till quit
    string input;
    cout << "What would you like to do?(add, print, quit) ";//search, delete, print, quit) ";
    cin >> input;

    if(input == "add"){
      //ask input
      cout << "input a number to add please (If you would like to input a file type '0') ";
      int num;
      cin >> num;
      if (num == 0){
	while (f >> fnum){
	  add(head, head, fnum);
	}
	cout <<endl;
      }else{
	add(head, head, num);
      }
      if (head != NULL){head->type='b';}//double check that head is black
      //search
    }else if(input == "print"){
      print(head, 0);
    }else if(input == "quit"){
      //leave
      done=true;
    }else{
      cout<<"Sorry, that was an invalid command" << endl;
    }
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
  switch colors: dont rly know what the exact rules for color switch are


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
  //cout << "parent: " << current->parent->data << " " << current->parent->type << endl << "Current: " << current->data << " " << current->type << endl;
  cout << "1" << endl;
  if(head==NULL){return;}
  cout << "2" << endl;
  if(current->parent==NULL){return;}
  cout << "3" << endl;
  if(current->parent->type == 'b'){return;}
  cout << "4" << endl;

  Node* unc = uncle(current);
  if(unc->type == 'r'){
    unc->parent->type = 'r';
    current->parent->type = 'b';
    unc->type = 'b';
    current->type = 'r';
    whichCase(unc->parent, head);//put at end?
  }else{
    //LL or LR or RR or RL
  }
  return;
}

void rotate(Node* current, Node*& head){
  if (!current->parent->parent){cout << "rotate error" << endl; return;}
  
  if(current->parent < uncle(current)){ //left child
    
  }else if(current->parent > uncle(current)){ //right child
    
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
      current->right->parent = head;
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
