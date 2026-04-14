#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"
using namespace std;

/*struct Node{
  Node* left=NULL;
  Node* right=NULL;
  int data;
  Node* parent=NULL;
  };*/

void add(Node*& head, int info);
void print(Node* head, int depth);
Node* search(Node* head, int query);
void del(Node*& head, int info);
Node* nextLargest(Node* head);
void allDone(Node* head);
void case1(Node*& head, int info);
void case2(Node*& head, int info);
void case3(Node*& head, int info);
void case4(Node*& head, int info);
void case5(Node*& head, int info);
void case6(Node*& head, int info);
int whichCase(Node* head);


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
	add(head,num);
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


void case1(Node* head){
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


void add(Node*& head, int info){
  //add leafs
  if (head == NULL){
    Node* new_current = new Node();
    head = new_current;
    head->data = info;
    head->parent=NULL;
    return;
  }
  //if input is less than head and at end, add 
  if(head->data > info && head->left==NULL){
    Node* new_current = new Node();
    head->left=new_current;
    new_current->data=info;
    new_current->parent = head;
    return;
  }else if(head->data < info && head->right==NULL){
  //if input is more than head and at end, add 
    Node* new_current = new Node();
    head->right=new_current;
    new_current->data=info;
    new_current->parent = head;
    return;
  }else if(head->data > info){
  //if input is less than head and not at end
    add(head->left, info);
  }else if(head->data < info){
    add(head->right, info);
  }else{
  //if input is more than head and not at end
    cout<< "problem";
  }
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
  cout << current->data << endl;
  print(current->left, depth+1);
}
