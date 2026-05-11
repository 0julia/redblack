#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"
using namespace std;


void add(Node*& head, Node* current, int info);
void print(Node* head, int depth);
Node* search(Node* head, int query);
Node* uncle(Node* current);
Node* sibling(Node* current);
void del(Node*& head, int info);
void allDone(Node* head);
void whichCase(Node* current, Node*& head);
Node* lrotate(Node* current, Node*& head);
Node* rrotate(Node* current, Node*& head);
void colorFix(Node*& head, char ogColor);

int main(){
  Node* head=NULL;
  bool done = false;
  fstream f("nums.txt");
  int fnum;  

  do{ // keep going till quit
    string input;
    cout << "What would you like to do?(add, search, delete, print, quit) ";
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
      }else{
	add(head, head, num);
      }
      if (head != NULL){head->type='b';}//double check that head is black
      //search
    }else if(input == "search"){
      int guess;
      cout << "What number are you looking for? ";
      cin >> guess;
      if (search(head, guess)!=NULL){
	cout << "Number found" <<endl;
      }
    }else if(input == "delete"){
      int guess;
      cout << "What number are you wanting to remove? ";
      cin >> guess;
      if (search(head, guess)!=NULL){
	cout<<"entering del function" << endl;
	del(head, guess);
	cout<<"exiting del function" << endl;
      }
      print(head,0);
      cout << head<<endl;
    }else if(input == "print"){
      print(head, 0);
    }else if(input == "quit"){
      //leave
      done=true;
    }else{
      cout<<"Sorry, that was an invalid command" << endl;
    }
    cout << endl;
    //cout <<"Head: "<< head<<" Left: "<< head->left<<"Right: "<< head->right<<endl;
  }while(done==false);
  f.close();
  return 0;
}


void colorFix(Node*& head, char ogColor){
  if(!head){return;}
  //if(
}

Node* nextLargest(Node* head){
  if (head->left == NULL){
    return head;
  }
  return nextLargest(head->left);
}



//void del(Node*& head, int num){
void del(Node*& head, int info){
  if(!head){
    cout << "tree empty";
    return;
  }
  Node* current = search(head, info);
  if(current == NULL){
    return;
  }
  char ogColor=current->type;
  
  //deletes things with no leafs
  if(current->left == NULL && current->right == NULL){
    if (current->parent != NULL){
      if(current->parent->left == current){//left child
	current->parent->left = NULL;
      }else if (current->parent->right == current){//right child
	current->parent->right = NULL;
      }
    }else{//if head
      head = NULL;
    }
    
    delete current;
    return;
  }


  //deletes things with one leaf (right child)
  if(current->left == NULL && current->right != NULL){
    if (current->parent ==NULL){
      head = current->right;
      current->right->parent = NULL;
      delete current;
      return;
    }

    if(current->parent->left == current){
      current->parent->left = current->right;
    }else{
      current->parent->right = current->right;
    }
    current->right->parent=current->parent;
    delete current;
    return;
  }
  //deletes thing with only left leaf
  if(current->left != NULL && current->right == NULL){
    if (current->parent ==NULL){
      head = current->left;
      current->left->parent = NULL;
      delete current;
      return;
    }
      if(current->parent->right == current){
      current->parent->right = current->left;
    }else{
      current->parent->left = current->left;
    }
    current->left->parent=current->parent;
    delete current;
    return;
  }

   //deletes 2 leafs
  if(current->left != NULL && current->right != NULL){
    Node* next = nextLargest(current->right);
    //if next has a right child, need to attach that child to its parent
    if(next != current->right){//if next biggest isn't hte imediet next one
      if(next->right != NULL){
	next->right->parent=next->parent;
      }
      if(next->parent->right==next){
	next->parent->right = next->right;
      }else{
	next->parent->left = next->right;
      }
    }

    
    //   print(current, 0);

    if(next != current->right){
      next->right=current->right;
      current->right->parent=next;
    }
    cout << search(head, 70)->left->parent->data<<endl;
    //    print(search(head, 70),0);
    
    next->left=current->left;
    current->left->parent = next;
    next->parent=current->parent;
    print(next,0);
    //if the one being replaced is the first thinger
    if(current->parent==NULL){
      head=next;
    }else if(current->type>current->parent->type){
      current->parent->right=next;
    }else{
      current->parent->left=next;
    }
    cout <<endl<<"checking: " << endl<<endl;
    print(current->parent,0);
    cout << endl<<endl<<"done checking" <<endl;
    delete current;
    return;
  }
}

 
void del2(Node*& head, int num){
  if(!head){return;}
  if (!head->parent && head->data==num){
    //delete head;
    head = NULL;
    //delete head;
    return;
  }
  //get to right place
  if (head->data < num){
    return del(head->right, num);
  }else if(head->data > num){
    return del(head->left, num);
  }
  char ogType = head->type;
  cout << "in del function at right place? " << head->data <<endl;
  if (head->left == NULL && head->right == NULL){// && head->type == 'r'){
    cout << "1"<< endl;
    if(num < head->parent->data){
      head->parent->left=NULL;
    }else if(num > head->parent->data){
      head->parent->right=NULL;
    }
    head=NULL;
  }else if(!head->left && head->right){
    head->parent=head->right;
    head->right->parent= head->parent;
    delete head; // could I go: head = NULL? why doesnt' that work above?
  }else if(!head->right && head->left){
    head->parent=head->left;
    head->left->parent= head->parent;
    delete head; // could I go: head = NULL? why doesnt' that work above?
  }
  return;
}

//should it have a return type
void whichCase(Node* current, Node*& head){
  if(!head||!current||!current->parent||!current->parent->parent){return;}
  if(current->parent->type == 'b'){return;}
  Node* unc = uncle(current);
  if(unc != NULL && unc->type == 'r'){
    current->parent->type = 'b';
    unc->type = 'b';
    current->parent->parent->type = 'r';
    current->type = 'r';
    whichCase(current->parent->parent, head);//put at end?
  }else{
    //if uncle is black or null...
    if(current->parent->data < current->parent->parent->data){ // and left child...
      current=lrotate(current, head);//rotate LL or LR
    } else if(current->parent->data > current->parent->parent->data){ // and right child...
      current=rrotate(current, head);//rotate RR or RL
    }
  }
  return;
}

Node* rrotate(Node* current, Node*& head){
  if (!current || !current->parent || !current->parent->parent){cout << "rotate error" << endl; return NULL;}
  Node* temp = current;
  Node* gpa = current->parent->parent;
  if(current->parent==gpa->right && current== current->parent->right){ //right grandchild 
    current=current->parent;
    Node* leftChild = current->left;
    Node* parentPointer = gpa->parent;
    current->parent=parentPointer;
    if(!parentPointer){
      head=current;
    }else{
      if(current->data < current->parent->data){
	parentPointer->left=current;//I FEEL LIKE THIS IS WRO
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
  if (!current || !current->parent || !current->parent->parent){cout << "rotate error" << endl; return NULL;}
  Node* temp = current;
  Node* gpa = current->parent->parent;
  if(current->parent->data > current->data){ //left grandchild 
    current=current->parent;
    Node* rightChild = current->right;
    Node* parentPointer = current->parent->parent;
    current->parent=parentPointer;
    current->left=temp;
    temp->parent=current;
    if (head==gpa){
      head=current;
    }else{
      if(current->data < current->parent->data){
	parentPointer->left=current;//I FEEL LIKE THIS IS WRO
      }else{
	parentPointer->right=current;
      }
    }
    gpa->left=current->right;
    gpa->parent=current;
    current->right=gpa;
    char temp = gpa->type;
    gpa->type=current->type;
    current->type=temp;
    return current;
  }else{//LR situation
    current=temp->parent;
    //set g-pa and parent pointing to each other
    gpa->left=temp;
    temp->parent=gpa;
    //set child and parent pointing to each other
    Node* child1 = temp->left;
    temp->left=current;
    current->right=child1;
    current->parent=temp;
    return lrotate(current,head);
  }
  return NULL;
}

Node* sibling(Node* current){
  if (!current){return NULL;}
  if (!current->parent){return NULL;}

  Node* parent= current->parent;//grandpa
  if(parent->left==current){
    return parent->right;
  }else{
    return parent->left;
  }
  cout << "bug sibling function";
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
    cout << "Sorry, that number is not in the tree" << endl;
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
  //cout << "Current: "<< current<<endl;
  //cout <<"Current Data: " << current->data <<endl;
  //print right then middle then left
  print(current->right, depth+1);
  for (int i = 0; i< depth; i++){
    cout << "    ";
  }
  cout << current->data << " "<< current->type << endl;
  print(current->left, depth+1);
}
