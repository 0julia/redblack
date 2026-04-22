#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"
using namespace std;


void add(Node*& head, int info);
void print(Node* head, int depth);
Node* search(Node* head, int query);
Node* casesearch(Node* head, int query);
void del(Node*& head, int info);
Node* nextLargest(Node* head);
void allDone(Node* head);
void case1(Node*& head, int info, Node* parent);
void case2(Node*& head, int info);
void case3(Node*& head, int info);
void case4(Node*& head, int info);
void case5(Node*& head, int info);
void case6(Node*& head, int info);
Node* whichCase(Node* head, int info);


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
	  add(head,fnum);
	}
	cout <<endl;
      }else{
	head = whichCase(head,num);
	cout << "Head: " << head->data << endl;
      }
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

Node* whichCase(Node* head, int data){
  cout << "1" << endl;
  
  if(!head){
    cout << "2" << endl;
    case1(head,data, NULL);
    cout << "6" << endl;
    return head;
  }
  Node* parent = search(head, data);
  if (!parent){
    cout << "prob line 78";
    return NULL;
  }else if(parent->type == 'b'){
    case1(head, data, parent);
    
  }
  return NULL;
}
  
  
void case1(Node*& head, int info, Node* parent){
  cout << "3" << endl;
  if(!head){//at end of thread and its not there
    cout << "4" << endl;
    head = new Node();
    head->data=info;
    head->type='b';
    cout << "5" << endl;
    return;
  }

  if(parent->type = 'r'){
    cout << "Should be b";
  }else if(parent->data < info){
    head->left = new Node();
    head->left->data = info;
    head->left->parent = head;
  }else if(parent->data > info){
    head->right = new Node();
    head->right->data = info;
    head->right->parent = head;
  }
  return;
}


//deletes the stuff:
void allDone(Node* head){
  if (head==NULL){
    return;}
  allDone(head->left);
  allDone(head->right);
  delete head;
}


//when calling the first time make sure you call wtvr thing you want's right child
Node* nextLargest(Node* head){
  if (head->left == NULL){
    return head;
  }
  return nextLargest(head->left);
}
  


Node* casesearch(Node* head, int info){ // returns where i
  if(!head){//at end of thread and its not there
    cout << "Sorry, that number is not in the tree";
    return NULL;
  }
  //if found, return it
  if(!head->left->data && head->data < info){
    return head;
  } else if(!head->right->data && head->data > info){
    return head;
  }else if(head->data > info){
    //recursive
    return casesearch(head->left, info);
  }else if(head->data < info){
    return casesearch(head->right, info);
  }else{ // debug
    cout <<"Problem!" << endl;
  }
  return NULL;
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


void add(Node*& head, int info) {
  //add leaf
  if (head==NULL) {
    head = new Node();
    head->data = info;
    return;
  }
  if (info < head->data) {
    if (head->left==NULL) { // if input is less than head and at end, add
      head->left = new Node();
      head->left->data = info;
      head->left->parent = head;
    } else { 
      add(head->left, info); // recursive
    }
  } else if (info > head->data) {
    if (head->right==NULL) { //if input is bigger than head and at end, add
      head->right = new Node();
      head->right->data = info;
      head->right->parent = head;
    } else {
      add(head->right, info); // recursive
    }
  } else {
    cout << "problem";
  }
  */
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
