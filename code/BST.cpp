#include "BST.h"

// constructor, initialize class variables and pointers here if need.
BST::BST(){
  // Your code here
}

//deconstructor,
BST::~BST(){
}

shared_ptr<bt_node> BST::InitNode(int data){
  shared_ptr<bt_node> ret;
  // Your code here
  return ret;
}

void BST::Insert(shared_ptr<bt_node> new_node){
  // Your code here
}

void BST::Insert_data(int data){
  // Your code here
}

void BST::Remove(int data){
  // Your code here
}

bool BST::Contains(shared_ptr<bt_node> t, int data){
  bool ret;
  // Your code here
  return ret;
}

shared_ptr<bt_node> BST::GetNode(shared_ptr<bt_node> subt, int data){
  shared_ptr<bt_node> ret;
  // Your code here
  return ret;
}

int BST::Size(shared_ptr<bt_node> subt){
  int ret;
  // Your code here
  return ret;
}

void BST::ToArray(shared_ptr<bt_node> subt, vector<int>& arr){
  // Your code here
  // eventually fill in arr ex. arr[0] = 1;
}

// This function is implemented for you
// Returns the root pointer
shared_ptr<bt_node> BST::GetRoot(){
  return root_ptr_;
}

// This function is implemented for you
// sets a given pointer as the top pointer
void BST::SetRoot(shared_ptr<bt_node> root_ptr){
  root_ptr_ = root_ptr;
}