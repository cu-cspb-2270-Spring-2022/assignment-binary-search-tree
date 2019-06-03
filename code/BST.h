#ifndef BST_H__
#define BST_H__

#include <string>
#include <memory>

using namespace std;

struct node {
  int data;               // data: the value of this node
  shared_ptr<node> next;  // next: pointer to the next node in the list, or NULL if this is the last node.
};

class BST {
public:
  // constructor, initialize class variables and pointers here if need.
  // Initially set top pointer to a null shared_ptr of node
  BST();

  //deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~BST();

private:

  // you can add add more private member variables and member functions here if you need
};

#endif  // BST_H__
